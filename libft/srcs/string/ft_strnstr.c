/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:58:26 by memotyle          #+#    #+#             */
/*   Updated: 2024/10/29 14:55:18 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big_s, const char *little_s, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	if (!big_s || len == 0)
		return (NULL);
	if (little_s[0] == '\0')
		return ((char *)big_s);
	i = 0;
	while (big_s[i] && i < len)
	{
		j = 0;
		if (little_s[j] == big_s[i])
		{
			while (little_s[j] == big_s[i + j] && i + j < len)
			{
				j++;
				if (!little_s[j])
					return ((char *)&big_s[i]);
			}
		}
		i++;
	}
	return (NULL);
}
