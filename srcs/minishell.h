#ifndef MINISHELL_H
# define MINISHELL_H

# define RST	"\033[0m"
# define RED	"\033[0;31m"
# define GREEN	"\033[0;32m"
# define YELLOW	"\033[1;33m"
# define BLUE	"\033[0;34m"
# define PURPLE	"\033[0;35m"
# define CYAN	"\033[0;36m"

# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include "libft.h"

typedef enum e_token_type
{
	CMD,
	READ_FILE, // <
	HERE_DOC, // <<
	WRITE_FILE, // >
	APPEND_FILE, // >>
	PIPE, // |
	ENV_VAR, // env variable like $PATH
}	t_token_type;

typedef enum e_quote_state
{
	NORMAL,
	SINGLE_QUOTE,
	DOUBLE_QUOTE

}	t_quote_state;

typedef struct s_token
{
	t_token_type			token_type;
	char					*value;
	struct s_token			*next;

}	t_token;

typedef struct s_redirect
{
	t_token_type			token_type;
	char					*value;
	struct s_redirect		*next;

}	t_redirect;

typedef struct s_process
{
	char				**cmd;
	t_redirect			*redirect;
	int					*pipe_in;
	int					*pipe_out;
	int					*here_doc;
	pid_t				pid;
	struct s_process	*next;

}	t_process;

typedef struct s_redirect_store
{
	int	offset;
	int	infile_fd;
	int	outfile_fd;
	int	cur_infile_type;

}	t_redir_store;

//token utils
char		*get_str_token(t_token_type type);

//linklist_token
t_token *create_token_lst(t_token_type type, char *value);
t_token *lastnode_token_lst(t_token *head);
void	addback_token_lst(t_token **head, t_token *new_node);

//linklist_redirect
void		display_redir_lst(t_redirect *head);
void		addback_redir_lst(t_redirect **head, t_redirect *new_node);
t_redirect	*create_redir_lst(t_token_type type, char *value);
t_redirect	*lastnode_redir_lst(t_redirect *head);

//linklist_process
void		addback_process_lst(t_process **head, t_process *new_node);
t_process	*create_process_lst(char **cmd, t_redirect *redir);
t_process	*lastnode_process_lst(t_process *head);
void		pipe_process_lst(t_process **head);

//split process
char		**split_by_pipes(char *str);

//Close & free
void		free_redirects(t_redirect *head);
void		free_process_and_redir(t_process *head);
void		close_fd(t_process *process);
void		free_token(t_token *head);

//heredoc
void		exec_heredoc(t_process *process);

//process_redirect
int			process_redirect(t_process *process);

// exec_process
void		wait_process(t_process *head, int *exit_code);
void		fork_process(t_process *head, char *env[]);
char		*ft_get_path(char *env[], char *command);

// error
int			display_error_access(char *access_name);
int			display_error_no_command(char *command);
int			display_error_path(char *command);

//lexical
t_token		*tokenize(char *input);

//env
char		**load_variable(char *env[]);

//display for dubugging
void		display_process_lst(t_process *head);
void 		display_redir_lst(t_redirect *head);
void		display_token_lst(t_token *head);
void		display_redir_lst(t_redirect *head);

#endif
