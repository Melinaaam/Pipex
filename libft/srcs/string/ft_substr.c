/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:33:29 by memotyle          #+#    #+#             */
/*   Updated: 2024/09/27 17:20:31 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ns;
	size_t	len_s;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	len_s = ft_strlen((char *)s);
	if (start >= len_s)
		return ("");
	if (len > len_s - start)
		len = len_s - start;
	ns = (char *)malloc(sizeof(char) * (len + 1));
	if (!ns)
		return (NULL);
	while (s[start] != '\0' && i < len)
		ns[i++] = s[start++];
	return (ns);
}
