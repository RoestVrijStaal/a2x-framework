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

#include "a2x_pack_conf.v.h"

void a_conf__set(void)
{
    a_out("You can edit %s", a2x_str("conf"));

    FileReader* const f = a_file_makeReader(a2x_str("conf"));

    while(a_file_readLine(f)) {
        char* const s = a_str_trim(a_file_getLine(f));

        if(strlen(s) >= 2 && s[0] == '/' && s[1] == '/') {
            free(s);
            continue;
        }

        char* const a = a_str_getPrefixFirstFind(s, '=');
        char* const b = a_str_getSuffixFirstFind(s, '=');

        if(a && b) {
            char* const key = a_str_trim(a);
            char* const value = a_str_trim(b);

            a2x_set(key, value);

            free(key);
            free(value);
        }

        free(a);
        free(b);
        free(s);
    }

    a_file_freeReader(f);
}
