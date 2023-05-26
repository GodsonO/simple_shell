#include "shell.h"
/**
 * free_recurrent_data - free data
 * @data: struct of the program's data
 * Return: void
 */
void free_recurrent_data(data_of_program *data)
{
	if (data->tokens)
		free_array_of_pointers(data->tokens);
	if (data->input_line)
		free(data->input_line);
	if (data->command_name)
		free(data->command_name);

	data->input_line = NULL;
	data->command_name = NULL;
	data->tokens = NULL;
}

/**
 * free_all_data - free all data
 * @data: struct of the program's data
 * Return: void
 */
void free_all_data(data_of_program *data)
{
	if (data->file_descriptor != 0)
	{
		if (close(data->file_descriptor))
			perror(data->program_name);
	}
	free_recurrent_data(data);
	free_array_of_pointers(data->env);
	free_array_of_pointers(data->alias_list);
}

/**
 * free_array_of_pointers - frees each pointer of an array of pointers
 * @array: array of pointers
 * Return: void
 */
void free_array_of_pointers(char **array)
{
	int x;

	if (array != NULL)
	{
		for (x = 0; array[x]; x++)
			free(array[x]);

		free(array);
		array = NULL;
	}
}
