#include "minishell.h"

static void	handle_exit_exec(int signum)
{
	t_process	**head;
	char		***var;
	int			*init_stdin;
	int			*init_stdout;

	head = get_h_proc();
	var = get_var();
	init_stdin = get_stdin();
	init_stdout = get_stdout();
	if (*init_stdin > 2)
		close(*init_stdin);
	if (*init_stdout > 2)
		close(*init_stdout);
	if (signum == SIGINT)
		terminate_process(*head, *var, 130);
	if (signum == SIGQUIT)
		terminate_process(*head, *var, 131);
}

void	setup_signal_exit_exec(t_process *head, char **var)
{
	set_h_proc(head);
	set_var(var);
	signal(SIGINT, handle_exit_exec);
	signal(SIGQUIT, handle_exit_exec);
}
