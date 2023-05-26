#include "shell.h"
/**
 * builtin_env - shows the environment where the shell runs
 * @data: struct for the program's data
 * Return: 0 on success, or otherwise
 */
int builtin_env(data_of_program *data)
{
	int x;
	char name_cp[50] = {'\0'};
	char *varcopy = NULL;

	/* if not arguments */
	if (data->tokens[1] == NULL)
		print_environ(data);
	else
	{
		for (x = 0; data->tokens[1][x]; x++)
		{/* checks if exists a char = */
			if (data->tokens[1][x] == '=')
			{/* checks if exists a var with the same name and change its value*/
			/* temporally */
				varcopy = str_duplicate(env_get_key(name_cp, data));
				if (varcopy != NULL)
					env_set_key(name_cp, data->tokens[1] + x + 1, data);

				/* print the environ */
				print_environ(data);
				if (env_get_key(name_cp, data) == NULL)
				{/* print the variable if it does not exist in the environ */
					_print(data->tokens[1]);
					_print("\n");
				}
				else
				{/* returns the old value of the var*/
					env_set_key(name_cp, varcopy, data);
					free(varcopy);
				}
				return (0);
			}
			name_cp[x] = data->tokens[1][x];
		}
		errno = 2;
		perror(data->command_name);
		errno = 127;
	}
	return (0);
}

/**
 * builtin_set_env - set env
 * @data: struct for the program's data
 * Return: 0 on success, or otherwise
 */
int builtin_set_env(data_of_program *data)
{
	/* validate args */
	if (data->tokens[1] == NULL || data->tokens[2] == NULL)
		return (0);
	if (data->tokens[3] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}

	env_set_key(data->tokens[1], data->tokens[2], data);

	return (0);
}

/**
 * builtin_unset_env - unset env
 * @data: struct for the program's data'
 * Return: 0
 */
int builtin_unset_env(data_of_program *data)
{
	/* validate args */
	if (data->tokens[1] == NULL)
		return (0);
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	env_remove_key(data->tokens[1], data);

	return (0);
}
