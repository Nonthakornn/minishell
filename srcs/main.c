#include "minishell.h"

// int main(void)
// {
// 	char		*input;
// 	t_token		*tokens;
// 	// t_process	*proc; 

// 	while (1)
// 	{
// 		input = readline("minishell $> ");
// 		if (!input)
// 			break ;
// 		add_history(input);
// 		if (input[0] == '\0')
// 		{
// 			free(input);
// 			continue;
// 		}
// 		//TODO
// 		tokens = tokenize(input); //lexical

// 		//! Debug: Display tokens
// 		display_token_lst(tokens);

// 		proc = parse(tokens); //Syntax

// 		//! Debug: Display process
// 		//display_process_lst(proc)

// 		//TODO Clean up
// 	}
// 	rl_clear_history();
// 	return (EXIT_SUCCESS);
// }

int main(int ac, char *av[], char *env[])
{
	(void)av;
	(void)ac;
	t_redirect *redir_1;
	// t_redirect *redir_2;
	t_process *process_1;
	// t_process *process_2;
	int exit_code = 0;
	char	**variable;

	variable = get_parent_variable(env);
	variable = add_str_arr(variable, slice("$a=", 0, ft_strlen("$a=")));

	char *cmd1[] = {"export", "b=",NULL};
	redir_1 = create_redir_lst(WRITE_FILE, "gen_export");
	// addback_redir_lst(&redir_1, create_redir_lst(HERE_DOC, "EOF"));
	// addback_redir_lst(&redir_1, create_redir_lst(WRITE_FILE, "out"));
	process_1 = create_process_lst(cmd1, redir_1);

	// char *cmd2[] = {"env", NULL};
	// redir_2 = create_redir_lst(READ_FILE, "text.txt");
	// redir_2 = create_redir_lst(HERE_DOC, "EOF");
	// redir_2 = create_redir_lst(WRITE_FILE, "test_env");
	// addback_redir_lst(&redir_2, create_redir_lst(HERE_DOC, "end"));
	// addback_redir_lst(&redir_2, create_redir_lst(READ_FILE, "text.txt"));
	// addback_redir_lst(&redir_2, create_redir_lst(WRITE_FILE, "test_env"));
	// process_2 = create_process_lst(cmd2, NULL);

	// addback_process_lst(&process_1, process_2);
	pipe_process_lst(&process_1);
	exec_heredoc(process_1);
	if (!(process_1->next))
		exit_code = exec_process(process_1, process_1, &variable) << 8;
	else
	{
		fork_process(process_1, &variable);
		wait_process(process_1, &exit_code);
		free_process_and_redir(process_1);
	}
	print_str_array(variable);
	free_str_arr(variable);
	return (exit_code >> 8);
}

// int	main()
// {
// 	char	**variable;

// 	variable = malloc(sizeof(char *) * 3);
// 	variable[0] = slice("$a=1234", 0, ft_strlen("$a=1234"));
// 	variable[1] = slice("b=1234", 0, ft_strlen("b=1234"));
// 	variable[2] = NULL;


// 	printf("%d\n", get_variable_index(variable, "a"));
// 	free_str_arr(variable);
// }
