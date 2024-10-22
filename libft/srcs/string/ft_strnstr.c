/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melinamotylewski <melinamotylewski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:58:26 by memotyle          #+#    #+#             */
/*   Updated: 2024/09/25 17:57:27 by melinamotyl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *chaineP, const char *SousChaine, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*SousChaine == '\0')
		return ((char *)chaineP);
	while (chaineP[i] && i < len)
	{
		j = 0;
		while (chaineP[i + j] == SousChaine[j] && i + j < len)
		{
			if (!SousChaine[j + 1])
				return ((char *)chaineP + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
