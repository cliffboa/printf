#include "main.h"
#include <ctype.h>

/**
 * get_width - Calculates the width for printing.
 * @format: Formatted string in which to print the arguments.
 * @i: Pointer to an integer that serves as an index in the format string.
 * @list: va_list containing the list of arguments.
 *
 * This function parses the format string to determine the width specified for
 * printing. The width can be either a non-negative integer or an asterisk (*)
 * indicating that the width is passed as an argument in the list.
 *
 * Return: The calculated width value.
 */
int get_width(const char *format, int *i, va_list list)
{
	int curr_i;
	int width = 0;

	/* Loop through the format string to extract the width. */
	for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
	{
		/* If the character is a digit, calculate the width value. */
		if (isdigit(format[curr_i]))
		{
			width *= 10;
			width += format[curr_i] - '0';
		}
		/* If the character is an asterisk (*), get the width from the va_list. */
		else if (format[curr_i] == '*')
		{
			curr_i++;
			width = va_arg(list, int);
			break;
		}
		/* If the character is not a digit or an asterisk, stop parsing. */
		else
			break;
	}

	/* Update the index to the last character used for width parsing. */
	*i = curr_i - 1;

	/* Return the calculated width value. */
	return (width);
}

