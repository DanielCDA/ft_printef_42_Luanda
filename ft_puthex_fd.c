/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danagost <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/27 10:41:51 by danagost          #+#    #+#             */
/*   Updated: 2026/09/01 10:47:20 by danagost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

char	*ft_preenh_fd(char c)
{
	char	*hex;

	hex = NULL;
	if (c == 'X')
		hex = "0123456789ABCDEF";
	else
		hex = "0123456789abcdef";
	return (hex);
}

int	ft_puthex_fd(unsigned int n, char c, int fd)
{
	char	*hex;
	int		cont;

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
