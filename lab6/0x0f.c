#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../lib/common.h"

/*
 * This programmer didn't check to see if size could be
 * overflowed.
 *
 * What can we do with that?
 * 
 * Get the win function to run, and cat your flag at:
 * "/flags/0x0f"
 */

struct node {
        char buf[2048];
};

struct exec {
	int priority;
        char buf[500];
	void (*func)();
};

void
lose(void)
{
	printf("Try again\n");
}

int
main(int argc, char *argv[])
{
        struct node *p;
        struct exec *f;
        unsigned int size, n;
        int i;

	if (argc < 3)
		errx(1, "Usage: %s [int] [str]", argv[0]);

        n = atoi(argv[1]);
        size = n * sizeof(struct node);
        p = malloc(size);

        f = malloc(sizeof(struct exec));
	f->priority = 0;
	f->func = lose;

        for (i = 0; i < n; i++) {
                strncpy(p[i].buf, argv[2], 2000);
                if (f->priority)
                        f->func();
        }

        return 0;
}
