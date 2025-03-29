#include "minishell.h"

volatile sig_atomic_t g_signal;

int	main(int argc, char *argv[], char *env[])
{
	int			code;
	char		**variable;
	char		*input;
	t_process	*proc;

	code = 0;
	check_argv(argc, argv);
	variable = get_parent_variable(env);
	g_signal = 0;
	while (1)
	{
		setup_signal();
		input = readline("minishell $> ");
		if (!input)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			break ;
		}
		proc = get_process(input, variable);
		if (!proc)
			continue ;
		excute(&proc, &variable);
		code = get_exit_code(variable);
	}
	free_str_arr(variable);
	rl_clear_history();
	return (code);
}
