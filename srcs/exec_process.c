#include "minishell.h"

static int	exec_process(t_process *head, t_process *process, char *env[])
{
	char	*exec_path;

	if (!(process->cmd) || !(process->cmd)[0])
	{
		display_error_no_command(" ");
		free_process_and_redir(head);
		return (127);
	}
	if (ft_strlen((process->cmd)[0]) == 1 && (process->cmd)[0][0] == '/')
	{
		display_error_path("/");
		free_process_and_redir(head);
		return (126);
	}
	exec_path = ft_get_path(env, (process->cmd)[0]);
	if (!exec_path)
	{
		free_process_and_redir(head);
		return (127);
	}
	execve(exec_path, process->cmd, env);
	free_process_and_redir(head);
	return (127);
}

void	fork_process(t_process *head, char *env[])
{
	t_process	*process;
	int			redir_result;

	process = head;
	while (process)
	{
		process->pid = fork();
		if (process->pid == 0)
		{
			redir_result = process_redirect(process);
			close_fd(head);
			if (redir_result != 0)
			{
				free_process_and_redir(head);
				exit(1);
			}
			exit(exec_process(head, process, env));
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
