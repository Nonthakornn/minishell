#include "minishell.h"

static int	is_buildin(char *cmd)
{
	if (is_equal("exit", cmd))
		return (1);
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

static int	run_buildin(t_process *process, char ***var, int std[2])
{
	if (is_equal("exit", (process->cmd)[0]))
		return (exec_exit(process, (*var), std));
	g_signal = 0;
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

static void	init_stdfd(int stdfd[2])
{
	stdfd[0] = dup(0);
	stdfd[1] = dup(1);
	set_stdin(stdfd[0]);
	set_stdout(stdfd[1]);
}

int	exec_process(t_process *head, t_process *process, char ***var)
{
	int	redir_result;
	int	exit_code;
	int	pid;
	int	stdfd[2];

	exit_code = 0;
	init_stdfd(stdfd);
	redir_result = process_redirect(process);
	close_pipe(head);
	if (redir_result != 0)
		return (recover_stdfd(stdfd), 1);
	if (is_buildin((process->cmd)[0]))
	{
		exit_code = run_buildin(process, var, stdfd);
		return (recover_stdfd(stdfd), exit_code);
	}
	g_signal = 0;
	pid = fork();
	if (pid == 0)
	{
		exec_execve(head, process, (*var), stdfd);
		exit (exit_code);
	}
	wait(&exit_code);
	return (recover_stdfd(stdfd), exit_code >> 8);
}
