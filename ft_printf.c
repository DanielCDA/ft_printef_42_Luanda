#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char c, int fd);

int indentificador(const char format, va_list args)
{
    int num;
    char *str;

    if (format == 'd')
    {
        num = va_arg(args, int);
        ft_putnbr_fd(num, 1);
        return 1;
    }
    else if (format == 's')
    {
        str = va_arg(args, char *);
        ft_putstr_fd(str, 1);
        return 1;
    }
    return 0;
}
int ft_printf(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    int count = 0;

    while (*format)
    {
        if (*format == '%')
        {
            format++;
            count += indentificador(*format, args);
        }
        else
        {
            ft_putchar_fd(*format, 1);
            count++;
        }
        format++;
    }
    va_end(args);
    return count;
}

int main()
{
    ft_printf("Hello, %s! You have %dd new messages.\n", "Alice", -5);
    return 0;
}