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

#include "a2x_pack_pixel.p.h"
#include "a2x_pack_pixel.v.h"

void a_pixel_putAlpha(const int x, const int y, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a)
{
    Pixel* const dst = a_pixels + y * a_width + x;
    a_pixel__putAlpha(dst, r, g, b, a);
}

void a_pixel_put25(const int x, const int y, const uint8_t r, const uint8_t g, const uint8_t b)
{
    Pixel* const dst = a_pixels + y * a_width + x;
    a_pixel__put25(dst, r, g, b);
}

void a_pixel_put50(const int x, const int y, const uint8_t r, const uint8_t g, const uint8_t b)
{
    Pixel* const dst = a_pixels + y * a_width + x;
    a_pixel__put50(dst, r, g, b);
}

void a_pixel_put75(const int x, const int y, const uint8_t r, const uint8_t g, const uint8_t b)
{
    Pixel* const dst = a_pixels + y * a_width + x;
    a_pixel__put75(dst, r, g, b);
}
