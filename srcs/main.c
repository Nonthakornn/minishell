#include "minishell.h"

int main(void)
{
	char		*input;
	// t_token		*tokens;
	// t_process	*proc; 

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
		//TODO
		// tokens = tokenize(input);

		//! Debug: Display tokens
		//display_token(tokens);

		// proc = parse(tokens);

		//! Debug: Display process
		//display_process_lst(proc)

		//TODO Clean up


	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}
