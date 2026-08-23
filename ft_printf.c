#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char c, int fd);

int indentificador(const char format, va_list *args)
{
    if (format == 'd')
    {
        ft_putnbr_fd(va_arg(*args, int), 1);
        return 1;
    }
    else if (format == 's')
    {
        ft_putstr_fd(va_arg(*args, char *), 1);
        return 1;
    }
    else if (format == 'c')
    {
        ft_putchar_fd((char)va_arg(*args, int), 1);
        return 1;
    } 
    else if (format == '%')
    {
        ft_putchar_fd('%', 1);
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
            count += indentificador(*format, &args);
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
    char *name = "Alice";
    int messages = 5;
    ft_printf("Hello, %s! You have %d new messages. %% %c\n", name, messages, 'A');
    return 0;
}