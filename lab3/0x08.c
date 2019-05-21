/*
 * This level is the same as 0x05 from the last lab
 * but the stack is no longer executable.
 *
 * You will have to use ret2libc
 *
 * This paper may be useful:
 * http://shellblade.net/docs/ret2libc.pdf
 *
 * [-] Buffer overflow smashing EIP and jumping forward to shellcode
 *
 *			  dummy bytes
 *			  /
 * |------------------|---------|-----------------|
 * |	 SHELLCODE    |  AAAA	|    &shellcode   |
 * |------------------|---------|-----------------|
 *	   buffer      saved-EBP       RET
 *
 * [-] Buffer overflow doing return-to-libc and executing system function
 *
 *			  dummy bytes		  dummy bytes	  arg1 for system()
 *			 /			 /		 /
 * |------------------|---------|------------|------|------------------|
 * | buffer_fill_up   |  AAAA	|  &system   | BBBB |addr of "/bin/sh" |
 * |------------------|---------|------------|------|------------------|
 *	   buffer      saved-EBP      RET 
 *
 *
 * --------------
 * | GDB Tricks |
 * --------------
 * "print &system" will tell you where system is in libc
 * x/500s <addr> will help you locate strings in memory
 * 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
	char buffer[64];

	setreuid(geteuid(), geteuid());

	if (argc != 2) {
		printf("Usage: %s argument\n", argv[0]);
		exit(1);
	}

	strcpy(buffer, argv[1]);
}

