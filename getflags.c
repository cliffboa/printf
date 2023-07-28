#include "main.h"

/**
 * get_flags - Calculates active flags based on the format string.
 * @format: Formatted string in which to print the arguments.
 * @i: Pointer to an integer that serves as an index in the format string.
 *
 * This function parses the format string to identify and calculate the active flags
 * that are specified in the format.
 *
 * Return: The calculated flags based on the format string.
 */
int get_flags(const char *format, int *i)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int j, curr_i;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	/* Loop through the format string starting from the current index. */
	for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
	{
		/* Check if the character at the current index matches any flag character. */
		for (j = 0; FLAGS_CH[j] != '\0'; j++)
		{
			if (format[curr_i] == FLAGS_CH[j])
			{
				/* Set the corresponding flag based on the found character. */
				flags |= FLAGS_ARR[j];
				break;
			}
		}

		/* If no matching flag character is found, exit the loop. */
		if (FLAGS_CH[j] == '\0')
			break;
	}

	/* Update the index to the last character used for flag parsing. */
	*i = curr_i - 1;

	/* Return the calculated flags based on the format string. */
	return (flags);
}

