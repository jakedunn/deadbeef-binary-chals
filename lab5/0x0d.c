#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/common.h"

/*
 * In this level you have two arbritrary writes.
 *
 * One write controls the destination of the other.
 */

struct data {
	int priority;
	char *name;
};

void
lose(void)
{
	printf("Try again\n");
}

void
win(void)
{
	print_flag("/flags/0x0d");
}

void (*func)() = lose;

int
main(int argc, char **argv)
{
	struct data *d1, *d2;

	if (argc < 3)
		errx(1, "2 arguments required");

	d1 = malloc(sizeof(struct data));
	d1->priority = 1;
	d1->name = malloc(8);

	d2 = malloc(sizeof(struct data));
	d2->priority = 2;
	d2->name = malloc(8);

	strcpy(d1->name, argv[1]);
	strcpy(d2->name, argv[2]);

	func();
}
