#include "minishell.h"

// Non Main
// int main(void)
// {
	// t_redirect	*redir_node;
	// t_pipe		*pipes_node;

	//segment
	// char		*input;
	// char		**pipe_segments;
	// int			i;

	// redir_node = create_redir_lst(READ_FILE, "text.txt");
	// char *cmd1[] = {"cat", "-e", "echo", NULL};
	// char *cmd2[] = {"ls", "-la", NULL};

	// pipes_node = create_pipe_lst(cmd1, redir_node);
	// addback_pipe_lst(&pipes_node, create_pipe_lst(cmd2, NULL));

	// display_pipe_lst(pipes_node);
	// free_pipe_and_redir(pipes_node);

	// while (1)
	// {
		// i = 0;
		// input = readline("minishell $> ");
		// if (!input)
		// 	break ;
		// add_history(input);
		// if (input[0] == '\0')
		// {
		// 	free(input);
		// 	continue;
		// }
		// pipes_node = NULL;
		// Split pipes into segment
		// pipe_segments = split_by_pipes(input);
		// display_process_segment(pipe_segments);

		// For each pipe segment
		// while (pipe_segments[i])
		// {
		// 	// Split segment into command and find redirections
		// 	// Example: "cat <input.txt" becomes cmd = {"cat", NULL}
		// 	// char **cmd = split_command(pipe_segments[i]);

		// 	// Example: "cat <input.txt >output.txt"
        //     // Creates redirect nodes and links them
		// 	/*
		// 	"cat >output.txt >>append.txt"
		// 	Creates:
		// 	redirects:
  		// 	type: WRITE_FILE
  		// 	value: "output.txt"
  		// 	next:
    	// 	type: APPEND_FILE
    	// 	value: "append.txt"
    	// 	next: NULL
		// 	*/
		// 	/*
		// 	if you find you create
		// 	t_redirect *redir = create_redir_lst(READ_FILE, "input.txt");
		// 	addback_redir_lst(&redir, create_redir_lst(WRITE_FILE, "output.txt"));
		// 	*/
		// 	// t_redirect *redir = find_redirections(pipe_segments[i]);
		// 	// // Create and link pipe node
		// 	// t_pipe *new_node = create_pipe_lst(cmd, redir);
		// 	// addback_pipe_lst(&pipes_node, new_node);
		// 	// i++;
		// }
// 			free(input);
// 	}

// 	rl_clear_history();
// 	return (EXIT_SUCCESS);
// }

// Tor Main

int main(int argc, char *argv[], char *env[])
{
	t_redirect	*redir_1;
	t_redirect	*redir_2;
	t_process	*process_1;
	t_process	*process_2;
	int			exit_code;

	if (argc > 1)
	{
		printf("%s %s\n", argv[1], env[0]);
	}

	char *cmd1[] = {"cat", NULL};
	redir_1 = create_redir_lst(READ_FILE, "text1.txt");
	addback_redir_lst(&redir_1, create_redir_lst(HERE_DOC, "end"));
	addback_redir_lst(&redir_1, create_redir_lst(HERE_DOC, "EOF"));
	// addback_redir_lst(&redir_1, create_redir_lst(WRITE_FILE, "out"));
	process_1 = create_process_lst(cmd1, redir_1);

	char *cmd2[] = {"cat", NULL};
	redir_2 = create_redir_lst(READ_FILE, "text.txt");
	// redir_2 = create_redir_lst(HERE_DOC, "EOF");
	// addback_redir_lst(&redir_2, create_redir_lst(HERE_DOC, "end"));
	// addback_redir_lst(&redir_2, create_redir_lst(READ_FILE, "text.txt"));
	addback_redir_lst(&redir_2, create_redir_lst(APPEND_FILE, "out1"));
	process_2 = create_process_lst(cmd2, redir_2);

	addback_process_lst(&process_1, process_2);
	pipe_process_lst(&process_1);

	exec_heredoc(process_1);
	fork_process(process_1, env);
	wait_process(process_1, &exit_code);
	free_process_and_redir(process_1);
	return (exit_code >> 8);
}

/*
1) cat <txt.txt >> out adfa
Command Structure Debug Output:
-----------------------------
cmd[0]: "cat"
cmd[1]: "adfa"
cmd[2]: NULL

redirects:
  type: READ_FILE
  value: "txt.txt"
  next: {
    type: APPEND_FILE
    value: "out"
    next: NULL
  }

next: NULL

2)ls <txt.txt >>out | ls

Command Structure Debug Output:
-----------------------------
[Command 1]
cmd[0]: "ls"
cmd[1]: NULL

redirects:
  type: READ_FILE
  value: "txt.txt"
  next: {
    type: APPEND_FILE
    value: "out"
    next: NULL
  }

next: {
    [Command 2]
    cmd[0]: "ls"
    cmd[1]: NULL
    redirects: NULL
    next: NULL
}
*/