/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melina <melina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:27:57 by memotyle          #+#    #+#             */
/*   Updated: 2024/10/12 23:32:59 by melina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*copy;
	int		len_s;
	int		i;

	len_s = ft_strlen((char *)s);
	copy = malloc((len_s + 1) * sizeof(char));
	i = 0;
	if (!copy)
		return (NULL);
	while (s[i])
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

/*
#include <stdio.h>
int	main()
{
	char	s[] = "Hello World 000";
	char	*cpy;

	printf("Avec vraie fonction : \n");
	printf("La chaine src est : %s\n", s);
	cpy = strdup(s);
	printf("La chaine dupliquee est : %s\n", cpy);
	free(cpy);

	printf("Avec ma fonction : \n");
	printf("La chaine src est : %s\n", s);
	cpy = ft_strdup(s);
	printf("La chaine dupliquee est : %s\n", cpy);
	free(cpy);

	return(0);
}
*/
