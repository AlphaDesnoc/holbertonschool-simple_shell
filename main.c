#include "main.h"

int main(void)
{
	char *input_buffer = NULL, **myargv;
	size_t size_allocated = 0;
	int char_read, ret = EXIT_SUCCESS;
	char *cwd;

	signal(SIGINT, SIG_IGN);
	do {
		cwd = getcwd(NULL, 0);
		if (cwd != NULL)
		{
			printf("\033[36m%s\033[00m$ ", cwd);
			free(cwd);
		}
		else
			perror("getcwd() error");

		fflush(stdin);
		char_read = getline(&input_buffer, &size_allocated, stdin);
		if (char_read == 1)
			continue;
		if (char_read == EOF)
		{
			free(input_buffer);
			if (isatty(STDIN_FILENO))
				putchar('\n');
			return (ret);
		}

		input_buffer[char_read - 1] = '\0';
		if (strncmp(input_buffer, "env", 3) == 0)
		{
			print_env();
			continue;
		}
		else if (strncmp(input_buffer, "exit", 4) == 0)
		{
			break;
		}

		myargv = token_args(input_buffer);
		if (myargv[0] != NULL)
			ret = execute_cmd(myargv);
		free(myargv);

	} while (1);
	free(input_buffer);
	return (ret);
}
