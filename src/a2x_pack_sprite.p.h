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

#ifndef A2X_PACK_SPRITE_PH
#define A2X_PACK_SPRITE_PH

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "a2x_pack_fix.p.h"
#include "a2x_pack_list.p.h"
#include "a2x_pack_screen.p.h"
#include "a2x_pack_types.p.h"

typedef struct Sheet Sheet;
typedef struct Sprite Sprite;
typedef struct SpriteAnimation SpriteAnimation;
typedef struct SpriteFrames SpriteFrames;

extern Sheet* a_sprite_sheetFromFile(const char* const path);
extern Sheet* a_sprite_sheetFromData(Pixel* data, const int w, const int h);
extern Sheet* a_sprite_sheetFromSheet(const Sheet* const sheet, const int x, const int y, const int w, const int h);
extern void a_sprite_freeSheet(Sheet* const s);

#define a_sprite_getPixel(s, x, y) (*((s)->data + (y) * (s)->w + (x)))

#define a_sprite_make(g, x, y, w, h) a_sprite_makeZoomed((g), (x), (y), (w), (h), 1)
extern Sprite* a_sprite_makeZoomed(const Sheet* const graphic, const int x, const int y, const int w, const int h, const int zoom);
extern Sprite* a_sprite_makeBlank(const int w, const int h);
extern void a_sprite_makeTransparent(Sprite* const s, const Sheet* const graphic);
extern void a_sprite_free(Sprite* const s);
extern int a_sprite_w(const Sprite* const s);
extern int a_sprite_h(const Sprite* const s);
extern Pixel* a_sprite_data(const Sprite* const s);

extern SpriteAnimation* a_sprite_makeAnimation(const int num, const int framesPerCycle);
extern void a_sprite_freeAnimation(SpriteAnimation* const s);
extern void a_sprite_addAnimation(SpriteAnimation* const s, Sprite* const sp);
extern Sprite* a_sprite_nextAnimation(SpriteAnimation* const s);
extern void a_sprite_changeAnimationDir(SpriteAnimation* const s, const int dir);
extern void a_sprite_flipAnimationDir(SpriteAnimation* const s);

extern SpriteFrames* a_sprite_makeFrames(void);
extern void a_sprite_freeFrames(SpriteFrames* const s);
extern void a_sprite_addFrame(SpriteFrames* const s, Sprite* const f);

#endif // A2X_PACK_SPRITE_PH