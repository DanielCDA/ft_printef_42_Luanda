# include "libft.h"

int    ft_puthex_fd(unsigned int n, int fd)
{
    char    *hex;
    int cont;

    cont = 0;
    if (n > 16)
    {
        cont += ft_puthex_fd(n / 16, fd);
        cont += ft_puthex_fd(n % 16, fd);
    }
    else
    {
        hex = "0123456789abcdef";
        ft_putchar_fd(hex[n], fd);
        cont++;
    }
    return (cont);
}