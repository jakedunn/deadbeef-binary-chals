#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/common.h"

/*
 * Is x86 little endian or big endian?
 *
 * You can use python/perl to print hex, try:
 * `python -c 'print "\x41" * 10`
 * or
 * `perl -e 'print "\x41"x10'`
 */
int
main(int argc, char *argv[])
{
	int modified;
	char buffer[20];

	if (argc == 1)
		errx(1, "Argument required\n");

	modified = 0;

	strcpy(buffer, argv[1]);

	if (modified == 0xdeadbeef)
		print_flag("/flags/0x01");
	else
		printf("Try again, you got 0x%08x\n", modified);
}
