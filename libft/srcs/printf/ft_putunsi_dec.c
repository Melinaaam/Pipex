/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsi_dec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melinamotylewski <melinamotylewski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:15:17 by memotyle          #+#    #+#             */
/*   Updated: 2024/09/25 17:52:30 by melinamotyl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putunsi_dec(unsigned int nb)
{
	int		count;

	count = 0;
	if (nb > 9)
		count = count + ft_putnbr(nb / 10);
	count = count + ft_putchar((nb % 10) + '0');
	return (count);
}
