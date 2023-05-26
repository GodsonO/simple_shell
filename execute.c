#include "shell.h"
/**
 * execute - execute a command using its entire path variables.
 * @data: a pointer to the program's data
 * Return: 0 on success, otherwise.
 */
int execute(data_of_program *data)
{
	int r_val = 0, stat;
	pid_t pidd;

	/* check for program in built ins */
	r_val = builtins_list(data);
	if (r_val != -1)/* if program was found in built ins */
		return (r_val);

	/* check for program file system */
	r_val = find_program(data);
	if (r_val)
	{/* if program not found */
		return (r_val);
	}
	else
	{/* if program was found */
		pidd = fork(); /* create a child process */
		if (pidd == -1)
		{ /* if the fork call failed */
			perror(data->command_name);
			exit(EXIT_FAILURE);
		}
		if (pidd == 0)
		{/* I am the child process, I execute the program*/
			r_val = execve(data->tokens[0], data->tokens, data->env);
			if (r_val == -1) /* if error when execve*/
				perror(data->command_name), exit(EXIT_FAILURE);
		}
		else
		{/* I am the father, I wait and check the exit status of the child */
			wait(&stat);
			if (WIFEXITED(stat))
				errno = WEXITSTATUS(stat);
			else if (WIFSIGNALED(stat))
				errno = 128 + WTERMSIG(stat);
		}
	}
	return (0);
}
