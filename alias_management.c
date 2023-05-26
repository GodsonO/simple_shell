#include "shell.h"
/**
 * print_alias - a program that add, remove or show aliases
 * @data: struct for the program's data
 * @alias: the alias name to be printed
 * Return: 0
 */
int print_alias(data_of_program *data, char *alias)
{
	int y, alias_len, x;
	char buffer[250] = {'\0'};

	if (data->alias_list)
	{
		alias_len = str_length(alias);
		for (x = 0; data->alias_list[x]; x++)
		{
			if (!alias || (str_compare(data->alias_list[x], alias, alias_len)
				&&	data->alias_list[x][alias_len] == '='))
			{
				for (y = 0; data->alias_list[x][y]; y++)
				{
					buffer[y] = data->alias_list[x][y];
					if (data->alias_list[x][y] == '=')
						break;
				}
				buffer[y + 1] = '\0';
				buffer_add(buffer, "'");
				buffer_add(buffer, data->alias_list[x] + y + 1);
				buffer_add(buffer, "'\n");
				_print(buffer);
			}
		}
	}

	return (0);
}

/**
 * get_alias - get alias
 * @data: struct for the program's data
 * @name: name of the requested alias.
 * Return: 0 on success, or other number
 */
char *get_alias(data_of_program *data, char *name)
{
	int x, alias_len;

	/* validate arguments */
	if (name == NULL || data->alias_list == NULL)
		return (NULL);

	alias_len = str_length(name);

	for (x = 0; data->alias_list[x]; x++)
	{/* moves through environ to check for coincidence of the var_name */
		if (str_compare(name, data->alias_list[x], alias_len) &&
			data->alias_list[x][alias_len] == '=')
		{/* returns the value of the key NAME=  when find it */
			return (data->alias_list[x] + alias_len + 1);
		}
	}
	/* returns NULL if did not find it */
	return (NULL);

}

/**
 * set_alias - the program add, or override alias
 * @alias_string: the alias
 * @data: struct for the program's data
 * Return: 0 on sucess, or other number
 */
int set_alias(char *alias_string, data_of_program *data)
{
	int x, y;
	char buffer[250] = {'0'}, *temp = NULL;

	/* validate the arguments */
	if (alias_string == NULL ||  data->alias_list == NULL)
		return (1);
	/* Iterates alias to find = char */
	for (x = 0; alias_string[x]; x++)
		if (alias_string[x] != '=')
			buffer[x] = alias_string[x];
		else
		{/* it checks if the value of the alias is another alias */
			temp = get_alias(data, alias_string + x + 1);
			break;
		}

	/* moves through the alias list and check for coincidence of the varname */
	for (y = 0; data->alias_list[y]; y++)
		if (str_compare(buffer, data->alias_list[y], x) &&
			data->alias_list[y][x] == '=')
		{/* if the alias alredy exist */
			free(data->alias_list[y]);
			break;
		}

	/* add the alias */
	if (temp)
	{/* if the alias already exist */
		buffer_add(buffer, "=");
		buffer_add(buffer, temp);
		data->alias_list[y] = str_duplicate(buffer);
	}
	else /* if the alias does not exist */
		data->alias_list[y] = str_duplicate(alias_string);
	return (0);
}
