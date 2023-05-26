#include "shell.h"

int check_file(char *full_path);

/**
 * find_program - find a program in path
 * @data: a pointer to the program's data
 * Return: 0 on success or otherwise
 */

int find_program(data_of_program *data)
{
	int a = 0, r_code = 0;
	char **directories;

	if (!data->command_name)
		return (2);

	/**if is a full_path or an executable in the same path */
	if (data->command_name[0] == '/' || data->command_name[0] == '.')
		return (check_file(data->command_name));

	free(data->tokens[0]);
	data->tokens[0] = str_concat(str_duplicate("/"), data->command_name);
	if (!data->tokens[0])
		return (2);

	directories = tokenize_path(data);/* search in the PATH */

	if (!directories || !directories[0])
	{
		errno = 127;
		return (127);
	}
	for (a = 0; directories[a]; a++)
	{/* appends the function_name to path */
		directories[a] = str_concat(directories[a], data->tokens[0]);
		r_code = check_file(directories[a]);
		if (r_code == 0 || r_code == 126)
		{/* the file was found, is not a directory and has execute permisions*/
			errno = 0;
			free(data->tokens[0]);
			data->tokens[0] = str_duplicate(directories[a]);
			free_array_of_pointers(directories);
			return (r_code);
		}
	}
	free(data->tokens[0]);
	data->tokens[0] = NULL;
	free_array_of_pointers(directories);
	return (r_code);
}

/**
 * tokenize_path - tokenize the path in the directory
 * @data: a pointer to the program's data
 * Return: array of path directories
 */

char **tokenize_path(data_of_program *data)
{
	int a = 0;
	int count_directories = 2;
	char **tokens = NULL;
	char *PATH;

	/* get the PATH value*/
	PATH = env_get_key("PATH", data);
	if ((PATH == NULL) || PATH[0] == '\0')
	{/*path not found*/
		return (NULL);
	}

	PATH = str_duplicate(PATH);

	/* find the number of directories in the PATH */
	for (a = 0; PATH[a]; a++)
	{
		if (PATH[a] == ':')
			count_directories++;
	}

	/* reserve space for the array of pointers */
	tokens = malloc(sizeof(char *) * count_directories);

	/*tokenize and duplicate each token of path*/
	a = 0;
	tokens[a] = str_duplicate(_strtok(PATH, ":"));
	while (tokens[a++])
	{
		tokens[a] = str_duplicate(_strtok(NULL, ":"));
	}

	free(PATH);
	PATH = NULL;
	return (tokens);

}

/**
 * check_file - checks for file
 * @full_path: pointer to the full file name
 * Return: 0 on success, or otherwise
 */

int check_file(char *full_path)
{
	struct stat sb;

	if (stat(full_path, &sb) != -1)
	{
		if (S_ISDIR(sb.st_mode) ||  access(full_path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}
	/*if not exit the file*/
	errno = 127;
	return (127);
}
