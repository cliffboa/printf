#include "main.h"

/**
 * handle_write_char - Writes a character to the buffer and handles padding.
 * @c: The character to be printed.
 * @buffer: Buffer array to handle print.
 * @flags: Active flags.
 * @width: Width specifier.
 * @precision: Precision specifier.
 * @size: Size specifier (unused in this function).
 *
 * Return: Number of characters printed.
 */
int handle_write_char(char c, char buffer[],
                      int flags, int width, int precision, int size)
{
    /* The char is stored at the left and padding at the buffer's right */
    int i = 0;
    char padd = ' ';

    UNUSED(precision);
    UNUSED(size);

    if (flags & F_ZERO)
        padd = '0';

    buffer[i++] = c;
    buffer[i] = '\0';

    if (width > 1)
    {
        buffer[BUFF_SIZE - 1] = '\0';
        for (i = 0; i < width - 1; i++)
            buffer[BUFF_SIZE - i - 2] = padd;

        if (flags & F_MINUS)
            return (write(1, &buffer[0], 1) +
                    write(1, &buffer[BUFF_SIZE - i - 1], width - 1));
        else
            return (write(1, &buffer[BUFF_SIZE - i - 1], width - 1) +
                    write(1, &buffer[0], 1));
    }

    return (write(1, &buffer[0], 1));
}

/**
 * write_number - Writes a number to the buffer and handles padding.
 * @is_negative: 1 if the number is negative, 0 otherwise.
 * @ind: Index at which the number starts on the buffer.
 * @buffer: Buffer array to handle print.
 * @flags: Active flags.
 * @width: Width specifier.
 * @precision: Precision specifier.
 * @size: Size specifier (unused in this function).
 *
 * Return: Number of characters printed.
 */
int write_number(int is_negative, int ind, char buffer[],
                 int flags, int width, int precision, int size)
{
    int length = BUFF_SIZE - ind - 1;
    char padd = ' ', extra_ch = 0;

    UNUSED(size);

    if ((flags & F_ZERO) && !(flags & F_MINUS))
        padd = '0';
    if (is_negative)
        extra_ch = '-';
    else if (flags & F_PLUS)
        extra_ch = '+';
    else if (flags & F_SPACE)
        extra_ch = ' ';

    return (write_num(ind, buffer, flags, width, precision,
                      length, padd, extra_ch));
}

/* Other functions like write_num and write_unsgnd follow... */

