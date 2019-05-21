#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 257
/*
 * Most vulnerabilites in modern programs don't give us
 * an arbritrary length to overwrite.
 * 
 * Can we still exploit a program if we can only partially
 * overwrite the saved EBP?
 *
 * Remember, EBP becomes ESP when the function returns.
 * If we can control EBP, we can change where ESP will point to.
 * and create a fake stack frame.
 * Where is the 'ret addr' in relation to our new stackframe?

 * You may want to read this paper:
 * http://phrack.org/issues/55/8.html
 *
 * --------------
 * | GDB Tricks |
 * --------------
 * "print $ebp" will tell you what address EBP contains
 * "x/x $ebp" will examine the memory that EBP is pointing to
 */

void
vuln(char *s)
{
	char buf[255];

	strncpy(buf, s, MAXSIZE);
}

int
main(int argc, char *argv[])
{
	if (argc < 2)
		errx(1, "Argument required\n");

	vuln(argv[1]);
}
