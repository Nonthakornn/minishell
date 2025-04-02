#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

static void	prompt(char **variable)
{
	char		*input;
	t_process	*proc;

	while (1)
	{
		setup_signal();
		input = readline("minishell $> ");
		if (g_signal == 1)
		{
			set_exit_code(&variable, 130);
			g_signal = 0;
		}
		if (!input)
			input = ft_strdup("exit");
		proc = get_process(input, variable);
		if (!proc)
			continue ;
		excute(&proc, &variable);
	}
}

int	main(int argc, char *argv[], char *env[])
{
	char		**variable;

	check_argv(argc, argv);
	variable = get_parent_variable(env);
	prompt(variable);
	return (0);
}
