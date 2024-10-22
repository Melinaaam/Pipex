/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melinamotylewski <melinamotylewski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:38:49 by memotyle          #+#    #+#             */
/*   Updated: 2024/09/25 18:27:47 by melinamotyl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_attributions(va_list argument, char c)
{
	int	len;

	len = 0;
	if (c == 'c')
		len = len + ft_putchar(va_arg(argument, int));
	if (c == 's')
		len = len + ft_putstr(va_arg(argument, char *));
	if (c == 'd' || c == 'i')
		len = len + ft_putnbr(va_arg(argument, int));
	if (c == 'u')
		len = len + ft_putunsi_dec(va_arg(argument, unsigned int));
	if (c == 'X')
		len = len + ft_putnbr_base("0123456789ABCDEF", va_arg(argument, int));
	if (c == 'x')
		len = len + ft_putnbr_base("0123456789abcdef", va_arg(argument, int));
	if (c == 'p')
		len = len + ft_putptr(va_arg(argument, void *), "0123456789abcdef", 0);
	if (c == '%')
		len = len + ft_putchar('%');
	return (len);
}

int	ft_printf(const char *s, ...)
{
	int		i;
	va_list	argument;
	int		len_print;

	i = 0;
	len_print = 0;
	va_start(argument, s);
	while (s[i])
	{
		if (s[i] == '%')
		{
			len_print = len_print + ft_attributions(argument, s[i + 1]);
			i++;
		}
		else
			len_print = len_print + ft_putchar(s[i]);
		i++;
	}
	va_end(argument);
	return (len_print);
}
