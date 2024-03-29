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

#ifndef A2X_PACK_SCREEN_VH
#define A2X_PACK_SCREEN_VH

#include "a2x_pack_screen.p.h"

#include "a2x_app_settings.v.h"

#include "a2x_pack_draw.v.h"
#include "a2x_pack_pixel.v.h"
#include "a2x_pack_sound.v.h"
#include "a2x_pack_sprite.v.h"
#include "a2x_pack_str.v.h"
#include "a2x_pack_time.v.h"

extern void a_screen__set(void);
extern void a_screen__free(void);

#if A_PLATFORM_LINUXPC || A_PLATFORM_WINDOWS
    extern void a_screen__switchFull(void);
    extern void a_screen__doubleRes(void);
#endif

#endif // A2X_PACK_SCREEN_VH
