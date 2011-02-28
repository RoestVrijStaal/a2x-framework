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

#include "a2x_pack_dir.v.h"

struct Dir {
    char* path;
    char* name;
    List* files;
    int num;
    char* current;
};

static int defaultFilter(const struct dirent* f);

Dir* a_dir_open(const char* const path)
{
    return a_dir_openFilter(path, defaultFilter);
}

Dir* a_dir_openFilter(const char* const path, int (*filter)(const struct dirent* f))
{
    struct dirent** dlist = NULL;
    const int numFiles = scandir(path, &dlist, filter, alphasort);

    Dir* const d = malloc(sizeof(Dir));

    d->path = a_str_dup(path);
    d->name = a_str_getSuffixLastFind(path, '/');
    d->files = a_list_set();
    d->num = a_math_max(0, numFiles);
    d->current = NULL;

    for(int i = d->num; i--; ) {
        char* const file = a_str_merge(3, path, "/", dlist[i]->d_name);
        a_list_addFirst(d->files, file);

        free(dlist[i]);
    }

    free(dlist);

    return d;
}

void a_dir_close(Dir* const d)
{
    free(d->path);
    free(d->name);
    a_list_freeContent(d->files);

    free(d);
}

bool a_dir_iterate(Dir* const d)
{
    if(a_list_iterate(d->files)) {
        d->current = a_list_current(d->files);
        return true;
    }

    return false;
}

const char* a_dir_current(const Dir* const d)
{
    return d->current;
}

const char* a_dir_path(const Dir* const d)
{
    return d->path;
}

const char* a_dir_name(const Dir* const d)
{
    return d->name;
}

int a_dir_num(const Dir* const d)
{
    return d->num;
}

int a_dir_exists(const char* const path)
{
    DIR* const d = opendir(path);

    if(d) {
        closedir(d);
        return 1;
    }

    return 0;
}

void a_dir_make(const char* const path)
{
    mkdir(path, S_IRWXU);
}

static int defaultFilter(const struct dirent* f)
{
    return strlen(f->d_name) > 0 && f->d_name[0] != '.';
}
