#include "minishell.h"

void handle_sigint(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void handle_sigquit(int signum)
{
	printf("Receive sigquit %d\n", signum);
}

/*
SIGINT(2) - Ctrl-C
SIGQUIT(3) - Ctrl-\ 
Ctrl-D is not signal but it is EOF (send NULL)
extern volatile sig_atomic_t	g_signal;;
volatile sig_atomic_t	g_signal;
*/

int main()
{
	char *input;
	struct sigaction sa_int;
	sa_int.sa_handler = handle_sigint;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;
    sigaction(SIGINT, &sa_int, NULL);
	signal(SIGQUIT, SIG_IGN);

	// signal(SIGINT, handle_sigint);
	// signal(SIGQUIT, SIG_IGN);

	while (1)
	{
		input = readline("prompt> ");
		if (!input)
			break;
	}
	return (0);
}

/*
rl_on_new_line - Tell readline to start a new line
rl_replace_line - Clear the current input line
rl_redisplay - Redisplay prompt
signal,
sigaction
sigemptyset
sigaddset
kill
*/