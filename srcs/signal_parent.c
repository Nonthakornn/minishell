#include "minishell.h"

static void	new_prompt(int signum)
{
	(void)signum;
	g_signal = 1;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_signal(void)
{
	signal(SIGINT, new_prompt);
	signal(SIGQUIT, SIG_IGN);
}

static void	handle_parent(int signum)
{
	if (signum == SIGINT)
	{
		write(2, "\n", 1);
		set_sig_code(130);
	}
	if (signum == SIGQUIT)
	{
		print_str(2, "Quit (core dumped)");
		set_sig_code(131);
	}
}

void	setup_signal_parent(void)
{
	signal(SIGINT, handle_parent);
	signal(SIGQUIT, handle_parent);
}
