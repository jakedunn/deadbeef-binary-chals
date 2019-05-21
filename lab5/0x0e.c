#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../lib/common.h"

#define BUFSIZE 256

/*
 * Can we exploit a recycled chunk?
 */

struct s1 {
	char buf[8];
};

struct s2 {
	int flag;
	char padding[50];
	void (*func)();
};

void
win(void)
{
	print_flag("/flags/0x0e");
}

int
main(int argc, char *argv[])
{
	struct s1 *p1;
	struct s2 *p2;

	if (argc < 2)
		errx(1, "Argument required");

	p1 = malloc(BUFSIZE);
	strcpy(p1->buf, argv[1]);
	free(p1);

	p2 = malloc(BUFSIZE);
	if (p2->flag == 0xcafebabe && p2->func != NULL)
		p2->func();
	free(p2);

	return 0;
}
