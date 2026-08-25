#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

int	ft_puthex_fd(unsigned long n, char c, int fd);
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
        return (i + 2);
    }
    else if (format == 'p')
    {
        void *ptr = va_arg(*args, void *);
        if (ptr == NULL)
        {
            ft_putstr_fd("0x0", 1);
            return 3;
        }
        else
        {
            ft_putstr_fd("0x", 1);
            int i = ft_puthex_fd((unsigned long)ptr, 'x', 1);
            return i + 2;
        }
    }
    else if (format == 'u')
    {
        unsigned int num = va_arg(*args, unsigned int);
        char buffer[20]; // Buffer to hold the string representation of the number
        int i = 0;

        if (num == 0)
        {
            ft_putchar_fd('0', 1);
            return 1;
        }

        while (num > 0)
        {
            buffer[i++] = (num % 10) + '0';
            num /= 10;
        }

        // Print the number in reverse order
        

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
   // ft_printf("Hello, %s! You have %d new messages. %% %c %X\n", name, messages, 'A', 15);
    ft_printf("Hello, %s! You have %d new messages. %% %c %x %p\n", name, messages, 'A', 15, (void *)16);
    printf("\n+============================================================================+\n");
   int p = printf("Hello, %s! You have %d new messages. %% %c %x %p\n", name, messages, 'A', 15, (void *)16);
   //printf("Hello, %s! You have %d new messages. %% %c %X\n", name, p, 'A', 15);
    
   return 0;
}