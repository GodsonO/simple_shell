#include "shell.h"
/**
* _getline - read one line from screen.
* @data: struct for the program's data
* Return: counting bytes.
*/
int _getline(data_of_program *data)
{
	char buff[BUFFER_SIZE] = {'\0'};
	static char *command[10] = {NULL};
	static char operator[10] = {'\0'};
	ssize_t bytes_read, x = 0;

	/* check if doesnot exist more commands in the array */
	/* and checks the logical operators */
	if (!command[0] || (operator[0] == '&' && errno != 0) ||
		(operator[0] == '|' && errno == 0))
	{
		/*free the memory allocated in the array if it exists */
		for (x = 0; command[x]; x++)
		{
			free(command[x]);
			command[x] = NULL;
		}

		/* read from the file descriptor int to buff */
		bytes_read = read(data->file_descriptor, &buff, BUFFER_SIZE - 1);
		if (bytes_read == 0)
			return (-1);

		/* split lines for \n or ; */
		x = 0;
		do {
			command[x] = str_duplicate(_strtok(x ? NULL : buff, "\n;"));
			/*checks and split for && and || operators*/
			x = check_logic_ops(command, x, operator);
		} while (command[x++]);
	}

	/*obtains the next command (command 0) and remove it for the array*/
	data->input_line = command[0];
	for (x = 0; command[x]; x++)
	{
		command[x] = command[x + 1];
		operator[x] = operator[x + 1];
	}

	return (str_length(data->input_line));
}


/**
* check_logic_ops - checks and split for && and || operators
* @array_commands: array of commands.
* @i: index in the commands to be checked
* @array_operators: array of the logical operators for each previous command
*
* Return: index of the last command in the array_commands.
*/
int check_logic_ops(char *array_commands[], int i, char array_operators[])
{
	char *temp = NULL;
	int y;

	/* checks for the & char in the command line*/
	for (y = 0; array_commands[i] != NULL  && array_commands[i][y]; y++)
	{
		if (array_commands[i][y] == '&' && array_commands[i][y + 1] == '&')
		{
			/* split the line when chars && was found */
			temp = array_commands[i];
			array_commands[i][y] = '\0';
			array_commands[i] = str_duplicate(array_commands[i]);
			array_commands[i + 1] = str_duplicate(temp + y + 2);
			i++;
			array_operators[i] = '&';
			free(temp);
			y = 0;
		}
		if (array_commands[i][y] == '|' && array_commands[i][y + 1] == '|')
		{
			/* split the line when chars || was found */
			temp = array_commands[i];
			array_commands[i][y] = '\0';
			array_commands[i] = str_duplicate(array_commands[i]);
			array_commands[i + 1] = str_duplicate(temp + y + 2);
			i++;
			array_operators[i] = '|';
			free(temp);
			y = 0;
		}
	}
	return (i);
}
