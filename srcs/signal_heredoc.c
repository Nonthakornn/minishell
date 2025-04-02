#include "minishell.h"

void	handle_stop(int signum)
{
	(void)		signum;
	t_process	**head;
	char		***var;
	int			*hdin;
	int			*hdout;
	int			**hdpipe;

	write(1, "\n", 1);
	head = get_head();
	var = get_var();
	hdin = get_hdin();
	hdout = get_hdout();
	hdpipe = get_hdpipe();
	close_pipe(*head);
	close(*hdin);
	close(*hdout);
	free(*hdpipe);
	free_process_and_redir(*head);
	free_str_arr(*var);
	exit(130);
}

void	setup_signal_heredoc()
{
	signal(SIGINT, handle_stop);
	signal(SIGQUIT, SIG_IGN);
}


