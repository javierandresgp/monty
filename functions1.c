#include "monty.h"
/**
 * _get_opcode - funtion to select the opcode to be used.
 * @name: opcode to find.
 * @stack: doubly linked list.
 * @line_number: number of line.
 * Return: EXIT_FAILURE if fail.
 */
void _get_opcode(stack_t **stack, unsigned int line_number, char *name)
{
	int i;

	instruction_t select[] = {
		{"push", _push},
		{"pall", _pall},
		{NULL, NULL}
	};

	i = 0;
	while (select[i].opcode)
	{
		if (strcmp(select[i].opcode, name) == 0)
		{
			select[i].f(stack, line_number);
			break;
		}
		i++;
	}
	if (!select[i].opcode)
	{
		fprintf(stderr, "L%d: unknown instruction %s\n", line_number, name);
		_freedom((*stack));
		exit(EXIT_FAILURE);
	}
}
/**
 * _freedom - function that free a list.
 * @stack: doubly linked list.
 * Return: nothing.
 */
void _freedom(stack_t *stack)
{
	stack_t *tmp;

	while (stack != NULL)
	{
		tmp = stack->next;
		free(stack);
		stack = tmp;
	}
	fclose(ready.file);
	free(ready.buffer);
}
/**
 * _split - function that generates tokens
 * @buffer: buffer that keeps lines
 * @stack: Doubly linked list that makes the stack
 * @line_number: Counter of lines in the file
 * Return: nothing
 */
void _split(char *buffer, stack_t **stack, unsigned int line_number)
{
	char *name;
	char *tmp;

	name = strtok(buffer, " \n\t");
	tmp = strtok(NULL, " \n\t");
	ready.data = tmp;
	if (name && name[0] != '#')
	{
		_get_opcode(stack, line_number, name);
	}
}
/**
 * _isdigit - function that checks for a digit (0 through 9).
 * @c: is the character input
 * Return: 1 if c is a digit, return 0 otherwise
 */
int _isdigit(int c)
{
	int i;

	for (i = 48; i <= 57; i++)
	{
		if (i == c)
		{
			return (1);
		}
	}
	return (0);
}
