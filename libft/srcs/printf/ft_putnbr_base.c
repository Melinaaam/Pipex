/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putn_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:07:34 by memotyle          #+#    #+#             */
/*   Updated: 2024/06/14 19:46:08 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_base(char *base, int n)
{
	unsigned long long	nb;
	int					count;
	unsigned int		base_len;

	count = 0;
	base_len = ft_strlen(base);
	if (n < 0)
		nb = n + 4294967295 + 1;
	else
		nb = (unsigned long long)n;
	if (nb >= base_len)
		count += ft_putnbr_base(base, nb / base_len);
	count += ft_putchar(base[nb % base_len]);
	return (count);
}
