#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>

typedef enum e_token_type
{
	CMD,
	READ_FILE, // <
	HERE_DOC, // <<
	WRITE_FILE, // >
	APPEND_FILE, // >>
	PIPE, // |
	ENV_VAR // env variable like $PATH

}	t_token_type;

typedef struct s_redirect
{
	t_token_type			token_type;
	char					*value;
	struct s_redirect		*next;

}	t_redirect;

typedef struct s_pipe
{
	char				**cmd; //The command with arguments
	t_redirect			*redirect; // Linked list of redirection
	struct s_command	*next; // For piping next command

}	t_pipe;

void	ft_print_str(int fd, char *str);

#endif
