#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

int main(int arg, char *argv[], char *env[])
{
	char *cmd[] = {"test", NULL};
	DIR *d;

	// printf("%d\n",access("./test", F_OK));
	d = opendir("bin");
	printf("%p\n", d);
	closedir(d);
	// execve("test", cmd, env);
	// printf("%s\n", strerror(errno));
}