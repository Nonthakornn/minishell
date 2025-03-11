#include <stdio.h>
#include "libft.h"

int main(int argc, char *argv[], char **env)
{
	char **sort_env;

	sort_env = sort_arr(env);
	print_str_array(sort_env);
	free_str_arr(sort_env);
}
