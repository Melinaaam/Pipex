/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melinamotylewski <melinamotylewski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:32:30 by memotyle          #+#    #+#             */
/*   Updated: 2024/09/25 17:48:22 by melinamotyl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *destination, const void *source, size_t n)
{
	unsigned char			*dest;
	const unsigned char		*src;

	dest = (unsigned char *)destination;
	src = (const unsigned char *)source;
	if (src == dest || n == 0)
		return (dest);
	if (dest > src && dest < src + n)
	{
		while (n--)
			dest[n] = src[n];
	}
	else
		ft_memcpy(dest, src, n);
	return (destination);
}
