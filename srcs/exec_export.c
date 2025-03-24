#include "minishell.h"

static void	printf_export_str(char *str)
{
	int		i;
	char	temp[2];
	int		found;

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

static void	show_export(char **var)
{
	int		i;
	char	**sort_var;

	sort_var = sort_str_arr(var);
	i = 0;
	while (sort_var[i])
	{
		if (startwith(sort_var[i], "_=") || \
		startwith(sort_var[i], "$") || \
		startwith(sort_var[i], "@"))
		{
			i++;
			continue ;
		}
		printf_export_str(sort_var[i]);
		i++;
	}
	free_str_arr(sort_var);
}

int	exec_export(t_process *process, char ***var)
{
	int	exit_code;
	int	i;

	exit_code = 0;
	i = 1;
	if (count_str_arr(process->cmd) == 1)
		show_export(*var);
	else
	{
		while ((process->cmd)[i])
		{
			exit_code = add_export(var, (process->cmd)[i]);
			if (exit_code > 0)
				break ;
			i++;
		}
	}
	return (exit_code);
}
