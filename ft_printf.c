#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

int	ft_puthex_fd(unsigned int n, char c, int fd);
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
    else if (format == 'x' || format == 'X')
    {
        int i;
        if (format == 'x')
            ft_putstr_fd("0x", 1);
        else if (format == 'X')
            ft_putstr_fd("0X", 1);
        i = ft_puthex_fd(va_arg(*args, unsigned int), format, 1);
        return i;
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
    ft_printf("Hello, %s! You have %d new messages. %% %c %X\n", name, messages, 'A', 25);
    ft_printf("Hello, %s! You have %d new messages. %% %c %x\n", name, messages, 'A', 25);
    printf("\n+============================================================================+\n");
    printf("Hello, %s! You have %d new messages. %% %c %x\n", name, messages, 'A', 25);
    printf("Hello, %s! You have %d new messages. %% %c %X\n", name, messages, 'A', 25);
    return 0;
}