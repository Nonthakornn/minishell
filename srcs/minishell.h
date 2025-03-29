#ifndef MINISHELL_H
# define MINISHELL_H

# define _POSIX_C_SOURCE 200809L
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
# include <dirent.h>
# include <limits.h>
# include <signal.h>
# include "libft.h"

/*
extern indicates that variable has external linkage
and can access across multiplefile
*/
extern volatile sig_atomic_t	g_signal;

typedef enum e_token_type
{
	CMD,
	READ_FILE, // <
	HERE_DOC, // <<
	WRITE_FILE, // >
	APPEND_FILE, // >>
	PIPE, // |
}	t_token_type;

typedef enum e_quote_state
{
	NORMAL,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
}	t_quote_state;

typedef struct s_token
{
	t_token_type			token_type;
	t_quote_state			quote_type;
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

typedef struct s_var_info
{
	int		start;
	int		end;
	char	*name;
	char	*value;
}	t_var_info;

//token utils
char			*get_str_token(t_token_type type);
int				command_count(t_token *token);
int				valid_to_expand(char *result, int i);
bool			is_normal_char(char c);
char			*create_empty_string(void);
char			*create_quoted_string(char *str, int start, int end);
char			*extract_quote(char *str, int *i, char quote_char);
int				join_with_previous(t_token **head, char *word);
t_token			*process_quoted_word(char *word, t_quote_state quote_type);
char			*extract_normal_word(char *str, int *i, int *len);
int				check_quote_and_state(char *str, int i, t_quote_state state);
int				is_ok_to_join(char *str, int i, char *word);
int				ft_combine(t_token *last, char *word);
t_quote_state	assign_quote_type(char quote_char);
bool			process_token(t_token **tokens, char **variable);

//linklist_token
t_token			*create_token_lst(t_token_type type, char *value);
t_token			*lastnode_token_lst(t_token *head);
void			addback_token_lst(t_token **head, t_token *new_node);

//linklist_redirect
void			display_redir_lst(t_redirect *head);
void			addback_redir_lst(t_redirect **head, t_redirect *new_node);
t_redirect		*create_redir_lst(t_token_type type, char *value);
t_redirect		*lastnode_redir_lst(t_redirect *head);

//linklist_process
void			addback_process_lst(t_process **head, t_process *new_node);
t_process		*create_process_lst(char **cmd, t_redirect *redir);
t_process		*lastnode_process_lst(t_process *head);
void			pipe_process_lst(t_process **head);

//split process
char			**split_by_pipes(char *str);

//Close & free
t_token			*free_token_return(t_token *head);
void			free_redirects(t_redirect *head);
void			free_process_and_redir(t_process *head);
void			close_pipe(t_process *process);
void			free_token(t_token *head);
void			free_everything(t_process *proc, char **var, int std[2]);

//heredoc
void			exec_heredoc(t_process *process);

//process_redirect
int				process_redirect(t_process *process);

// exec_process
void			exec_execve(t_process *head, t_process *process, \
				char **var, int stdfd[2]);
int				exec_process(t_process *head, t_process *process, char ***var);
void			wait_process(t_process *head, int *exit_code);
void			fork_process(t_process *head, char ***var);
char			*get_path(char *env[], char *command);
void			terminate_process(t_process *head, char **var, int code);
void			recover_stdfd(int stdfd[2]);

// error
void			put_strerror(char *name, char *strerr);
int				error_access(char *access_name);
int				error_no_command(char *command);
int				error_no_path(char *command);
int				error_unset_option(char *name);
int				error_export_option(char *key, char *value);
int				error_pwd_option(char *name);
int				error_export_name(char *key, char *value);
int				error_argument(char *cmd, char *arg);

//lexical
t_token			*tokenize(char *input);
int				handle_operator(char *str, int *i, t_token **head);
int				handle_quote(char *str, int *i, \
				t_token **head, t_quote_state *state);
int				handle_normal_word(char *str, int *i, t_token **head);

//syntax
bool			check_syntax_err(t_token *tokens);
bool			check_redir_type(t_token *tokens);
t_process		*syntax(t_token *tokens);

//env
int				key_exist(char *var_str, char *key);
int				get_variable_index(char **var, char *key);
int				count_variable(char *env[]);
char			**inherited_variable(char *env[]);
char			**get_parent_variable(char *env[]);
int				exec_env(t_process *process, char **var);

//unset
int				exec_unset(t_process *process, char ***var);

//export
int				exec_export(t_process *process, char ***var);
int				add_export(char ***var, char *str);

//cd pwd
char			*getcwd_variable(char *key);
int				exec_pwd(t_process *process, char ***var);
int				exec_chdir(t_process *process, char **var);
int				exec_cd(t_process *process, char ***var);
int				is_dir(char *path);

//expand
bool			expand_token(t_token **token, char **variable);
char			*handle_dollar(char *str, char **variable);

//echo
int				exec_echo(t_process *process, char **variable);

//exit
int				exec_exit(t_process *process, char **var, int std[2]);
bool			handle_overflow(long long result, int sign, int *status);
int				count_arg(t_process	*proc);
int				get_exit_code(char **var);

//syntax utils
int				count_commands(t_token *seg_start, t_token *seg_end);
t_token			*find_seg_end(t_token *start);
int				is_filename_for_redirection(t_token *seg_start,
					t_token *current);

//process
t_process		*get_process(char *input, char **var);
void			check_argv(int argc, char *argv[]);
void			excute(t_process **head, char ***var);

//signal
void			setup_signal(void);
void			handle_sigint(int signum);
void			handle_sigquit(int signum);

//display for dubugging
void			display_process_lst(t_process *head);
void			display_redir_lst(t_redirect *head);
void			display_token_lst(t_token *head);
void			display_redir_lst(t_redirect *head);
#endif
