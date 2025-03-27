#include "minishell.h"

static void	command_is_dir(t_process *head, t_process *process, \
		char **var, int stdfd[2])
{
	put_strerror((process->cmd)[0], "Is a directory");
	recover_stdfd(stdfd);
	terminate_process(head, var, 126);
}

static void	no_command_execve(t_process *head, char **var, int stdfd[2])
{
	recover_stdfd(stdfd);
	terminate_process(head, var, 0);
}

static void	command_nopath(t_process *head, t_process *process, \
		char **var, int stdfd[2])
{
	char	*exec_path;

	exec_path = get_path(var, (process->cmd)[0]);
	if (!exec_path)
	{
		recover_stdfd(stdfd);
		terminate_process(head, var, 127);
	}
	execve(exec_path, process->cmd, var);
	recover_stdfd(stdfd);
	terminate_process(head, var, errno);
}

static void	command_withpath(t_process *head, t_process *process, \
		char **var, int stdfd[2])
{
	if (access((process->cmd)[0], F_OK) == -1)
	{
		put_strerror((process->cmd)[0], "No such file or directory");
		terminate_process(head, var, 127);
	}
	if (access((process->cmd)[0], X_OK) == -1)
	{
		put_strerror((process->cmd)[0], "Permission denied");
		terminate_process(head, var, 126);
	}
	execve((process->cmd)[0], process->cmd, var);
	recover_stdfd(stdfd);
	terminate_process(head, var, errno);
}

void	exec_execve(t_process *head, t_process *process, \
		char **var, int stdfd[2])
{
	if (!(process->cmd) || !(process->cmd)[0])
		no_command_execve(head, var, stdfd);
	if (is_include((process->cmd)[0], '/'))
	{
		if (is_dir((process->cmd)[0]))
			command_is_dir(head, process, var, stdfd);
		else
			command_withpath(head, process, var, stdfd);
	}
	else
		command_nopath(head, process, var, stdfd);
}
