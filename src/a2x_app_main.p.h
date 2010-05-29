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

#ifndef A2X_APP_MAIN_PH
#define A2X_APP_MAIN_PH

#ifndef A_PLATFORM_LINUXPC
    #define A_PLATFORM_LINUXPC 0
#endif

#ifndef A_PLATFORM_WINDOWS
    #define A_PLATFORM_WINDOWS 0
#endif

#ifndef A_PLATFORM_WIZ
    #define A_PLATFORM_WIZ 0
#endif

#ifndef A_PLATFORM_GP2X
    #define A_PLATFORM_GP2X 0
#endif

#ifndef A_PLATFORM_PANDORA
    #define A_PLATFORM_PANDORA 0
#endif

#ifndef A_PLATFORM_GP32
    #define A_PLATFORM_GP32 0
#endif

#ifndef A_PLATFORM_LINUX
    #if A_PLATFORM_LINUXPC || A_PLATFORM_GP2X || A_PLATFORM_WIZ || A_PLATFORM_PANDORA
        #define A_PLATFORM_LINUX 1
    #else
        #define A_PLATFORM_LINUX 0
    #endif
#endif

#include <stdlib.h>
#include <stdio.h>

#include "a2x_app_settings.p.h"

extern int a_argsNum;
extern char** a_args;

extern void Main(void);

#endif // A2X_APP_MAIN_PH
