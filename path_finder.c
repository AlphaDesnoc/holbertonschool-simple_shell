#include "main.h"

/**
 * path_finder - Resolves the full path of a command.
 *
 * @cmd: The command to find.
 * @work_buffer: A buffer to store the resolved path.
 *
 * This function checks if the command specified by `cmd` is an absolute path
 * or a relative path (e.g., "./", "../"). If it is, and it exists, it directly
 * returns `EXIT_SUCCESS`. Otherwise, it searches through directories listed in
 * the PATH environment variable to locate the command.If the command is found,
 * it stores the full path in work_buffer and returns `EXIT_SUCCESS`.Otherwise,
 * it returns `EXIT_FAILURE`.
 *
 * Return:
 *   -EXIT_SUCCESS: If the command was found and its path resolved successfully
 *   -EXIT_FAILURE: If the command is not found or if any error occurs during
 *     path resolution.
 *
 * Notes:
 *   -The function uses `strtok` to split the `PATH` environment variable into
 *     individual directory tokens.
 *   -The function assumes that `cmd` is a valid, non-NULL string.
 *   -Memory for `var_path` and `work_buffer` is dynamically allocated and must
 *     be freed by the caller.
 *   -The function assumes the presence of a valid `PATH` environment variable.
 *   -The file_checker function is used to check if the constructed path exists
 *
 * Example:
 *   char work_buffer[1024];
 *   int status = path_finder("ls", work_buffer);
 *   if (status == EXIT_SUCCESS)
 *       printf("Found: %s\n", work_buffer);
 *   else
 *       printf("Command not found.\n");
 *
 */
int path_finder(char *cmd, char *work_buffer)
{
	char *token;
	char *var_path, *var_value_path;

	if ((cmd[0] == '/' || strncmp(cmd, "./", 2) == 0 ||
				strncmp(cmd, "../", 3) == 0) && file_checker(cmd) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);

	var_value_path = _getenv("PATH");
	if (var_value_path == NULL)
		return (EXIT_FAILURE);
	if (strlen(var_value_path) == 0)
		return (EXIT_FAILURE);

	var_path = strdup(var_value_path);
	if (var_path == NULL)
		return (EXIT_FAILURE);

	token = strtok(var_path, ":");
	while (token)
	{
		if (sprintf(work_buffer, "%s/%s", token, cmd) < 0)
		{
			free(var_path);
			return (EXIT_FAILURE);
		}

		if (file_checker(work_buffer) == EXIT_SUCCESS)
		{
			free(var_path);
			return (EXIT_SUCCESS);
		}
		token = strtok(NULL, ":");
	}
	free(var_path);
	return (EXIT_FAILURE);
}
