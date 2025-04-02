#include "minishell.h"

int	*get_sig_code(void)
{
	static int	sig_code = 0;

	return (&sig_code);
}

void	set_sig_code(int code)
{
	int	*sig_code;

	sig_code = get_sig_code();
	*sig_code = code;
}

static void	handle_child(int signum)
{
	t_process	**head;
	char		***var;
	int			*stdin_fd;
	int			*stdout_fd;

	head = get_head();
	var = get_var();
	stdin_fd = get_stdin();
	stdout_fd = get_stdout();
	if (*stdin_fd > 2)
		close(*stdin_fd);
	if (*stdout_fd > 2)
		close(*stdout_fd);
	if (signum == SIGINT)
		terminate_process(*head, *var, 130);
	if (signum == SIGQUIT)
		terminate_process(*head, *var, 131);
}

void	setup_signal_child(t_process *head, char **var)
{
	set_head(head);
	set_var(var);
	signal(SIGINT, handle_child);
	signal(SIGQUIT, handle_child);
}
