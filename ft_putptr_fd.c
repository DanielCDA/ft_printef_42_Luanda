/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danagost <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 16:21:25 by danagost          #+#    #+#             */
/*   Updated: 2026/09/01 11:06:28 by danagost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static int	ft_putptr_hex(unsigned long n)
{
	char	*base;
	int		cont;

	cont = 0;
	base = "0123456789abcdef";
	if (n >= 16)
		cont += ft_putptr_hex(n / 16);
	cont += ft_putchar_fd(base[n % 16], 1);
	return (cont);
}

int	ft_putptr_fd(void *ptr, int fd)
{
	unsigned long	addr;
	int				cont;

	(void)fd;
	if (!ptr)
		return (ft_putstrn_fd("(nil)", 1));
	cont = 0;
	addr = (unsigned long)ptr;
	cont += ft_putstrn_fd("0x", 1);
	cont += ft_putptr_hex(addr);
	return (cont);
}
