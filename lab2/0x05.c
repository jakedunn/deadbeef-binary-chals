/*
 * Get your shellcode in memory somehow, and smash the stack to
 * get it to execute!
 *
 * Using a NOP sled will help, see
 * http://deadbeefsociety.org/nop.html
 *
 * You can use an environment variable or the stack
 * to store your shellcode.
 *
 * When you've popped a shell, grab the flag with
 * `cat /flags/0x05`.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
	char buffer[64];

	if (argc != 2) {
		printf("Usage: %s argument\n", argv[0]);
		exit(1);
	}

	printf("Hi, shall we play another game?\n");

	strcpy(buffer, argv[1]);

	printf("%s", buffer);
}
