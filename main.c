#include "minishell.h"

int main(int argc, char *argv[], char *env[])
{
	(void)argc;
	(void)argv;
	(void)env;

	ft_print_str(1, "Testing");
	//if readline reutrn NULL (Ctrl+D), break the loop.
	//Add line to history
	//Split by pipes (|) to get each command segment.
	//For each command segment:
		//Identify the command (first word not part of redirection)
		//Find all redirections (< << > >>)
		//Collect remaining words as arguments
		//Link it to next command if there was a pipe
	//Debug Output Stage
	return (0);
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