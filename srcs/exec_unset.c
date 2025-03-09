#include "minishell.h"

int	exec_unset(t_process *head, t_process *process, char ***variable)
{
	int	i;
	int	remove_index;

	i = 1;
	remove_index = -1;
	while (process->cmd[i])
	{
		remove_index = get_variable_index((*variable), process->cmd[i]);
		if (remove_index >= 0)
		{
			(*variable) = remove_str_arr((*variable), remove_index);
		}
		i++;
	}
	free_process_and_redir(head);
	return (0);
}
