#include "minishell.h"


//CTRL-C
static void new_prompt(int signum)
{
	(void)signum;
	g_signal = 1;
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


static void handle_mom(int signum)
{
	if (signum == SIGINT)
		write(2, "\n", 1);
	if (signum == SIGQUIT)
		write(2, "Quit (core dump)\n", 18);
	return ;
}

void	setup_signal_parent()
{
	signal(SIGINT, handle_mom);
	signal(SIGQUIT, handle_mom);
}

// void	setup_signal_parent()
// {
// 	signal(SIGINT, SIG_IGN);
// 	signal(SIGQUIT, SIG_IGN);
// }

void	setup_signal_child()
{
	signal(SIGINT, handle_child);
	signal(SIGQUIT, handle_child);
}

void handle_child(int signum)
{
	(void)signum;
	if (signum == SIGINT)
		write(2, "\n", 1);
	if (signum == SIGQUIT)
		write(2, "Quit (core dump)\n", 18);
	exit (130);
}

// static void change_status(int signum)
// {
// 	(void)signum;
// 	g_signal = 1;
// 	write(1, "\n", 1);
// }
