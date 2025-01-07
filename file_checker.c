#include "main.h"

/**
 * file_checker - Checks if a file exists and is accessible.
 *
 * @file: A pointer to a null-terminated string representing the file path.
 *
 * This function uses the `stat` system call to determine if the specified file
 * exists and is accessible. If the `stat` call succeeds, the function returns
 * `EXIT_SUCCESS`. Otherwise, it returns `EXIT_FAILURE`.
 *
 * Return:
 *   - EXIT_SUCCESS (commonly 0): If the file exists and is accessible.
 *   - EXIT_FAILURE (commonly 1): If the file does not exist or is inaccessible
 *
 * Notes:
 *   -The function checks for the existence of a file or directory but does not
 *     verify specific permissions (e.g., read/write access).
 *   -The `stat` function populates a struct stat with metadata about the file
 *     but this information is not used by file_checker.
 *   -The caller must ensure the `file` argument is a valid, non-NULL string.
 *
 * Example:
 *   if (file_checker("/path/to/file") == EXIT_SUCCESS)
 *       printf("File exists.\n");
 *   else
 *       printf("File does not exist or is inaccessible.\n");
 *
 */
int file_checker(char *file)
{
	struct stat st;

	if (stat(file, &st) == 0)
		return (EXIT_SUCCESS);

	return (EXIT_FAILURE);
}

