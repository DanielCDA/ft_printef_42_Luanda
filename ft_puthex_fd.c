# include "libft.h"

char    *ft_preenh_fd(char c)
{
    char    *hex;

    if (c == 'X')
        hex = "0123456789ABCDEF";
    else if (c == 'x')
        hex = "0123456789abcdef";
    return (hex);
}

int    ft_puthex_fd(unsigned int n, char c, int fd)
{
    char    *hex;
    int cont;

    cont = 0;
    if (n > 15)
    {
        cont += ft_puthex_fd(n / 16, c, fd);
        cont += ft_puthex_fd(n % 16, c, fd);
    }
    else
    {
        hex = ft_preenh_fd(c);
        ft_putchar_fd(hex[n], fd);
        cont++;
    }
    return (cont);
}