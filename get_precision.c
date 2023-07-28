#include <ctype.h>
#include "main.h"

/**
 * get_precision - Calculates the precision for printing.
 * @format: Formatted string in which to print the arguments.
 * @i: Pointer to an integer that serves as an index in the format string.
 * @list: va_list containing the list of arguments.
 *
 * This function parses the format string to determine the precision specified
 * for printing. The precision can be either a non-negative integer or an asterisk
 * (*) indicating that the precision is passed as an argument in the list.
 *
 * Return: The calculated precision value.
 */
int get_precision(const char *format, int *i, va_list list)
{
	int curr_i = *i + 1;
	int precision = -1;

	/* Check if the format string contains a precision specifier. */
	if (format[curr_i] != '.')
		return (precision);

	precision = 0;

	/* Loop through the format string to extract the precision. */
	for (curr_i += 1; format[curr_i] != '\0'; curr_i++)
	{
		/* If the character is a digit, calculate the precision value. */
		if (isdigit(format[curr_i]))
		{
			precision *= 10;
			precision += format[curr_i] - '0';
		}
		/* If the character is an asterisk (*), get the precision from the va_list. */
		else if (format[curr_i] == '*')
		{
			curr_i++;
			precision = va_arg(list, int);
			break;
		}
		/* If the character is not a digit or an asterisk, stop parsing. */
		else
			break;
	}

	/* Update the index to the last character used for precision parsing. */
	*i = curr_i - 1;

	/* Return the calculated precision value. */
	return (precision);
}

