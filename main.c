#include "shell.h"
/**
 * main - implements a unix cmd interpreter
 * @argc: num of values received from the command line
 * @argv: values received from the command line
 * @env: num of values received from the command line
 * Return: 0
 */
int main(int argc, char *argv[], char *env[])
{
	data_of_program data_struct = {NULL}, *data = &data_struct;
	char *prompt = "";

	inicialize_data(data, argc, argv, env);

	signal(SIGINT, handle_ctrl_c);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{/* interactive mode */
		errno = 2;
		prompt = PROMPT_MSG;
	}
	errno = 0;
	sisifo(prompt, data);
	return (0);
}

/**
 * handle_ctrl_c - print the prompt in a new line
 * @UNUSED: an integer
 */
void handle_ctrl_c(int opr UNUSED)
{
	_print("\n");
	_print(PROMPT_MSG);
}

/**
 * inicialize_data - initialize the struct with the info
 * @data: pointer to the structure of data
 * @argv: array of arguments
 * @env: environ pased to the program execution
 * @argc: num of val received from d command line
 */
void inicialize_data(data_of_program *data, int argc, char *argv[], char **env)
{
	int x = 0;

	data->program_name = argv[0];
	data->input_line = NULL;
	data->command_name = NULL;
	data->exec_counter = 0;
	/* define the file descriptor to be readed*/
	if (argc == 1)
		data->file_descriptor = STDIN_FILENO;
	else
	{
		data->file_descriptor = open(argv[1], O_RDONLY);
		if (data->file_descriptor == -1)
		{
			_printe(data->program_name);
			_printe(": 0: Can't open ");
			_printe(argv[1]);
			_printe("\n");
			exit(127);
		}
	}
	data->tokens = NULL;
	data->env = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[x]; x++)
		{
			data->env[x] = str_duplicate(env[x]);
		}
	}
	data->env[x] = NULL;
	env = data->env;

	data->alias_list = malloc(sizeof(char *) * 20);
	for (x = 0; x < 20; x++)
	{
		data->alias_list[x] = NULL;
	}
}
/**
 * sisifo - the program shows the prompt
 * @prompt: the prompt
 * @data: stores the prompt
 */
void sisifo(char *prompt, data_of_program *data)
{
	int string_len = 0, error_num = 0;

	while (++(data->exec_counter))
	{
		_print(prompt);
		error_num = string_len = _getline(data);

		if (error_num == EOF)
		{
			free_all_data(data);
			exit(errno); /* if EOF is the fisrt Char of string, exit*/
		}
		if (string_len >= 1)
		{
			expand_alias(data);
			expand_variables(data);
			tokenize(data);
			if (data->tokens[0])
			{ /* if a text is given to prompt, execute */
				error_num = execute(data);
				if (error_num != 0)
					_print_error(error_num, data);
			}
			free_recurrent_data(data);
		}
	}
}
