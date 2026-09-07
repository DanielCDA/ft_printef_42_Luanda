/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned_fd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danagost <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 18:07:38 by danagost          #+#    #+#             */
/*   Updated: 2026/09/01 10:46:39 by danagost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_putnbr_unsigned_fd(unsigned int nb, int fd)
{
	int	cont;

	cont = 0;
	if (nb > 9)
		cont += ft_putnbr_unsigned_fd(nb / 10, fd);
	ft_putchar_fd((nb % 10) + '0', fd);
	cont++;
	return (cont);
}
