#include "main.h"

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
