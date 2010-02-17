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

#ifndef A2X_APP_SETTINGS
#define A2X_APP_SETTINGS

#include "a2x_pack_str.h"

typedef struct A2xSettings {
    String64 title;
    String64 version;
    String64 author;
    String64 compiled;
    String64 conf;
    int quiet;
    int window;
    int tool;
    int gp2xMenu;
    int mhz;
    int width;
    int height;
    int fps;
    int trackFps;
    int sound;
    int musicScale;
    int sfxScale;
    int trackMouse;
    int fakeScreen;
    int fixWizTear;
} A2xSettings;

extern A2xSettings a2xSet;

extern void a2x(void);
extern void a2x_defaults(void);
extern void a2x_set(const char* const var, const char* const val);

#endif // A2X_APP_SETTINGS
