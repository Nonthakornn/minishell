#include "minishell.h"

int	exec_command(t_process *head, t_process *process, char **variable)
{
	char	*exec_path;

	if (!(process->cmd) || !(process->cmd)[0])
	{
		error_no_command(" ");
		free_process_and_redir(head);
		return (127);
	}
	if (ft_strlen((process->cmd)[0]) == 1 && (process->cmd)[0][0] == '/')
	{
		error_path("/");
		free_process_and_redir(head);
		return (126);
	}
	exec_path = get_path(variable, (process->cmd)[0]);
	if (!exec_path)
	{
		free_process_and_redir(head);
		return (127);
	}
	execve(exec_path, process->cmd, variable);
	free_process_and_redir(head);
	return (127);
}

int	exec_process(t_process *head, t_process *process, char ***variable)
{
	int	redir_result;

	redir_result = process_redirect(process);
	close_fd(head);
	if (redir_result != 0)
	{
		free_process_and_redir(head);
		return (1);
	}
	if (is_equal("env", (process->cmd)[0]))
		return (exec_env(head, process, (*variable)));
	if (is_equal("unset", (process->cmd)[0]))
		return (exec_unset(head, process, variable));
	if (is_equal("export", (process->cmd)[0]))
		return (exec_export(head, process, variable));
	if (is_equal("pwd", (process->cmd)[0]))
		return (exec_pwd(head, process, variable));
	return (exec_command(head, process, (*variable)));
}

void	fork_process(t_process *head, char ***variable)
{
	t_process	*process;
	char		**child_variable;
	int			exit_code;

	process = head;
	while (process)
	{
		process->pid = fork();
		if (process->pid == 0)
		{
			child_variable = get_child_variable((*variable));
			exit_code = exec_process(head, process, &child_variable);
			free_str_arr(child_variable);
			exit(exit_code);
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
