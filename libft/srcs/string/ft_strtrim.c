/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melinamotylewski <melinamotylewski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:31:21 by memotyle          #+#    #+#             */
/*   Updated: 2024/09/25 17:58:35 by melinamotyl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ns;
	size_t	start;
	size_t	end;

	start = 0;
	end = ft_strlen((char *)s1);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	if (start != end || start >= end)
	{
		while (end > start && ft_strchr(set, s1[end - 1]))
			end--;
	}
	ns = malloc(end - start + 1);
	if (!ns)
		return (NULL);
	ft_strlcpy (ns, &s1[start], end - start + 1);
	ns[end - start] = '\0';
	return (ns);
}
