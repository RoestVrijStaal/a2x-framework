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

#include "a2x_pack_state.p.h"
#include "a2x_pack_state.v.h"

int a_state_unchanged;

static StateRunner a__state = NULL;

void a_state_go(StateRunner s)
{
    a__state = s;
    a_state_unchanged = 0;
}

void a__state_run(void)
{
    while(a__state) {
        a_state_unchanged = 1;
        a__state();
    }
}
