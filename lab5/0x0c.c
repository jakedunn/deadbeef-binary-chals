#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/common.h"

struct data {
	char buf[64];
};

struct fp {
	int (*fp)();
};

void
win(void)
{
	print_flag("/flags/0x0c");
}

void
lose(void)
{
	printf("Try again.\n");
}

int
main(int argc, char **argv)
{
	struct data *d;
	struct fp *f;

	if (argc < 2)
		errx(1, "Argument required");

	d = malloc(sizeof(struct data));
	f = malloc(sizeof(struct fp));

	f->fp = lose;

	strcpy(d->buf, argv[1]);
	
	f->fp();
}
