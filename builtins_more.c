#include "shell.h"
/**
 * builtin_exit - exit of the program
 * @data: struct for the program's data
 * Return: 0 on sucess, or other number
 */
int builtin_exit(data_of_program *data)
{
	int a;

	if (data->tokens[1] != NULL)
	{/*if exists arg for exit, check if is a number*/
		for (a = 0; data->tokens[1][a]; a++)
			if ((data->tokens[1][a] < '0' || data->tokens[1][a] > '9')
				&& data->tokens[1][a] != '+')
			{/*if is not a number*/
				errno = 2;
				return (2);
			}
		errno = _atoi(data->tokens[1]);
	}
	free_all_data(data);
	exit(errno);
}

/**
 * builtin_cd - changes the current directory
 * @data: struct for the program's data
 * Return: 0 on success, or otherwise if its declared in the arguments
 */
int builtin_cd(data_of_program *data)
{
	char *home_dir = env_get_key("HOME", data), *old_dir = NULL;
	char dir_old[128] = {0};
	int error_num = 0;

	if (data->tokens[1])
	{
		if (str_compare(data->tokens[1], "-", 0))
		{
			old_dir = env_get_key("OLDPWD", data);
			if (old_dir)
				error_num = set_work_directory(data, old_dir);
			_print(env_get_key("PWD", data));
			_print("\n");

			return (error_num);
		}
		else
		{
			return (set_work_directory(data, data->tokens[1]));
		}
	}
	else
	{
		if (!home_dir)
			home_dir = getcwd(dir_old, 128);

		return (set_work_directory(data, home_dir));
	}
	return (0);
}

/**
 * set_work_directory - sets the work directory
 * @data: struct for the program's data
 * @new_dir: path to be set as work directory
 * Return: 0 on success, or otherwise
 */
int set_work_directory(data_of_program *data, char *new_dir)
{
	char dir_old[128] = {0};
	int err_num = 0;

	getcwd(dir_old, 128);

	if (!str_compare(dir_old, new_dir, 0))
	{
		err_num = chdir(new_dir);
		if (err_num == -1)
		{
			errno = 2;
			return (3);
		}
		env_set_key("PWD", new_dir, data);
	}
	env_set_key("OLDPWD", dir_old, data);
	return (0);
}

/**
 * builtin_help - shows the environment where the shell runs
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int builtin_help(data_of_program *data)
{
	int a, len = 0;
	char *mensages[6] = {NULL};

	mensages[0] = HELP_MSG;

	/* validate args */
	if (data->tokens[1] == NULL)
	{
		_print(mensages[0] + 6);
		return (1);
	}
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	mensages[1] = HELP_EXIT_MSG;
	mensages[2] = HELP_ENV_MSG;
	mensages[3] = HELP_SETENV_MSG;
	mensages[4] = HELP_UNSETENV_MSG;
	mensages[5] = HELP_CD_MSG;

	for (a = 0; mensages[a]; a++)
	{
		len = str_length(data->tokens[1]);
		if (str_compare(data->tokens[1], mensages[a], len))
		{
			_print(mensages[a] + len + 1);
			return (1);
		}
	}
	/*if there is no match, print error */
	errno = EINVAL;
	perror(data->command_name);
	return (0);
}

/**
 * builtin_alias - the program add, remove or show aliases
 * @data: struct for the program's data
 * Return: 0 on success, or otherwise
 */
int builtin_alias(data_of_program *data)
{
	int a = 0;

	/* if there are no arguments, print all environment */
	if (data->tokens[1] == NULL)
		return (print_alias(data, NULL));

	while (data->tokens[++a])
	{/* if there are arguments, print each env variable*/
		if (count_characters(data->tokens[a], "="))
			set_alias(data->tokens[a], data);
		else
			print_alias(data, data->tokens[a]);
	}

	return (0);
}
