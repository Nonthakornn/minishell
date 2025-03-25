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

static char	**clear_local_var(char **var)
{
	char	**new_var;
	int		n;
	int		i;
	int		j;

	n = count_pub_var(var);
	new_var = new_str_arr(n + 1);
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
	char	**var;
	int		shlvl_idx;
	int		shlvl_value;
	char	*new_shlvl;

	var = inherited_variable(env);
	if (!var)
		return (NULL);
	var = clear_local_var(var);
	var = add_str_arr(var, slice("$?=0", 0, 4));
	shlvl_idx = get_variable_index(var, "SHLVL");
	if (shlvl_idx == -1)
		var = add_str_arr(var, slice("SHLVL=1", 0, 7));
	else
	{
		shlvl_value = ft_atoi(var[shlvl_idx] + 6) + 1;
		if (shlvl_value < 0)
			shlvl_value = 0;
		new_shlvl = itoa(shlvl_value);
		edit_str_arr(var, shlvl_idx, str_join("SHLVL=", new_shlvl));
		free(new_shlvl);
	}
	return (var);
}
