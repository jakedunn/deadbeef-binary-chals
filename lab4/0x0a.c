/*
 * You will need your format string to print a certain
 * amount of bytes then write
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/common.h"

int
main(int argc, char** argv)
{
	if (argc != 2) {
		puts("Argument required");
		exit(1);
	}

	int flag = 0;
	printf(argv[1], &flag);

	if (flag == 0xdead) {
		print_flag("/flags/0x0a");
	}
}
