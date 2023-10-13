#include "samples/prototypes.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

/* initial allocation will be for min size, if not big enough, doubles
 * to 64, then 128, then 256, etc. as needed to accommodate the entire line
 * resize-as-you-go, doubling each time.
 */
#define MINIMUM_SIZE 32
#define arNULLd '\0'    //screw the all caps convention, this is a pun about the null TERMINATOR!

/*this function dynamically allocates enough memory on the heap to hold a line from a file or
  the standard input and then returns that line as a pointer to the string stored in heap memory */
char *read_line(FILE *fp) {
    //a variable to hold the size we are allocating/reallocating
    int bytes = MINIMUM_SIZE;
    //allocate the minimum size on the heap for the returned string
    char *line = malloc(bytes);
    assert(line != NULL);

    if(!fgets(line, bytes, fp)) {
        free(line);
        return NULL;
    }

    //if we haven't encountered \n, we need to enlarge the buffer
    while (strlen(line) == strcspn(line, "\n")) {
        bytes *= 2;    //double the number of bytes

        //reallocate and assert
        line = realloc(line, bytes);
        assert(line != NULL);

        //if it's not EOF, append the next chunk of the line onto *line
        if (fgets(line + strlen(line), bytes - strlen(line), fp) == NULL) {
            return line;
        }
    }

    line[strlen(line) - 1] = arNULLd;    //overwrite the endline character that fgets is using to terminate
    

    //return a pointer to the start of our heap allocated memory for the line
    return line;
}
