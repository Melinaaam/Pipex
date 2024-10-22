/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melinamotylewski <melinamotylewski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:12:59 by memotyle          #+#    #+#             */
/*   Updated: 2024/09/25 17:46:24 by melinamotyl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *) s;
	while (n--)
	{
		*ptr = 0;
		ptr++;
	}
}
// #include <stdio.h>
// #include <strings.h>

// int	main(void)
// {
// 	char	s[14] = "Hello ?";
// 	int	tab[4] = {0, 1, 2, 3};

// 	printf("Test ave une chaine de caractere :\n");
// 	printf("Chaine : %s\n", s);
// 	bzero(s + 4, 4);
//         printf("Resultat attendu : %s\n", s);
// 	ft_bzero(s + 4, 4);
// 	printf("Resultat : %s\n", s);

// 	printf("\nTest ave une chaine de caractere :\n");
//         for (int i = 0; i < 4; i++)
// 		printf("Tableau de int : %d\n", tab[i]);
//         bzero(tab + 2, 1);
// 	for (int i = 0; i < 4; i++)
// 		printf("Resultat attendu : %d\n", tab[i]);
//         ft_bzero(tab + 2, 1);
// 	for (int i = 0; i < 4; i++)
// 		printf("Resultat : %d\n", tab[i]);
// 	return (0);
// }
