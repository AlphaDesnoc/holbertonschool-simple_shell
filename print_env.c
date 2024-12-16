#include "main.h"

void print_env(void)
{
	int ctr_env = 0;

	while (environ[ctr_env] != NULL)
	{
		printf("%s\n", environ[ctr_env]);
		ctr_env++;
	}
}
