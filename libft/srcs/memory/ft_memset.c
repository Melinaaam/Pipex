/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melinamotylewski <melinamotylewski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:15:50 by memotyle          #+#    #+#             */
/*   Updated: 2024/09/25 17:49:10 by melinamotyl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *) s;
	while (n--)
	{
		*ptr = c;
		ptr++;
	}
	return (s);
}

/*
#include <string.h>
#include <stdio.h>
#include <limits.h>

int main()
{
    int intArray[5];
    char charArray[10];
    char    str[] = "Hello bonjour ?";

    printf("%s\n", str);
    ft_memset(str + 5, '!', 2);
    printf("%s\n", str);


    // memset
    memset(intArray, INT_MAX, sizeof(intArray));

    memset(charArray, 'A', sizeof(charArray));

    printf("MEMSET\n");
    printf("tableau de int :\n");
    for (int i = 0; i < 5; i++)
        printf("%d ", intArray[i]);
    printf("\n");

    printf("tableau de char :\n");
    for (int i = 0; i < 10; i++)
        printf("%c ", charArray[i]);
    printf("\n \n");

    // ft_memset
    ft_memset(intArray, INT_MAX, sizeof(intArray));

    ft_memset(charArray, 33, sizeof(charArray));

    printf("FT_MEMSET\n");
    printf("tableau de int :\n");
    for (int i = 0; i < 5; i++) {
        printf("%d ", intArray[i]);
    }
    printf("\n");

    printf("tableau de char :\n");
    for (int i = 0; i < 10; i++) {
        printf("%c ", charArray[i]);
    }
    printf("\n");
}*/
