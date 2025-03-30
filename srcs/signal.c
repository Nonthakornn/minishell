#include "minishell.h"

//CTRL-C
void handle_sigint(int signum)
{
	(void)signum;
	g_signal = 1;
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
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

// void handle_sigint_heredoc(int signum)
// {
// 	if (signum == SIGINT)
// 		g_signal = 1;
// }

// void handle_sigint_fork(int signum)
// {
// 	if (signum == SIGINT)
// 	{
// 		print_str(1, "2");
// 		g_signal = 1;
// 	}
// 	if (signum == SIGQUIT)
// 	{
// 		print_str(1, "2");
// 		g_signal = 2;
// 		print_str(2, "Quit (core dump)");
// 		kill(0, SIGINT);
// 	}
// }
// void	setup_signal_heredoc(void)
// {
// 	signal(SIGINT, handle_sigint_heredoc);
// 	signal(SIGQUIT, SIG_IGN);
// }

// void	setup_signal_fork()
// {
// 	signal(SIGQUIT, SIG_DFL);
// 	// enable_ctrl_backslash(proc);
// 	signal(SIGINT, handle_sigint_fork);
// 	signal(SIGQUIT, handle_sigint_fork);
// }

// void			reset_signal(void)
// {
// 	signal(SIGINT, SIG_DFL);
// 	signal(SIGQUIT, SIG_DFL);
// }