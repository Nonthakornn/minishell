#include "minishell.h"

volatile sig_atomic_t g_signal = 0;

static void prompt(char **variable)
{
	char		*input;
	t_process	*proc;
	char		*new_exit_code;

	while (1)
	{
		setup_signal();
		input = readline("minishell $> ");
		if (g_signal == 1)
        {
            int idx = get_variable_index(variable, "?");
            if (idx >= 0)
            {
                new_exit_code = itoa(130);
                edit_str_arr(variable, idx, str_join("$?=", new_exit_code));
                free(new_exit_code);
            }
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
