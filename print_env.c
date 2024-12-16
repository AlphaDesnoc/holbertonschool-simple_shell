#include "main.h"

/**
 * print_env - Prints the current environment variables to standard output.
 *
 * This function iterates over the `environ` array, which contains the current
 * environment variables of the process. For each entry in `environ`, it prints
 * the variable in the format "name=value" to standard output (`stdout`).
 *
 * Return:
 *   - None.
 *
 * Notes:
 *   - The `environ` array is globally available in a POSIX environment and
 *     contains null-terminated strings in the format "name=value".
 *   - The function uses a simple loop to print each environment variable.
 *   - Each entry in `environ` must be a valid, non-NULL string.
 *
 * Example:
 *   $ ./hsh
 *   PATH=/usr/bin:/bin:/usr/sbin:/sbin
 *   HOME=/home/user
 *   ...
 *
 * Caveats:
 *   - The function does not check for errors or handle failure cases.
 *   - Modifying or freeing the environment variables in `environ` is not
 *     allowed as it may affect the process's environment globally.
 *   - The function assumes a POSIX-compliant environment.
 */
void print_env(void)
{
	int ctr_env = 0;

	while (environ[ctr_env] != NULL)
	{
		printf("%s\n", environ[ctr_env]);
		ctr_env++;
	}
}
