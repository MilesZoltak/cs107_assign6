
//Practice environment for code
#include "samples/prototypes.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
    int d;
    char *s;
    s = "meat114";
    d = strtoul(s + 5, NULL, 10);
    printf("%d\n", d);
    return 0;
}
