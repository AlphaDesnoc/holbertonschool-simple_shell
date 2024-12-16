#include "main.h"

/**
 * _getenv - Retrieves the value of an environment variable.
 *
 * @name: The name of the environment variable to find.Must be non-NULL string
 *
 * This function searches the `environ` array for an environment variable
 * matching the specified name. If the variable exists and is formatted as
 * "name=value", the function returns a pointer to the value part of the
 * string (i.e., the portion after the '=' character). If the variable is not
 * found, or if `name` or `environ` is NULL, the function returns NULL.
 *
 * Return:
 *   - On success: A pointer to the value of the environment variable.
 *   - On failure: NULL
 *
 * Notes:
 *   - The `name` parameter must not include the '=' character.
 *   - The returned pointer points to memory within the `environ` array.
 *     Modifying this memory may affect the environment variables globally.
 *   - This function does not perform memory allocation; the caller must not
 *     free the returned pointer.
 *
 * Example:
 *   char *path = _getenv("PATH");
 *   if (path != NULL)
 *       printf("PATH: %s\n", path);
 *   else
 *       printf("PATH variable not found.\n");
 *
 */
char *_getenv(const char *name)
{
	int i;
	size_t name_len;

	if (name == NULL || environ == NULL)
		return (NULL);

	name_len = strlen(name);

	for (i = 0 ; environ[i] != NULL ; i++)
	{
		if (strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=')
		{
			return (&environ[i][name_len + 1]);
		}
	}
	return (NULL);
}
