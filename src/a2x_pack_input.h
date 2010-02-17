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

#ifndef A2X_PACK_INPUT_H
#define A2X_PACK_INPUT_H

#include <SDL/SDL.h>

#include "a2x_pack_collide.h"
#include "a2x_pack_fps.h"
#include "a2x_pack_list.h"
#include "a2x_pack_state.h"
#include "a2x_pack_str.h"
#include "a2x_pack_types.h"

typedef struct Button {
    char* name;
    int code;
    int pressed;
} Button;

typedef struct Touch {
    List* motion;
    int x;
    int y;
    int tap;
} Touch;

typedef struct Input {
    List* buttons;
    char* name;
    int working;
} Input;

typedef struct Inputs {
    List* buttons;
    Touch mouse;
    #if A_PLATFORM_GP2X || A_PLATFORM_WIZ
        SDL_Joystick* joystick;
    #endif
} Inputs;

extern void a__input_set(void);
extern void a__input_free(void);
extern void a__input_get(void);

extern Input* a_input_set(const char* const names);
extern void a_input_free(Input* const i);
extern int a_input_get(Input* const i);
extern void a_input_unpress(Input* const i);
extern int a_input_getUnpress(Input* const i);

#define a_input_name(i)    (i->name)
#define a_input_working(i) (i->working)

extern void a_input_waitFor(Input* const i);
extern int a_input_touchedPoint(const int x, const int y);
extern int a_input_touchedRect(const int x, const int y, const int w, const int h);

#endif // A2X_PACK_INPUT_H
