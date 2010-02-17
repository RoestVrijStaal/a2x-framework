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

#ifndef A2X_PACK_TYPES_H
#define A2X_PACK_TYPES_H

#define a_stringify(s)  a__stringify(s)
#define a__stringify(s) #s

typedef struct Point {
    int x;
    int y;
} Point;

typedef struct Dim {
    int w;
    int h;
} Dim;

typedef struct Span {
    int x1;
    int x2;
} Span;

typedef struct Rect {
    int x;
    int y;
    int w;
    int h;
} Rect;

#endif // A2X_PACK_TYPES_H
