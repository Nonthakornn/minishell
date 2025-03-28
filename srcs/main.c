#include "minishell.h"

static void	excute(t_process **head, char ***var)
{
	int		code;
	int		idx;
	char	*new_code;

	code = 0;
	pipe_process_lst(head);
	exec_heredoc(*head);
	if ((*head)->next)
	{
		fork_process(*head, var);
		wait_process(*head, &code);
	}
	else
		code = exec_process(*head, *head, var);
	idx = get_variable_index(*var, "?");
	if (idx < 0)
		*var = add_str_arr(*var, slice("$?=0", 0, 4));
	else
	{
		new_code = itoa(code);
		edit_str_arr(*var, idx, str_join("$?=", new_code));
		free(new_code);
	}
	free_process_and_redir(*head);
}

static t_process	*get_process(char *input, char **var)
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

static void	check_argv(int argc, char *argv[])
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

int	main(int argc, char *argv[], char *env[])
{
	int			code;
	char		**variable;
	char		*input;
	t_process	*proc;

	code = 0;
	check_argv(argc, argv);
	variable = get_parent_variable(env);
	while (1)
	{
		input = readline("minishell $> ");
		if (!input)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			break ;
		}
		proc = get_process(input, variable);
		if (!proc)
			continue ;
		excute(&proc, &variable);
		code = get_exit_code(variable);
	}
	free_str_arr(variable);
	rl_clear_history();
	return (code);
}
