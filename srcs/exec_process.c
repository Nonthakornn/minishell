#include "minishell.h"

void	exec_command(t_process *head, t_process *process, char **variable)
{
	char	*exec_path;

	if (!(process->cmd) || !(process->cmd)[0])
	{
		free_process_and_redir(head);
		free_str_arr(variable);
		exit (0);
	}
	if (ft_strlen((process->cmd)[0]) == 1 && (process->cmd)[0][0] == '/')
	{
		error_path("/");
		free_process_and_redir(head);
		free_str_arr(variable);
		exit (126);
	}
	exec_path = get_path(variable, (process->cmd)[0]);
	if (!exec_path)
	{
		free_process_and_redir(head);
		free_str_arr(variable);
		exit (127);
	}
	execve(exec_path, process->cmd, variable);
	free_process_and_redir(head);
	free_str_arr(variable);
	exit (127);
}

int	exec_process(t_process *head, t_process *process, char ***variable)
{
	int	redir_result;
	int	exit_code;
	int	pid;

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
	if (is_equal("cd", (process->cmd)[0]))
		return (exec_cd(head, process, variable));
	pid = fork();
	if (pid == 0)
	{
		exec_command(head, process, (*variable));
	}
	wait(&exit_code);
	return (exit_code >> 8);
}

void	fork_process(t_process *head, char ***variable)
{
	t_process	*process;
	int			exit_code;

	process = head;
	while (process)
	{
		process->pid = fork();
		if (process->pid == 0)
		{
			exit_code = exec_process(head, process, variable);
			free_str_arr(*variable);
			exit(exit_code);
		}
		process = process->next;
	}
}

void	wait_process(t_process *head, int *exit_code)
{
	int		code;
	pid_t	last_pid;
	t_process	*temp;

	close_fd(head);
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
			*exit_code = code;
		}
		temp = temp->next;
	}
}

