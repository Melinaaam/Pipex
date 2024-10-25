/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:54:53 by memotyle          #+#    #+#             */
/*   Updated: 2024/10/24 16:18:52 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char *s1, char *s2)
{
	char	*fusion;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	fusion = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!fusion)
		return (NULL);
	i = -1;
	while (s1[++i])
		fusion[i] = s1[i];
	j = 0;
	while (s2[j])
		fusion[i++] = s2[j++];
	fusion[i] = '\0';
	// free(s1);
	return (fusion);
}
