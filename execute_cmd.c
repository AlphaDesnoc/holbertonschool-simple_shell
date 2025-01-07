#include "main.h"

/**
 * execute_cmd - Executes a command provided as an argument array.
 *
 * @argv: A null-terminated array of strings, where the first element is the
 *        command to execute, and subsequent elements are its arguments.
 *
 * This function attempts to execute a command by:
 *   1. Allocating a work buffer to hold the resolved command path.
 *   2. Checking if the command exists and resolving its path using path_finder
 *   3. Creating a child process using `fork`.
 *   4. In the child process, attempting to execute the command with `execve`.
 *   5. In the parent process, waiting for the child process to terminate and
 *      returning its exit status.
 *
 * If any step fails (e.g., memory allocation, command resolution, forking, or
 * execution) the function handles errors and returns appropriate failure codes
 *
 * Return:
 *   - On success: The exit status of the executed command.
 *   - On failure:
 *       - 127 if the command is not found.
 *       - EXIT_FAILURE (commonly 1) if memory allocation, forking, or other
 *         internal errors occur.
 *
 * Notes:
 *   - The `path_finder` function is expected to resolve the full path of the
 *     command and store it in the provided buffer (`work_buffer`).
 *   - The child process exits immediately upon encountering an error,returning
 *     127 for a "command not found" scenario or EXIT_FAILURE for other errors.
 *   - The function assumes `environ` is globally available.
 *
 * Example:
 *   char *args[] = { "ls", "-l", "/home", NULL };
 *   int status = execute_cmd(args);
 *   if (status == 127)
 *       fprintf(stderr, "Command not found.\n");
 *   else if (status != 0)
 *       fprintf(stderr, "Command execution failed with status %d.\n", status);
 *
 * Caveats:
 *   - The function assumes `path_finder` correctly resolves the command path.
 *   - The work buffer size (1024 bytes) may be insufficient for some commands,
 *     potentially causing truncation or errors.
 *   - If a signal interrupts `wait`, the function may not handle it explicitly
 *   - The `argv` array must be null-terminated and non-NULL.
 */
int execute_cmd(char **argv)
{
	pid_t child_pid;
	int status;
	char *cmd = argv[0], *work_buffer;

	work_buffer = malloc(1024);
	if (work_buffer == NULL)
		return (_error());

	if (strcpy(work_buffer, cmd) != work_buffer)
	{
		free(work_buffer);
		return (_error());
	}
	if (path_finder(cmd, work_buffer) == EXIT_FAILURE)
	{
		fprintf(stderr, "./hsh: 1: %s: not found\n", cmd);
		free(work_buffer);
		return (127);
	}
	child_pid = fork();
	if (child_pid == -1)
	{
		free(work_buffer);
		return (_error());
	}
	if (child_pid == 0)
	{
		if (execve(work_buffer, argv, environ) == -1)
		{
			fprintf(stderr, "./hsh: 1: %s: not found\n", cmd);
			free(work_buffer);
			exit(127);
		}
		exit(EXIT_FAILURE);
	}
	wait(&status);
	free(work_buffer);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	return (status);
}

