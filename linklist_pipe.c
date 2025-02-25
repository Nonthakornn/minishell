#include "minishell.h"

t_pipe	*create_pipe_lst(char **cmd, t_redirect *redir)
{
	int		i;
	t_pipe	*new_node;

	i = 0;
	while (cmd[i])
		i++;
	new_node = malloc(sizeof(t_pipe));
	if (!new_node)
		return (NULL);
	new_node->cmd = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (cmd[i])
	{
		new_node->cmd[i] = malloc(ft_strlen(cmd[i]) + 1);
		ft_strcpy(new_node->cmd[i], cmd[i]);
		i++;
	}
	new_node->cmd[i] = NULL;
	new_node->redirect = redir;
	new_node->next = NULL;
	return (new_node);
}

t_pipe	*lastnode_pipe_lst(t_pipe *head)
{
	t_pipe	*ptr;

	if (!head)
		return (NULL);
	ptr = head;
	while (ptr->next)
		ptr = ptr->next;
	return (ptr);
}

void	addback_pipe_lst(t_pipe **head, t_pipe *new_node)
{
	if (!head || !new_node)
		return ;
	if (!(*head))
		*head = new_node;
	else
		lastnode_pipe_lst(*head)->next = new_node;
}

/*
This one will comment later use for debug only dont care about norm
cmd[0] = "ls"
cmd[1] = "-la"
cmd[2] = NULL
*/
void	display_pipe_lst(t_pipe *head)
{
	int	i;
	int	cmd_num;

	cmd_num = 0;
	printf(PURPLE"Pipe Command List:\n"RST);
	printf(PURPLE"-----------------------------\n"RST);
	while (head)
	{
		i = 0;
		printf(PURPLE"[Command %d]\n"RST, cmd_num++);
		while (head->cmd[i])
		{
			printf("cmd[%d]: \"%s\"\n", i, head->cmd[i]);
			i++;
		}
		printf("cmd[%d]: NULL\n", i);
		if (head->redirect)
			display_redir_lst(head->redirect);
		else
			printf("Redirects: NULL\n");
		printf("next: ");
		if (head->next)
			printf("\n");
		else
			printf("NULL\n");
		head = head->next;
	}
	printf(RED"-----------------------------\n"RST);
}
