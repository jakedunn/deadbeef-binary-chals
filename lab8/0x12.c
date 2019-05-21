#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
No easy shell this time.. you'll need shellcode.
Where can you put it? How can you find the address?
You'll probably need to calculate another offset..
*/

enum { SM_START, SM_USER, SM_PASS, SM_AUTHED };
int state = SM_USER;
int admin_account = 0;
char intro[] =
	"************************************************\n"
	"* AUTHORIZED ACCESS ONLY. PLEASE AUTHENTICATE. \n*"
	"************************************************\n";
char prompt_user[] = "username: ";
char prompt_pass[] = "password: ";

struct cmd {
	int id;
	char *name;
};

#define USER "Elliot"
#define PASS "iwantedtosavetheworld"

void
stripnl(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\n' && buf[i] != '\r'; i++);
	buf[i] = '\0';
}

void cmd_lookup(const char *query)
{
	system("/usr/games/fortune | /usr/games/cowsay -d");
}
void cmd_exit(void)
{
	fprintf(stdout, "THANK YOU FOR USING THIS VERY IMPORTANT SOFTWARE\n");
	exit(0);
}

void
cmd_help(void)
{
	fprintf(stdout, "Available commands:\ngimme\nexit\nhelp\n");
}

int
authenticate(char *user, char *pass)
{
	if (!strcmp(user, USER) && !strcmp(pass, PASS))
		return 1;
	return 0;
}

void *
find_cmd(char *buf)
{
	char tmp[64];
	void *funcptr = cmd_help;

	strcpy(tmp, buf);
	if (!strcmp(tmp, "gimme"))
		funcptr = cmd_lookup;
	else if (!strcmp(tmp, "exit"))
		funcptr = cmd_exit;
	else if (!strcmp(tmp, "help")) {
		funcptr = cmd_help;
	} else {
		fprintf(stdout, "Error: ");
		fprintf(stdout, buf);
		fprintf(stdout, "\nCommand not found.\n");
	}

	return funcptr;
}

int
main(int argc, char *argv[])
{
	int i, in, out;
	unsigned char buf[256];
	unsigned char login_msg[256];
	char *user, *pass;
	void (*cmd_fp)();

	fprintf(stdout, "%s", intro);
	fprintf(stdout, "%s", prompt_user);
	fflush(stdout);

	while (read(STDIN_FILENO, buf, 256) > 0) {
		stripnl(buf);
		switch (state) {
			case SM_USER:
				user = strdup(buf);
				state = SM_PASS;
				fprintf(stdout, "%s", prompt_pass);
				fflush(stdout);
				break;
			case SM_PASS:
				pass = strdup(buf);
				if (authenticate(user, pass)) {
					fprintf(stdout, "Welcome %s.\n", user);
					fprintf(stdout, "> ");
					fflush(stdout);
					state = SM_AUTHED;
				} else {
					fprintf(stdout, "Authentication failed. GET OUT.\n");
					exit(0);
				}
				break;
			case SM_AUTHED:
				cmd_fp = find_cmd(buf);
				cmd_fp(buf);
				fprintf(stdout, "> ");
				fflush(stdout);
				break;
		}
	}
}

