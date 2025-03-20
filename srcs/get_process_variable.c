#include "minishell.h"

static int	count_pub_var(char **var)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (var && var[i])
	{
		if (var[i][0] != '$')
			count++;
		i++;
	}
	return (count);
}

static char **clear_local_var(char **var)
{
	char	**new_var;
	int		n;
	int		i;
	int		j;

	n = count_pub_var(var);
	new_var = malloc(sizeof(char *) * (n + 1));
	init_str_array(new_var, n);
	i = 0;
	j = 0;
	while (var && var[i])
	{
		if (var[i][0] == '$')
			free(var[i]);
		else
		{
			new_var[j] = var[i];
			j++;
		}
		i++;
	}
	free(var);
	return (new_var);
}

char	**get_parent_variable(char *env[])
{
	char	**variable;
	int		shlvl_idx;
	int		shlvl_value;
	char	*new_shlvl;
	
	variable = inherited_variable(env);
	if (!variable)
		return (NULL);
	variable = clear_local_var(variable);
	shlvl_idx = get_variable_index(variable, "SHLVL");
	if (shlvl_idx == -1)
	{
		variable = add_str_arr(variable, \
		slice("SHLVL=1", 0, ft_strlen("SHLVL=1")));
	}
	else
	{
		shlvl_value = ft_atoi(variable[shlvl_idx] + 6) + 1;
		if (shlvl_value < 0)
			shlvl_value = 0;
		new_shlvl = itoa(shlvl_value);
		edit_str_arr(variable, shlvl_idx, str_join("SHLVL=", new_shlvl));
		free(new_shlvl);
	}
	return (variable);
}
