#include "minishell.h"

static void	interrupt_prompt(int signum)
{
	(void)signum;
	g_signal = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_signal_prompt(void)
{
	signal(SIGINT, interrupt_prompt);
	signal(SIGQUIT, SIG_IGN);
}

static void	interrupt_execute(int signum)
{
	(void)signum;
	if (signum == SIGINT)
	{
		write(2, "\n", 1);
		g_signal = 130;
	}
}

static void	quit_execute(int signum)
{
	(void)signum;
	print_str(2, "Quit (core dumped)");
	g_signal = 131;
}

void	setup_signal_execute(void)
{
	signal(SIGINT, interrupt_execute);
	signal(SIGQUIT, quit_execute);
}
