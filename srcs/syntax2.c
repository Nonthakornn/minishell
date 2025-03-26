#include "minishell.h"

t_redirect	*parse_redirect(t_token **token)
{
	t_redirect	*head;
	t_token		*current;
	t_token		*file;

	head = NULL;
	current = *token;
	while (current && current->token_type != PIPE)
	{
		if (check_redir_type(current))
		{
			file = current->next;
			if (!file || file->token_type != CMD)
			{
				free_redirects(head);
				return (NULL);
			}
			addback_redir_lst(&head,
				create_redir_lst(current->token_type, file->value));
			current = file->next;
		}
		else
			break ;
	}
	*token = current;
	return (head);
}

static void	add_command_to_array(char **cmd_array, int *index, t_token *current,
					t_token *seg_start)
{
	if (current->token_type == CMD)
	{
		if (!is_filename_for_redirection(seg_start, current))
			cmd_array[(*index)++] = ft_strdup(current->value);
	}
}

static void	process_redirection(t_redirect **redirect, t_token **current)
{
	t_redirect	*new_redir;
	char		*temp_value;	

	temp_value = NULL;
	if (check_redir_type(*current) && (*current)->next)
	{
		temp_value = ft_strdup((*current)->next->value);
		new_redir = create_redir_lst((*current)->token_type, temp_value);
		free(temp_value);
		if (!*redirect)
			*redirect = new_redir;
		else
			addback_redir_lst(redirect, new_redir);
		*current = (*current)->next;
	}
}

static t_token	*process_command_seg(t_token *seg_start, t_process **head)
{
	t_token		*seg_end;
	t_token		*current;
	char		**cmd;
	t_redirect	*redirect;
	int			i;

	seg_end = find_seg_end(seg_start);
	cmd = malloc_array(count_commands(seg_start, seg_end));
	if (!cmd)
		return (NULL);
	redirect = NULL;
	i = 0;
	current = seg_start;
	while (current && current->token_type != PIPE)
	{
		add_command_to_array(cmd, &i, current, seg_start);
		process_redirection(&redirect, &current);
		current = current->next;
	}
	cmd[i] = NULL;
	addback_process_lst(head, create_process_lst(cmd, redirect));
	return (current);
}

t_process	*syntax(t_token *tokens)
{
	t_process	*head;
	t_token		*current;

	head = NULL;
	current = tokens;
	while (current)
	{
		current = process_command_seg(current, &head);
		if (current && current->token_type == PIPE)
			current = current->next;
	}
	free_token(tokens);
	return (head);
}
/*
syntax Flow:
Start with token list and NULL head
While current token exists:
1. Call process_command_segment with current token and head reference
	process_command_segment Flow
2. Find segment end (end of the pipe)
3. Count commands in segment
4. Allocate memory for command array
5. Set redirect to NULL and index to 0
6. Process each token until pipe or end:
	If token is CMD:
		Is it a filename for redirection?
			No -> Add to command array at index i++
7. If token is redirection type and has next token:
Create new redirection node
	Add to redirection list
	Skip the filename token
8. Set cmd[i] = NULL
9. Create process with commands and redirections
10. Add process to list
11. Return current token after segment
*/