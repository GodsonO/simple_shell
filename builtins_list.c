#include "shell.h"
/**
 * builtins_list - search list
 * @data: struct for the program's data
 * Return: return of the function executed if there is a match,
 * otherwise returns -1.
 **/
int builtins_list(data_of_program *data)
{
	int cursor;
	builtins options[] = {
		{"exit", builtin_exit},
		{"help", builtin_help},
		{"cd", builtin_cd},
		{"alias", builtin_alias},
		{"env", builtin_env},
		{"setenv", builtin_set_env},
		{"unsetenv", builtin_unset_env},
		{NULL, NULL}
	};

/*walk through the structure*/
	for (cursor = 0; options[cursor].builtin != NULL; cursor++)
	{
/*if there is a match between the given command and a builtin,*/
		if (str_compare(options[cursor].builtin, data->command_name, 0))
		{
/*execute the function, and return the return value of the function*/
			return (options[cursor].function(data));
		}
/*if there is no match return -1 */
	}
	return (-1);
}
