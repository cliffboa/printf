#include "main.h"

/**
 * handle_print - Handles printing based on the format specifier.
 * @fmt: Formatted string in which to print the arguments.
 * @ind: Pointer to an integer that serves as an index in the format string.
 * @list: va_list containing the list of arguments.
 * @buffer: Buffer array to handle the print.
 * @flags: Integer representing the active flags.
 * @width: Width specifier.
 * @precision: Precision specifier.
 * @size: Size specifier.
 *
 * This function handles printing based on the format specifier. It checks the
 * format specifier and calls the corresponding print function to handle the
 * printing of the respective data type. It supports various format specifiers
 * such as 'c', 's', '%', 'i', 'd', 'b', 'u', 'o', 'x', 'X', 'p', 'S', 'r', and 'R'.
 *
 * Return: The number of characters printed on success, -1 if an unknown specifier
 * is encountered, or 1 if the specifier is '%' and followed by space or width.
 */
int handle_print(const char *fmt, int *ind, va_list list, char buffer[],
                 int flags, int width, int precision, int size)
{
	int i, unknown_len = 0, printed_chars = -1;
	fmt_t fmt_types[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};

	for (i = 0; fmt_types[i].fmt != '\0'; i++)
	{
		if (fmt[*ind] == fmt_types[i].fmt)
			return (fmt_types[i].fn(list, buffer, flags, width, precision, size));
	}

	if (fmt_types[i].fmt == '\0')
	{
		if (fmt[*ind] == '\0')
			return (-1);

		unknown_len += write(1, "%%", 1);

		if (fmt[*ind - 1] == ' ')
			unknown_len += write(1, " ", 1);
		else if (width)
		{
			--(*ind);
			while (fmt[*ind] != ' ' && fmt[*ind] != '%')
				--(*ind);

			if (fmt[*ind] == ' ')
				--(*ind);
			return (1);
		}

		unknown_len += write(1, &fmt[*ind], 1);
		return (unknown_len);
	}

	return (printed_chars);
}

