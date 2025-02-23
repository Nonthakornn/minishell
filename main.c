#include "minishell.h"

int main()
{
	// char	*input;
	t_redirect	*redir_node;
	t_pipe		*pipes_node;

	redir_node = create_redir_lst(READ_FILE, "text.txt");
	char *cmd1[] = {"cat", "file.txt", NULL};
	char *cmd2[] = {"ls", "-la", NULL};

	pipes_node = create_pipe_lst(cmd1, redir_node);
	addback_pipe_lst(&pipes_node, create_pipe_lst(cmd2, NULL));

	display_pipe_lst(pipes_node);
	free_pipe_and_redir(pipes_node);
	// display_redir_lst(redirects);

	/*
	while (1)
	{
		input = readline("minishell $> ");
		if (!input)
			break ;
		add_history(input);
		// start parsing
		free(input);
	}
	rl_clear_history();
	*/

	//Split by pipes (|) to get each command segment.
	//For each command segment:
		//Identify the command (first word not part of redirection)
		//Find all redirections (< << > >>)
		//Collect remaining words as arguments
		//Link it to next command if there was a pipe
	//Debug Output Stage
	return (EXIT_SUCCESS);
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