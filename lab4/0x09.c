/*
 * The flag is in the heap somewhere. 
 * The address to the flag is on the stack.
 *
 * Leak some of the stack and look for a "stack-like" address.
 * (hint: stack addresses usually start with 0xff, heap 0x0804)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main(int argc, char** argv)
{
	if (argc != 2) {
		puts("Argument required");
		exit(1);
	}

	char *pass = malloc(14);
	strcpy(pass, "XXXXXXX"); // Not the real string, you'll have to find it

	printf(argv[1]);
}
