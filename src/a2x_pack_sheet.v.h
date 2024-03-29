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

#ifndef A2X_PACK_SHEET_VH
#define A2X_PACK_SHEET_VH

#include "a2x_pack_sheet.p.h"

#include "a2x_pack_png.v.h"
#include "a2x_pack_screen.v.h"

struct Sheet {
    int w;
    int h;
    Pixel* data;
    Pixel transparent;
    Pixel limit;
    Pixel end;
};

#define DEFAULT_TRANSPARENT a_pixel_make(255, 0, 255)
#define DEFAULT_LIMIT       a_pixel_make(0, 255, 0)
#define DEFAULT_END         a_pixel_make(0, 255, 255)

#define a_sheet__getPixel(s, x, y) (*((s)->data + (y) * (s)->w + (x)))

#endif // A2X_PACK_SHEET_VH
