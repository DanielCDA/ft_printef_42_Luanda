/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danagost <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 17:35:01 by danagost          #+#    #+#             */
/*   Updated: 2026/09/01 10:35:53 by danagost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_check_specifier(char spec, va_list *args)
{
	if (spec == 'c')
		return (ft_putchar_fd(va_arg(*args, int), 1));
	if (spec == 's')
		return (ft_putstrn_fd(va_arg(*args, char *), 1));
	if (spec == 'p')
		return (ft_putptr_fd(va_arg(*args, void *), 1));
	if (spec == 'd' || spec == 'i')
		return (ft_putnbrint_fd(va_arg(*args, int), 1));
	if (spec == 'u')
		return (ft_putnbr_unsigned_fd(va_arg(*args, unsigned int), 1));
	if (spec == 'x' || spec == 'X')
		return (ft_puthex_fd(va_arg(*args, unsigned int), spec, 1));
	if (spec == '%')
		return (ft_putchar_fd('%', 1));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		len;

	if (!format)
		return (-1);
	len = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%' && *(format + 1))
		{
			format++;
			len += ft_check_specifier(*format, &args);
		}
		else
			len += ft_putchar_fd(*format, 1);
		format++;
	}
	va_end(args);
	return (len);
}
