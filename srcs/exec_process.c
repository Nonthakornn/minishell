#include "minishell.h"

void	exec_execve(t_process *head, t_process *process, char **var, int stdfd[2])
{
	char	*exec_path;


	if (!(process->cmd) || !(process->cmd)[0])
	{
		recover_stdfd(stdfd);
		terminate_process(head, var, 0);
	}
	if (ft_strlen((process->cmd)[0]) == 1 && (process->cmd)[0][0] == '/')
	{
		error_path("/");
		recover_stdfd(stdfd);
		terminate_process(head, var, 126);
	}
	exec_path = get_path(var, (process->cmd)[0]);
	if (!exec_path)
	{
		recover_stdfd(stdfd);
		terminate_process(head, var, 127);
	}
	close(stdfd[0]);
	close(stdfd[1]);
	execve(exec_path, process->cmd, var);
	terminate_process(head, var, 127);
}

int	is_buildin(char *cmd)
{
	if (is_equal("echo", cmd))
		return (1);
	if (is_equal("env", cmd))
		return (1);
	if (is_equal("unset", cmd))
		return (1);
	if (is_equal("export", cmd))
		return (1);
	if (is_equal("pwd", cmd))
		return (1);
	if (is_equal("cd", cmd))
		return (1);
	return (0);
}

int	run_buildin(t_process *process, char ***var)
{
	if (is_equal("echo", (process->cmd)[0]))
		return (exec_echo(process, (*var)));
	if (is_equal("env", (process->cmd)[0]))
		return (exec_env(process, (*var)));
	if (is_equal("unset", (process->cmd)[0]))
		return (exec_unset(process, var));
	if (is_equal("export", (process->cmd)[0]))
		return (exec_export(process, var));
	if (is_equal("pwd", (process->cmd)[0]))
		return (exec_pwd(process, var));
	if (is_equal("cd", (process->cmd)[0]))
		return (exec_cd(process, var));
	return (0);
}

void	recover_stdfd(int stdfd[2])
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	dup2(stdfd[0], STDIN_FILENO);
	dup2(stdfd[1], STDOUT_FILENO);
	close(stdfd[0]);
	close(stdfd[1]);
}

int	exec_process(t_process *head, t_process *process, char ***var)
{
	int	redir_result;
	int	exit_code;
	int	pid;
	int	stdfd[2];

	stdfd[0] = dup(0);
	stdfd[1] = dup(1);
	redir_result = process_redirect(process);
	close_pipe(head);
	if (redir_result != 0)
		return (recover_stdfd(stdfd), 1);
	if (is_buildin((process->cmd)[0]))
	{
		exit_code = run_buildin(process, var);
		return (recover_stdfd(stdfd), exit_code);
	}
	pid = fork();
	if (pid == 0)
		exec_execve(head, process, (*var), stdfd);
	wait(&exit_code);
	return (recover_stdfd(stdfd), exit_code >> 8);
}
