/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:20:51 by memotyle          #+#    #+#             */
/*   Updated: 2024/10/21 13:06:12 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*sd;
	unsigned char	*sc;
	size_t			i;

	sd = (unsigned char *)dest;
	sc = (unsigned char *)src;
	i = 0;
	if ((!sd || !sc))
		return (NULL);
	while (i < n)
	{
		((char *)sd)[i] = ((char *)sc)[i];
		i++;
	}
	return (sd);
}

// void	*ft_memcpy(void *dst, const void *src, size_t n)
// {
// 	unsigned char		*d;
// 	const unsigned char	*s;

// 	d = (unsigned char *)dst;
// 	s = (const unsigned char *)src;
// 	while (n--)
// 		*d++ = *s++;
// 	return (dst);
// }
