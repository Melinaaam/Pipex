/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melinamotylewski <melinamotylewski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:45:59 by memotyle          #+#    #+#             */
/*   Updated: 2024/09/25 18:20:56 by melinamotyl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t n, size_t size)
{
	void	*ptr;
	size_t	longueur;

	longueur = n * size;
	if (n != 0 && longueur / n != size)
		return (NULL);
	ptr = malloc(longueur);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, longueur);
	return (ptr);
}
