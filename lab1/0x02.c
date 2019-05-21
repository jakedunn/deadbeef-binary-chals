#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/common.h"

/*
 * Is gets safe? (man page)
 *
 * How can you find the memory address of a function?
 *
 * You can use a file as input
 * ./program < input.txt
 * In GDB:
 * gdb> run params .. < input.txt
 *
 * `objdump -d` might also be useful
 */
void
lose(void)
{
	printf("Nope, try again\n");
}

void
win(void)
{
	print_flag("/flags/0x02");
}

int
main(int argc, char *argv[])
{
	void (*fp)(void);
	char buf[20];

	fp = &lose;

	printf("What is your name?\n");

	gets(buf);

	printf("Hello %s, are you a winner?\n", buf);
	printf("  ... jumping to 0x%08x ...\n", fp);

	fp();
}
