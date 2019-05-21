/*
 * The stack has a saved instruction pointer so it
 * knows where to continue execution after the
 * function returns.
 *
 * What would happen if you overwrote that?
 *
 */

#include <stdio.h>
#include "../lib/common.h"

void
win(void)
{
	print_flag("/flags/0x04");
}

int
main()
{
	char buffer[64];

	printf("Shall we play a game?\n");

	gets(buffer);
}
