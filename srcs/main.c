#include "minishell.h"

void	excute(t_process **head, char ***var, int *code)
{
	pipe_process_lst(head);
	exec_heredoc(*head);
	if ((*head)->next)
	{
		fork_process(*head, var);
		wait_process(*head, code);
	}
	else
		*code = exec_process(*head, *head, var);
	free_process_and_redir(*head);
}

int main(int ac, char *av[], char *env[])
{
	int			code = 0;
	char		**variable;
	char		*input;
	t_token		*tokens;
	t_process	*proc;

	(void) ac;
	(void) av;
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
		excute(&proc, &variable, &code);
	}
	free_str_arr(variable);
	rl_clear_history();
	return (code >> 8);
}


