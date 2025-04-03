#include "minishell.h"

t_process	**get_h_proc(void)
{
	static t_process	*head;

	return (&head);
}

void	set_h_proc(t_process *head)
{
	t_process	**h;

	h = get_h_proc();
	*h = head;
}

char	***get_var(void)
{
	static char	**var;

	return (&var);
}

void	set_var(char **var)
{
	char	***v;

	v = get_var();
	*v = var;
}
