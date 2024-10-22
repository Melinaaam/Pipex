/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melinamotylewski <melinamotylewski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:45:43 by memotyle          #+#    #+#             */
/*   Updated: 2024/09/25 18:28:50 by melinamotyl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	if ((dest == NULL) || (src == NULL))
		return (0);
	i = 0;
	while (src[i])
		i++;
	if (n == 0)
		return (i);
	while (*src && --n)
		*dest++ = *src++;
	*dest = '\0';
	return (i);
}
