#include "minishell.h"

void	setup_signal_heredoc()
{
	signal(SIGINT, 0);
	signal(SIGQUIT, SIG_IGN);
}


