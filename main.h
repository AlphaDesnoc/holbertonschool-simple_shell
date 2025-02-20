#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

int path_finder(char *cmd, char *work_buffer);
int file_checker(char *file);
int execute_cmd(char *argv[]);
char **token_args(char *input_buffer);
void print_env(void);
int _error(void);
char *_getenv(const char *name);

#endif

