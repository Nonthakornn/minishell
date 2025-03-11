#include "minishell.h"

static void	printf_export_str(char *str)
{
	int	i;
	char temp[2];
	int	found;

	if (is_equal(str, "_"))
		return ;
	i = 0;
	found = 0;
	write(1, "declare -x ", 11);
	while (str[i])
	{
		if (str[i] == '=' && !found)
		{
			found = 1;
			write(1, "=\"", 2);
		}
		else
		{
			temp[0] = str[i];
			write(1, temp, 1);
		}
		i++;
	}
	write(1, "\"\n", 2);
}

static void	show_export(char **variable)
{
	int		i;
	char	**sort_variable;

	sort_variable = sort_arr(variable);
	i = 0;
	while (sort_variable[i])
	{
		if (startwith(sort_variable[i], "_=") || startwith(sort_variable[i], "$"))
		{
			i++;
			continue ;
		}
		printf_export_str(sort_variable[i]);
		i++;
	}
	free_str_arr(sort_variable);
}

int	exec_export(t_process *head, t_process *process, char ***variable)
{	
	int	exit_code;
	int	i;

	exit_code = 0;
	i = 1;
	if (count_str_array(process->cmd) == 1)
		show_export(*variable);
	else
	{
		while ((process->cmd)[i])
		{
			if (!add_export(variable, (process->cmd)[i]))
				exit_code = 1;
			i++;
		}
	}
	free_process_and_redir(head);
	return (exit_code);
}
