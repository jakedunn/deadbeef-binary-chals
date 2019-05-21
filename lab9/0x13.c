#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
Stack and heap are marked non-executable.
Remember ret2libc?
There are many ways to get code execution.
ROP for bonus points.
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

#define USER "Thomas"
#define PASS "no_spoon"

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
	int i;
	char tmp[64];
	unsigned int err_len;
	void *funcptr = cmd_help;
	unsigned char err_msg[64];
	unsigned int *blocked[] = { (void *)system, NULL }; 

	err_len = strlen(buf) + 27;
	memset(err_msg, '\0', 64);
	snprintf(
		err_msg,
		sizeof(err_msg) - 1,
		"Error: %s\nCommand not found.\n",
		buf
	);
	
	memset(tmp, '\0', sizeof(tmp));
	for (i = 0; buf[i] != '\n'; i++)
		tmp[i] = buf[i];
	stripnl(tmp);

	if (!strcmp(tmp, "gimme"))
		funcptr = cmd_lookup;
	else if (!strcmp(tmp, "exit"))
		funcptr = cmd_exit;
	else if (!strcmp(tmp, "help")) {
		funcptr = cmd_help;
	} else {
		// no more fmt str bug.. take that, russian hackers
		for (i = 0; i < err_len; i++) {
			putchar(err_msg[i]);
		}
	}

	// Advanced Threat Detection
	for (i = 0; blocked[i] != (unsigned int *)NULL; i++) {
		if (funcptr == blocked[i]) {
			fprintf(stdout, "SNEAKY!\n");
			exit(0);
		}
	}

	return funcptr;
}

int
main(int argc, char *argv[])
{
	int i, in, out;
	unsigned char buf[256];
	unsigned char login_msg[64*1024];
	char *user, *pass;
	void (*cmd_fp)();

	fprintf(stdout, "%s", intro);
	fprintf(stdout, "%s", prompt_user);
	fflush(stdout);

	while (read(STDIN_FILENO, buf, 256) > 0) {
		switch (state) {
			case SM_USER:
				stripnl(buf);
				user = strdup(buf);
				state = SM_PASS;
				fprintf(stdout, "%s", prompt_pass);
				fflush(stdout);
				break;
			case SM_PASS:
				stripnl(buf);
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

