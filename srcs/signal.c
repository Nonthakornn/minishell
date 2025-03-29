#include "minishell.h"

//CTRL-C
void handle_sigint(int signum)
{
	(void)signum;
	print_str(1, "Receive Signal: Ctrl-C");
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void handle_sigquit(int signum)
{
	(void)signum;
}

void	setup_signal(void)
{
	print_str(1, "Setup Signal");
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
