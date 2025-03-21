#include "minishell.h"

void	exec_execve(t_process *head, t_process *process, char **var)
{
	char	*exec_path;

	if (!(process->cmd) || !(process->cmd)[0])
		terminate_process(head, var, 0);
	if (ft_strlen((process->cmd)[0]) == 1 && (process->cmd)[0][0] == '/')
	{
		error_path("/");
		terminate_process(head, var, 126);
	}
	exec_path = get_path(var, (process->cmd)[0]);
	if (!exec_path)
		terminate_process(head, var, 127);
	execve(exec_path, process->cmd, var);
	terminate_process(head, var, 127);
}

int	exec_process(t_process *head, t_process *process, char ***variable)
{
	int	redir_result;
	int	exit_code;
	int	pid;

	redir_result = process_redirect(process);
	close_pipe(head);
	if (redir_result != 0)
		return (1);
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
		exec_execve(head, process, (*variable));
	wait(&exit_code);
	return (exit_code >> 8);
}
