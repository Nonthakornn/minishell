#include "minishell.h"

t_process	*get_process(char *input, char **var)
{
	t_token		*tokens;
	t_process	*proc;

	add_history(input);
	if (input[0] == '\0')
	{
		free(input);
		return (NULL);
	}
	tokens = tokenize(input);
	free(input);
	if (!tokens)
		return (NULL);
	if (!process_token(&tokens, var))
		return (NULL);
	proc = syntax(tokens);
	return (proc);
}

static void	set_for_free(t_process *head, char **var)
{
	set_head(head);
	set_var(var);
}

void	excute(t_process **head, char ***var)
{
	int		code;

	code = 0;
	pipe_process_lst(head);
	set_for_free(*head, *var);
	exec_heredoc(*head);
	if (g_signal > 0)
	{
		close_pipe(*head);
		free_process_and_redir(*head);
		return ;
	}
	setup_signal_parent();
	if ((*head)->next)
	{
		fork_process(*head, var);
		wait_process(*head, &code);
	}
	else
		code = exec_process(*head, *head, var);
	if (g_signal == 0)
		g_signal = code;
	free_process_and_redir(*head);
}

void	check_argv(int argc, char *argv[])
{
	if (argc > 1)
	{
		if (is_dir(argv[1]))
		{
			put_strerror(argv[1], "Is a directory");
			exit(126);
		}
		if (access(argv[1], F_OK) == -1)
		{
			put_strerror(argv[1], "No such file or directory");
			exit(127);
		}
		if (access(argv[1], X_OK) == -1)
		{
			put_strerror(argv[1], "Permission denied");
			exit(126);
		}
		if (is_equal(argv[1], "./minishell") || is_equal(argv[1], "minishell"))
		{
			put_strerror(argv[1], "cannot execute binary file");
			exit(126);
		}
	}
}
