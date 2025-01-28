#include <stdio.h>
#include "markings.h"

extern void startup_print() {
    printf("%s v%f %s\n", NAME, VERSION, VERSION_MODE);
}
