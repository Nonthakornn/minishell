#include "minishell.h"

t_process	**get_head()
{
	static t_process	*head = NULL;
	return (&head);
}

void	set_head(t_process *head)
{
	t_process	**h;

	h = get_head();
	*h = head;
}

char	***get_var()
{
	static char	**var = NULL;
	return (&var);
}

void	set_var(char **var)
{
	char	***v;

	v = get_var();
	*v = var;
}
