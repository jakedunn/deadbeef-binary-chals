/*
 * How do you set environment variables?
 *
 * When you've popped the shell, get the flag by running
 * `cat /flags/0x03`.
 */

#include <stdio.h>
#include <stdlib.h>

int
main()
{
        int (*ret)();

        if (getenv("DEADBEEF") == NULL) {
                printf("DEADBEEF is not set! Exiting\n");
                exit(1);
        }

        ret = getenv("DEADBEEF");
        ret();
}
