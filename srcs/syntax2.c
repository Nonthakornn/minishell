#include "minishell.h"

static char			**extract_cmd(t_token **token, t_redirect **redirect);
static t_process	*process_cmd_segment(t_token **token);
t_process			*syntax(t_token *tokens);
t_redirect			*parse_redirect(t_token **token);

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

static void	handle_more_redirect(t_token **token, t_redirect **redirect)
{
	t_redirect	*more_redirect;
	t_redirect	*last;

	more_redirect = parse_redirect(token);
	if (more_redirect)
	{
		last = *redirect;
		while (last->next)
			last = last->next;
		last->next = more_redirect;
	}
}

static char	**extract_cmd(t_token **token, t_redirect **redirect)
{
	char	**cmd;
	int		cmd_count;
	int		i;

	cmd = NULL;
	i = 0;
	cmd_count = command_count(*token);
	cmd = malloc(sizeof(char *) * (cmd_count + 1));
	while (i < cmd_count && *token)
	{
		cmd[i] = slice((*token)->value, 0, ft_strlen((*token)->value));
		i++;
		(*token) = (*token)->next;
	}
	cmd[i] = NULL;
	if (!(*redirect))
		*redirect = parse_redirect(token);
	else
		handle_more_redirect(token, redirect);
	return (cmd);
}

static t_process	*process_cmd_segment(t_token **token)
{
	char		**cmd;
	t_token		*tmp_token;
	t_redirect	*redirect;

	tmp_token = *token;
	cmd = NULL;
	redirect = NULL;
	if (tmp_token && check_redir_type(tmp_token))
	{
		redirect = parse_redirect(&tmp_token);
		if (!redirect)
			return (NULL);
		*token = tmp_token;
	}
	cmd = extract_cmd(token, &redirect);
	if (!cmd)
	{
		free_redirects(redirect);
		return (NULL);
	}
	return (create_process_lst(cmd, redirect));
}

t_process	*syntax(t_token *tokens)
{
	t_process	*head;
	t_process	*new_proc;
	t_token		*current;

	head = NULL;
	new_proc = NULL;
	current = tokens;
	while (current)
	{
		new_proc = process_cmd_segment(&current);
		if (!new_proc)
		{
			free_token(tokens);
			return (free_process_and_redir(head), NULL);
		}
		addback_process_lst(&head, new_proc);
		if (current && current->token_type == PIPE)
			current = current->next;
	}
	free_token(tokens);
	return (head);
}
