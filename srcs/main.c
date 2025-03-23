#include "minishell.h"

int main(int ac, char *av[], char *env[])
{
	int			code = 0;
	char		**variable;
	char		*input;
	t_token		*tokens;
	t_process	*proc;

	variable = get_parent_variable(env);
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
		tokens = tokenize(input);
		// display_token_lst(tokens);
		free(input);
		if (!tokens)
			continue;
		if (!check_syntax_err(tokens))
		{
			printf("Syntax Error\n");
			free_token(tokens);
			continue;
		}
		proc = syntax(tokens);
		// display_process_lst(proc);
		pipe_process_lst(&proc);
		exec_heredoc(proc);
		if (proc->next)
		{
			fork_process(proc, &variable);
			wait_process(proc, &code);
		}
		else
			code = exec_process(proc, proc, &variable);
		free_process_and_redir(proc);
	}
	free_str_arr(variable);
	clear_history();
	return (code >> 8);
}
