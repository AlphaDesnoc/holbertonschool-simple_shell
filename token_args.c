#include "main.h"

/**
 * token_args - Tokenizes a command string into arguments.
 *
 * @input_buffer: The command string to tokenize.
 *
 * This function tokenizes the input_buffer into individual arguments splitting
 * by spaces or tabs. It dynamically allocates memory for an array of strings
 * argv to hold these tokens. The function first creates a copy of input_buffer
 * to avoid modifying the original input. The last element of the array
 * is set to `NULL` to mark the end.
 *
 * Return:
 *   - A pointer to an array of strings (`argv`) containing
 *   the command arguments.
 *   - On failure, the function prints an error message and
 *   exits with `EXIT_FAILURE`.
 *
 * Notes:
 *   - The function uses `strdup` to create a copy of the `input_buffer`
 *     to tokenize without altering the original input.
 *   - The function uses `strtok` to split the command string into tokens.
 *   - Memory for the token array (`argv`) is dynamically allocated
 *     and must be freed by the caller after use.
 *   - The function assumes that each token is a valid, non-NULL string.
 *   - Error handling is minimal and only checks for memory allocation failures
 *
 * Example:
 *   char *input = "ls -l /home/user";
 *   char **args = token_args(input);
 *   for (int i = 0; args[i] != NULL; i++)
 *       printf("%s\n", args[i]);
 *
 * Caveats:
 *   - The function does not handle quoted strings or escape sequences.
 *   - The function assumes the `input_buffer` is not NULL.
 *   - If `strdup` or `malloc` fails, the function will exit with EXIT_FAILURE.
 *   - The caller must free the memory allocated for argv to avoid memory leaks
 */
char **token_args(char *input_buffer)
{
	char *token, **argv, *input_copy;
	int token_count = 0, i = 0;

	while (*input_buffer == ' ' || *input_buffer == '\t')
		input_buffer++;

	input_copy = strdup(input_buffer);
	if (!input_copy)
	{
		perror("Memory allocation error");
		exit(EXIT_FAILURE);
	}

	token = strtok(input_copy, " ");
	while (token)
	{
		token_count++;
		token = strtok(NULL, " ");
	}

	argv = malloc((token_count + 1) * sizeof(char *));
	if (!argv)
	{
		perror("Memory allocation error");
		free(input_copy);
		exit(EXIT_FAILURE);
	}

	token = strtok(input_buffer, " ");
	while (token)
	{
		argv[i++] = token;
		token = strtok(NULL, " ");
	}
	argv[i] = NULL;
	free(input_copy);

	return (argv);
}

