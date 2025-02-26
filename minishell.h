#ifndef MINISHEL_H
#define MINISHEL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>

typedef enum e_token_type
{
	CMD,
	READ_FILE,
	HERE_DOC,
	WRITE_FILE,
	APPEND_FILE,
	PIPE,
	ENV_VAR
} t_token_type;

typedef struct s_redirect
{
	t_token_type		token_type;
	char				*value;
	struct s_redirect	*next;
} t_redirect;

typedef struct s_pipe
{
	char			**cmd;
	t_redirect		*redicts;
	struct s_pipe	*next;
} t_pipe;

int		**run_here_doc_in_cmd(t_pipe *pipe);
int		redirect_in_pipe(t_redirect *redir, int *here_doc_fd);

#endif