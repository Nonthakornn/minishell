#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

static void	prompt(char **variable)
{
	char		*input;
	t_process	*proc;

	while (1)
	{
		setup_signal_prompt();
		input = readline("minishell $> ");
		if (!input)
			input = ft_strdup("exit");
		proc = get_process(input, variable);
		if (!proc)
			continue ;
		set_h_proc(proc);
		set_var(variable);
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
