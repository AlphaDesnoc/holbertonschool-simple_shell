#include "main.h"

/**
 * _error - Prints an error message to standard error and returns failure code
 *
 * This function utilizes `perror` to print a predefined error message
 * ("./hsh - not found") to the standard error stream (`stderr`). It then
 * returns `EXIT_FAILURE`, indicating an unsuccessful operation.
 *
 * Return:
 *   - EXIT_FAILURE: A macro typically defined as 1, representing failure.
 *
 * Notes:
 *   -The `perror` function appends a description of the last error encountered
 *     (stored in the `errno` global variable) to the provided string, followed
 *     by a newline.
 *   -This function does not take any parameters and has no dependencies
 *     on external input.
 *
 * Example:
 *   if (some_condition_failed())
 *   {
 *       return (_error());
 *   }
 *
 * Caveats:
 *   - The function does not modify `errno`; it merely reports the last error.
 *   - The error message is hardcoded and may not be relevant for all contexts.
 */
int _error(void)
{
	perror("./hsh - not found");
	return (EXIT_FAILURE);
}

