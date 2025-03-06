#include "minishell.h"

t_process	*create_process_lst(char **cmd, t_redirect *redir)
{
	int			i;
	t_process	*new_node;

	i = 0;
	while (cmd[i])
		i++;
	new_node = malloc(sizeof(t_process));
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
	new_node->pipe_in = NULL;
	new_node->pipe_out = NULL;
	new_node->here_doc = NULL;
	new_node->next = NULL;
	new_node->pid = -1;
	return (new_node);
}

t_process	*lastnode_process_lst(t_process *head)
{
	t_process	*ptr;

	if (!head)
		return (NULL);
	ptr = head;
	while (ptr->next)
		ptr = ptr->next;
	return (ptr);
}

void	addback_process_lst(t_process **head, t_process *new_node)
{
	if (!head || !new_node)
		return ;
	if (!(*head))
		*head = new_node;
	else
		lastnode_process_lst(*head)->next = new_node;
}

void	pipe_process_lst(t_process **head)
{
	t_process	*tmp;
	int			*cur_pipe;
	int			*prev_pipe;

	if (!head || !(*head)->next)
		return ;
	prev_pipe = NULL;
	tmp = *head;
	while (tmp)
	{
		if (prev_pipe)
			tmp->pipe_in = prev_pipe;
		if (tmp->next)
		{
			cur_pipe = malloc(sizeof(int) * 3);
			cur_pipe[2] = 0;
			pipe(cur_pipe);
			tmp->pipe_out = cur_pipe;
			prev_pipe = cur_pipe;
		}
		tmp = tmp->next;
	}
}
/*
This one will comment later use for debug only dont care about norm
cmd[0] = "ls"
cmd[1] = "-la"
cmd[2] = NULL
*/

void	display_process_lst(t_process *head)
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
