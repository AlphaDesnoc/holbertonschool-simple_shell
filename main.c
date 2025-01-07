#include "main.h"

/**
 * main - Entry point of the shell program.
 *
 * This function implements a simple command-line shell. It repeatedly:
 *   1. Displays the current working directory.
 *   2. Reads a command from the user.
 *   3. Tokenizes the command into arguments.
 *   4. Executes the command using `execute_cmd`.
 *   5. Handles built-in commands like "env" and "exit".
 *   6. Loops until the user enters an "exit" command.
 *
 * Return:
 *   - EXIT_SUCCESS: On successful execution.
 *   - Various error codes from the shell commands.
 *
 * Notes:
 *   - The function uses `getline` to read commands from stdin.
 *   - The `input_buffer` is freed after each iteration to avoid memory leaks.
 *   - The `print_env` function outputs the current environment variables.
 *   - The `token_args` function breaks the input into command arguments.
 *   - `execute_cmd` is responsible for executing non-built-in commands.
 *   - The signal handler (`SIGINT`) is set to ignore interrupts to allow
 *     for a more user-friendly shell experience.
 *
 * Example:
 *   $ ./hsh
 *   /home/user$ env
 *   PATH=/usr/bin:/bin:/usr/sbin:/sbin
 *   /home/user$ ls -l
 *   total 12
 *   drwxr-xr-x 2 user user 4096 Dec 16 12:34 dir1
 *   /home/user$ exit
 *
 */
int main(void)
{
	char *input_buffer = NULL, **myargv, *cwd;
	size_t size_allocated = 0;
	int char_read, ret = EXIT_SUCCESS;

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
		if (char_read <= 1)
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
			break;
		myargv = token_args(input_buffer);
		if (myargv[0] != NULL)
			ret = execute_cmd(myargv);
		free(myargv);
	} while (1);
	free(input_buffer);
	return (ret);
}

