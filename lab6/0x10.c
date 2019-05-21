#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/queue.h>

/*
 * This game demonstrates what you can do if you
 * can corrupt an element in a data structure.
 *
 * The node list is a doubly linked list.
 *
 * What actually happens when you remove
 * an element from a doubly linked list? What can we do
 * if we control the "next" and "prev" pointers?
 *
 * You might find it easier to actually look at what
 * the assembly is doing when your program crashes
 * and look at the registers you control.
 *
 * The stack is executable, you can use an environment variable
 * with shellcode.
 *
 * When you have a shell, grab the flag with `cat /flags/0x10`
 *
 * Some GDB tricks you might find useful:
 *
 * (gdb) x/i $pc # what is the current instruction?
 * (gdb) disas # examine the assembly
 * (gdb) info registers # examine current register values
 * (gdb) print *(struct x *)0x41414141 # You can use GDB to cast a struct
 *
 * Remember - GDB and objdump -d use x86 AT&T/GAS Syntax for assembly.
 * Don't look at the wrong docsheet.
 */

struct node {
	char buf[256];

	LIST_ENTRY(node) nodes;
};

LIST_HEAD(NodeHead, node) head;

void
lose(void)
{
	printf("Try again\n");
}

void (*func)() = lose;

void
main(int argc, char **argv)
{
	struct node *x;
	x = malloc(sizeof(struct node));

	if (argc < 2)
		errx(1, "Argument required");

	LIST_INIT(&head);
	LIST_INSERT_HEAD(&head, x, nodes);

	strcpy(x->buf, argv[1]);

	LIST_REMOVE(x, nodes);

	func();
}
