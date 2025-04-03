#include "minishell.h"

void	terminate_process(t_process *head, char **var, int code)
{
	free_process_and_redir(head);
	free_str_arr(var);
	exit(code);
}

void	fork_process(t_process *head, char ***var)
{
	t_process	*process;
	int			exit_code;

	process = head;
	while (process)
	{
		process->pid = fork();
		if (process->pid == 0)
		{
			setup_signal_exit_exec(head, *var);
			exit_code = exec_process(head, process, var);
			terminate_process(head, *var, exit_code);
		}
		process = process->next;
	}
}

void	wait_process(t_process *head, int *exit_code)
{
	int			code;
	pid_t		last_pid;
	t_process	*temp;

	close_pipe(head);
	temp = head;
	while (temp)
	{
		if (!temp->next)
		{
			last_pid = temp->pid;
		}
		temp = temp->next;
	}
	temp = head;
	while (temp)
	{
		if (wait(&code) == last_pid)
		{
			*exit_code = code >> 8;
		}
		temp = temp->next;
	}
}
