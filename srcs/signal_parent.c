#include "minishell.h"

static void	new_prompt(int signum)
{
	(void)signum;
	g_signal = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_signal()
{
	signal(SIGINT, new_prompt);
	signal(SIGQUIT, SIG_IGN);
}

static void	handle_parent(int signum)
{
	if (signum == SIGINT)
	{
		write(2, "\n", 1);
		g_signal = 130;
	}
	if (signum == SIGQUIT)
	{
		print_str(2, "Quit (core dumped)");
		g_signal = 131;
	}
}

void	setup_signal_parent()
{
	signal(SIGINT, handle_parent);
	signal(SIGQUIT, handle_parent);
}
