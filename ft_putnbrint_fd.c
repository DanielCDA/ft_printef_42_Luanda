/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrint_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danagost <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 14:55:21 by danagost          #+#    #+#             */
/*   Updated: 2026/09/01 10:44:35 by danagost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_putnbrint_fd(int nb, int fd)
{
	int	cont;

	cont = 0;
	if (nb == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		cont++;
		nb *= -1;
	}
	if (nb > 9)
		cont += ft_putnbrint_fd(nb / 10, 1);
	ft_putchar_fd((nb % 10) + '0', fd);
	cont++;
	return (cont);
}
