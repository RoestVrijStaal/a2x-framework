/*
    Copyright 2010 Alex Margarit

    This file is part of a2x-framework.

    a2x-framework is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    a2x-framework is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with a2x-framework.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "a2x_pack_sprite.p.h"
#include "a2x_pack_sprite.v.h"

struct SpriteAnimation {
    Sprite** sprites;
    fix8 num;
    fix8 current;
    fix8 speed;
    int dir;
};

struct SpriteFrames {
    int num;
    Sprite** frames;
};

static List* sprites;

static void setSheetValues(Sheet* const s);

void a_sprite__set(void)
{
    sprites = a_list_set();
}

void a_sprite__free(void)
{
    while(a_list_iterate(sprites)) {
        a_sprite_free(a_list_current(sprites));
    }

    a_list_free(sprites);
}

Sheet* a_sprite_sheetFromFile(const char* const path)
{
    SDL_Surface* const sf = IMG_Load(path);
    Sheet* const s = malloc(sizeof(Sheet));

    s->w = sf->w;
    s->h = sf->h;
    s->data = malloc(s->w * s->h * sizeof(Pixel));

    for(int i = 0; i < s->h; i++) {
        for(int j = 0; j < s->w; j++) {
            const Uint8* const p = (Uint8*)sf->pixels + i * sf->pitch + j * sf->format->BytesPerPixel;
            Uint32 pixel;

            switch(sf->format->BytesPerPixel) {
                case 1: {
                    pixel = *p;
                } break;

                case 2: {
                    pixel = *(Uint16*)p;
                } break;

                case 3: {
                    if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                        pixel = (p[0] << 16) | (p[1] << 8) | (p[2]);
                    } else {
                        pixel = (p[0]) | (p[1] << 8) | (p[2] << 16);
                    }
                } break;

                case 4: {
                    pixel = *(Uint32*)p;
                } break;

                default: {
                    pixel = 0;
                } break;
            }

            Uint8 r, g, b;
            SDL_GetRGB(pixel, sf->format, &r, &g, &b);

            s->data[i * s->w + j] = a_screen_makePixel(r, g, b);
        }
    }

    SDL_FreeSurface(sf);

    setSheetValues(s);

    return s;
}

Sheet* a_sprite_sheetFromData(Pixel* data, const int w, const int h)
{
    Sheet* const s = malloc(sizeof(Sheet));

    s->w = w;
    s->h = h;
    s->data = a_mem_decodeRLE(data, w * h, sizeof(Pixel), NULL);

    setSheetValues(s);

    return s;
}

Sheet* a_sprite_sheetFromSheet(const Sheet* const sheet, const int x, const int y, const int w, const int h)
{
    Sheet* const s = malloc(sizeof(Sheet));

    s->w = w;
    s->h = h;
    s->data = malloc(w * h * sizeof(Pixel));

    const int W = sheet->w;
    const Pixel* const src = sheet->data;

    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            s->data[i * w + j] = *(src + (i + y) * W + (j + x));
        }
    }

    s->transparent = sheet->transparent;
    s->limit = sheet->limit;

    return s;
}

void a_sprite_freeSheet(Sheet* const s)
{
    free(s->data);
    free(s);
}

Sprite* a_sprite_makeZoomed(const Sheet* const graphic, const int x, const int y, const int w, const int h, const int zoom)
{
    const int spritew = w * zoom;
    const int spriteh = h * zoom;

    Sprite* const s = malloc(sizeof(Sprite));

    s->w = spritew;
    s->h = spriteh;
    s->data = malloc(spritew * spriteh * sizeof(Pixel));

    const int wp = graphic->w;
    const Pixel* const data = graphic->data;
    Pixel* const dst = s->data;

    // put the pixels on

    for(int i = y; i < y + h; i++) {
        for(int j = x; j < x + w; j++) {
            const Pixel pixel = *(data + i * wp + j);

            const int dy = (i - y) * zoom;
            const int dx = (j - x) * zoom;

            for(int zy = zoom; zy--; ) {
                for(int zx = zoom; zx--; ) {
                    dst[(dy + zy) * spritew + dx + zx] = pixel;
                }
            }
        }
    }

    a_sprite_makeTransparent(s, graphic);

    a_list_addLast(sprites, s);

    return s;
}

Sprite* a_sprite_makeBlank(const int w, const int h)
{
    Sprite* const s = malloc(sizeof(Sprite));

    s->w = w;
    s->h = h;
    s->data = malloc(w * h * sizeof(Pixel));
    s->spansNum = malloc(h * sizeof(int));
    s->spans = malloc(h * sizeof(int**));

    for(int i = 0; i < h; i++) {
        s->spansNum[i] = 1;
        s->spans[i] = malloc(1 * sizeof(int*));

        s->spans[i][0] = malloc(3 * sizeof(int));

        s->spans[i][0][0] = 0;
        s->spans[i][0][1] = w;
        s->spans[i][0][2] = (s->spans[i][0][1] - s->spans[i][0][0]) << 1;
    }

    a_list_addLast(sprites, s);

    return s;
}

void a_sprite_makeTransparent(Sprite* const s, const Sheet* const graphic)
{
    const Pixel tpixel = graphic->transparent;

    s->t = graphic->transparent;

    const int spritew = s->w;
    const int spriteh = s->h;

    const int verti = spriteh;
    const int horiz = spritew;

    s->spans = malloc(verti * sizeof(int**));
    s->spansNum = malloc(verti * sizeof(int));

    const Pixel* const dst = s->data;

    for(int i = 0; i < verti; i++) {
        List* const spans = a_list_set();

        int start = 0;
        int transparent = 1;

        for(int j = 0; j < horiz; j++) {
            const Pixel pixel = dst[i * horiz + j];

            int oldTra = transparent;
            transparent = pixel == tpixel;

            if(oldTra && !transparent) {
                if(j == horiz - 1) {
                    Span* const span = malloc(sizeof(Span));

                    span->x1 = j;
                    span->x2 = horiz;

                    a_list_addLast(spans, span);
                } else {
                    start = j;
                }
            } else if(!oldTra) {
                if(j == horiz - 1) {
                    Span* const span = malloc(sizeof(Span));

                    span->x1 = start;
                    span->x2 = horiz - transparent;

                    a_list_addLast(spans, span);
                } else if(transparent) {
                    Span* const span = malloc(sizeof(Span));

                    span->x1 = start;
                    span->x2 = j;

                    a_list_addLast(spans, span);
                }
            }
        }

        s->spansNum[i] = a_list_size(spans);
        s->spans[i] = malloc(s->spansNum[i] * sizeof(int*));

        int counter = 0;

        while(a_list_iterate(spans)) {
            const int x1 = ((Span*)a_list_current(spans))->x1;
            const int x2 = ((Span*)a_list_current(spans))->x2;

            s->spans[i][counter] = malloc(3 * sizeof(int));

            s->spans[i][counter][0] = x1;
            s->spans[i][counter][1] = x2;
            s->spans[i][counter][2] = x2 - x1;

            counter++;
        }

        a_list_freeContent(spans);
    }
}

void a_sprite_free(Sprite* const s)
{
    free(s->data);

    for(int i = 0; i < s->h; i++) {
        for(int j = 0; j < s->spansNum[i]; j++) {
            free(s->spans[i][j]);
        }
        free(s->spans[i]);
    }
    free(s->spans);
    free(s->spansNum);

    free(s);
}

int a_sprite_w(const Sprite* const s)
{
    return s->w;
}

int a_sprite_h(const Sprite* const s)
{
    return s->h;
}

Pixel* a_sprite_data(const Sprite* const s)
{
    return s->data;
}

SpriteAnimation* a_sprite_makeAnimation(const int num, const int framesPerCycle)
{
    SpriteAnimation* const s = malloc(sizeof(SpriteAnimation));

    s->sprites = malloc(num * sizeof(Sprite*));
    s->num = a_fix8_itofix(num);
    s->current = 0;
    s->speed = s->num / framesPerCycle;
    s->dir = 1;

    return s;
}

void a_sprite_freeAnimation(SpriteAnimation* const s)
{
    free(s->sprites);
    free(s);
}

void a_sprite_addAnimation(SpriteAnimation* const s, Sprite* const sp)
{
    s->sprites[a_fix8_fixtoi(s->current)] = sp;

    s->current += FONE8;

    if(s->current == s->num) {
        s->current = 0;
    }
}

Sprite* a_sprite_nextAnimation(SpriteAnimation* const s)
{
    Sprite* const sp = s->sprites[a_fix8_fixtoi(s->current)];

    s->current += s->speed * s->dir;

    if(s->current >= s->num) {
        s->current = s->current - s->num;

        if(s->current >= s->num) {
            s->current = 0;
        }
    } else if(s->current < 0) {
        s->current = s->num - FONE8 + s->current;

        if(s->current < 0) {
            s->current = s->num - FONE8;
        }
    }

    return sp;
}

void a_sprite_changeAnimationDir(SpriteAnimation* const s, const int dir)
{
    s->dir = dir;
}

void a_sprite_flipAnimationDir(SpriteAnimation* const s)
{
    s->dir *= -1;
}

SpriteFrames* a_sprite_makeFrames(void)
{
    SpriteFrames* const s = malloc(sizeof(SpriteFrames));

    s->num = 0;
    s->frames = NULL;

    return s;
}

void a_sprite_freeFrames(SpriteFrames* const s)
{
    free(s->frames);
    free(s);
}

void a_sprite_addFrame(SpriteFrames* const s, Sprite* const f)
{
    Sprite** const tempFrames = s->frames;
    s->frames = malloc(++(s->num) * sizeof(Sprite*));

    for(int i = s->num - 1; i--; ) {
        s->frames[i] = tempFrames[i];
    }

    s->frames[s->num - 1] = f;
    free(tempFrames);
}

static void setSheetValues(Sheet* const s)
{
    s->transparent = a_sprite_getPixel(s, s->w - 1, s->h - 1);
    s->limit = a_sprite_getPixel(s, s->w - 2, s->h - 1);
}
