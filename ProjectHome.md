a2x is a C framework I wrote to help me write my games faster and easier. It supports desktop Linux, GP2X F-100/200, GP2X Wiz, and Caanoo.

## Example main.c ##
```
#include <a2x.h>

void a2x(void)
{
    a2x_set("title", "New App");
    a2x_set("version", "0.1");
    a2x_set("author", "You");
    a2x_set("window", "no");
    a2x_set("quiet", "yes");
}

void Main(void)
{
    printf("Code me!\n");
}
```

Documentation is yet to be written.