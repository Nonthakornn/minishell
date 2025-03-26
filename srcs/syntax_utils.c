#include "minishell.h"

int	count_commands(t_token *seg_start, t_token *seg_end)
{
	int		cmd_count;
	t_token	*current;

	cmd_count = 0;
	current = seg_start;
	while (current && current != seg_end)
	{
		if (current->token_type == CMD)
			cmd_count++;
		current = current->next;
	}
	return (cmd_count);
}

t_token	*find_seg_end(t_token *start)
{
	t_token	*end;

	end = start;
	while (end && end->token_type != PIPE)
		end = end->next;
	return (end);
}

int	is_filename_for_redirection(t_token *seg_start, t_token *current)
{
	t_token	*prev;

	prev = seg_start;
	while (prev != current)
	{
		if (check_redir_type(prev) && prev->next == current)
			return (1);
		prev = prev->next;
	}
	return (0);
}
