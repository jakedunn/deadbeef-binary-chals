#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/common.h"

/* Is strcpy safe? */
int
main(int argc, char *argv[])
{
	int flag;
	char buf[20];

	flag = 0;

	if (argc != 2) {
		fprintf(stderr, "usage: %s <password>\n", argv[0]);
		exit(1);
	}

	strcpy(buf, argv[1]);

        if (flag)
		print_flag("/flags/0x00");
	else
		printf("Access denied\n");
}

