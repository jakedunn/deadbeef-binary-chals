#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * Overflow or underflow?
 */

int
what(void)
{
	fprintf(stderr, "huh?\n");
}


int
main(int argc, char *argv[])
{
	char *a[] = { "1. Thing One", "2. Thing Two", "3. Thing Three", NULL };
	char buf[64];
	char *e;
	int i, c, thing;
	void (*who)();
	who = what;

	for (c = 0, i = 0; a[i] != NULL; i++) {
		printf("%s\n", a[i]);
		c++;
	}

	fprintf(stderr, "Pick thing: ");
	scanf("%64s", buf);
	buf[63] = '\0';
	thing = atoi(buf);

	if (thing > c) {
		fprintf(stderr, ":o\n");
		return 0;
	}

	fprintf(stderr, "Copying $DEADBEEF to Thing %d\n", thing);
	e = getenv("DEADBEEF");

	if (e == NULL) {
		fprintf(stderr, ":O\n");
		return 0;
	}

	printf("%p\n", &who);
	memcpy(&a[thing], e, 4);
	who();
	return 0;
}
