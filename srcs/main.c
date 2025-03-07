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


// int main(int ac, char *av[], char *env[])
// {
// 	(void)av;
// 	(void)ac;
// 	t_redirect *redir_1;
// 	t_redirect *redir_2;
// 	t_process *process_1;
// 	t_process *process_2;
// 	int exit_code;

// 	char *cmd1[] = {"cat", NULL};
// 	redir_1 = create_redir_lst(READ_FILE, "text1.txt");
// 	addback_redir_lst(&redir_1, create_redir_lst(HERE_DOC, "end"));
// 	addback_redir_lst(&redir_1, create_redir_lst(HERE_DOC, "EOF"));
// 	// addback_redir_lst(&redir_1, create_redir_lst(WRITE_FILE, "out"));
// 	process_1 = create_process_lst(cmd1, redir_1);

// 	char *cmd2[] = {"cat", NULL};
// 	redir_2 = create_redir_lst(READ_FILE, "text.txt");
// 	// redir_2 = create_redir_lst(HERE_DOC, "EOF");
// 	// addback_redir_lst(&redir_2, create_redir_lst(HERE_DOC, "end"));
// 	// addback_redir_lst(&redir_2, create_redir_lst(READ_FILE, "text.txt"));
// 	addback_redir_lst(&redir_2, create_redir_lst(APPEND_FILE, "out1"));
// 	process_2 = create_process_lst(cmd2, redir_2);

// 	addback_process_lst(&process_1, process_2);
// 	pipe_process_lst(&process_1);

// 	exec_heredoc(process_1);
// 	fork_process(process_1, env);
// 	wait_process(process_1, &exit_code);
// 	free_process_and_redir(process_1);
// 	return (exit_code >> 8);

// }

int main(int ac, char *av[], char *env[])
{
	(void)av;
	(void)ac;
	(void)env;
	char	**str_arr;

	str_arr = NULL;
	print_str_array(str_arr);
	printf("---------------\n");
	str_arr = push_str_arr(str_arr, ft_slice("test='helllo'", 0, ft_strlen("test='helllo'")));
	// print_str_array(str_arr);
	free_str_arr(str_arr);
}