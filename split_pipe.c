#include "minishell.h"

/*
	"ls -l | grep test"      -> ["ls -l", "grep test", NULL]
	"cat file.txt | wc -l"   -> ["cat file.txt", "wc -l", NULL]
	"echo hello"             -> ["echo hello", NULL]
*/
static int	pipe_count(char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == '|')
			count++;
		str++;
	}
	return (count + 1);
}

static char	*fill_segment(int start, int end, char *str)
{
	char	*segment;
	int		i;	

	//trim space
	while (start < end && is_space(str[start]))
		start++;
	while (end > start && is_space(str[end - 1]))
		end--;
	i = 0;
	segment = malloc(end - start + 1);
	if (!segment)
		return (NULL);
	while (start < end)
		segment[i++] =str[start++];
	segment[i] = '\0';
	return (segment);
}

char **split_by_pipes(char *str)
{
	int		i;
	char	**pipe_segment;
	int		start;
	int		end;

	if (!str)
		return (NULL);
	pipe_segment = malloc(sizeof(char *) * (pipe_count(str) + 1));
	if (!pipe_segment)
		return (NULL);
	i = 0;
	start = 0;
	end = 0;
	while (i <  pipe_count(str))
	{
		start = end;
		while (str[end] && str[end] != '|')
			end++;
		pipe_segment[i] = fill_segment(start, end, str);
		i++;
		if (str[end] == '|')
			end++;
	}
	pipe_segment[i] = NULL;
	return (pipe_segment);
}

void display_pipe_segment(char **pipe_segment)
{
	int i;
	int	j;

	i = 0;
	j = 1;
	if (!pipe_segment[0][0])
	{
		printf("(empty string)\n");
		return ;
	}
	while (pipe_segment[i])
	{
		printf("\"%s\",\n", pipe_segment[i]);
		i++;
		j++;
	}
	printf("NULL\n");
}

// cc parser.c utils.c
// int main()
// {
// 	int i = 0;
// 	char *input = "echo \"hello\" | cat -e";

// 	char **pipe_segment = split_by_pipes(input);
// 	display_pipe_segment(pipe_segment);

// }