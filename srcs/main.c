#include "minishell.h"

int main(int ac, char *av[], char *env[])
{
	char		*input;
	t_token		*tokens;
	t_process	*proc; 
	int exit_code;

	while (1)
	{
		input = readline("minishell $> ");
		if (!input)
			break ;
		add_history(input);
		if (input[0] == '\0')
		{
			free(input);
			continue;
		}
		//! lexical 
		tokens = tokenize(input); //lexical
		// display_token_lst(tokens);

		//! syntax
		proc = syntax(tokens); //Syntax
		// display_process_lst(proc);

		//!execution
		pipe_process_lst(&proc);
		exec_heredoc(proc);
		fork_process(proc, env);
		wait_process(proc, &exit_code);

		//! clean up 
		free_token(tokens);
		free_process_and_redir(proc);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}


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
