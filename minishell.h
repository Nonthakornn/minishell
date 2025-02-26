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
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_token_type
{
	CMD,
	READ_FILE, // <
	HERE_DOC, // <<
	WRITE_FILE, // >
	APPEND_FILE, // >>
	PIPE, // |
	ENV_VAR, // env variable like $PATH
	SINGLE_QUOTE,
	DOUBLE_QUOTE

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
	struct s_pipe		*next; // For piping next command

}	t_pipe;

//utils
void		ft_print_str(int fd, char *str);
void		ft_strcpy(char *dst, char *src);
int			ft_strlen(char *str);
bool		is_space(int c);

//token utils
char 		*get_str_token(t_token_type type);

//linklist_token
void		addback_redir_lst(t_redirect **head, t_redirect *new_node);
t_redirect	*create_redir_lst(t_token_type type, char *value);
t_redirect	*lastnode_redir_lst(t_redirect *head);

//linklist_pipe
void	addback_pipe_lst(t_pipe **head, t_pipe *new_node);
t_pipe	*create_pipe_lst(char **cmd, t_redirect *redir);
t_pipe	*lastnode_pipe_lst(t_pipe *head);

//split pipe
void pipe_segment(char **pipe_segment);
char	**split_by_pipes(char *str);


//free
void	free_redirects(t_redirect *head);
void	free_pipe_and_redir(t_pipe *head);


//display for dubugging
void		display_pipe_lst(t_pipe *head);
void		display_pipe_segment(char **pipe_segment);
void 		display_redir_lst(t_redirect *head);

#endif
