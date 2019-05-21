/*
 * Find the address of the flag. Then figure
 * out the stack offset to reach argv[1]. Put
 * in the address and write at the correct offset
 * Hint: you may need to massage the stack by stuffing
 * bytes at the start or end
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/common.h"

// what's the address of this?
int flag = 0;

int
main(int argc, char** argv)
{
	if (argc != 2)
		errx(1, "Argument required");

	printf(argv[1]);

	if (flag == 0x1337)
		print_flag("/flags/0x0b");
	else
		printf("Nope. Flag is %x\n", flag);
}
