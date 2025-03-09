#include "minishell.h"

int	exec_command(t_process *head, t_process *process, char **variable)
{
	char	*exec_path;

	if (!(process->cmd) || !(process->cmd)[0])
	{
		display_error_no_command(" ");
		free_end_process(head, variable);
		return (127);
	}
	if (ft_strlen((process->cmd)[0]) == 1 && (process->cmd)[0][0] == '/')
	{
		display_error_path("/");
		free_end_process(head, variable);
		return (126);
	}
	exec_path = get_path(variable, (process->cmd)[0]);
	if (!exec_path)
	{
		free_end_process(head, variable);
		return (127);
	}
	execve(exec_path, process->cmd, variable);
	free_end_process(head, variable);
	return (127);
}

void	exec_process(t_process *head, t_process *process, char **variable)
{
	int	redir_result;

	redir_result = process_redirect(process);
	close_fd(head);
	if (redir_result != 0)
	{
		free_end_process(head, variable);
		exit(1);
	}
	if (is_equal("env", (process->cmd)[0]))
	{
		exit(exec_env(head, process, variable));
	}
	exit(exec_command(head, process, variable));
}

void	fork_process(t_process *head, char **variable)
{
	t_process	*process;

	process = head;
	while (process)
	{
		process->pid = fork();
		if (process->pid == 0)
		{
			variable = get_child_variable(variable);
			exec_process(head, process, variable);
		}
		process = process->next;
	}
}

void	wait_process(t_process *head, int *exit_code)
{
	close_fd(head);
	while (head)
	{
		if (head->pid > 0)
		{
			if (head->next)
				waitpid(head->pid, NULL, 0);
			else
				waitpid(head->pid, exit_code, 0);
		}
		head = head->next;
	}
}
