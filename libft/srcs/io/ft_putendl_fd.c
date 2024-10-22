/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 08:20:22 by memotyle          #+#    #+#             */
/*   Updated: 2024/05/30 14:54:01 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		write (fd, &s[i], 1);
		i++;
	}
	write (fd, "\n", 1);
}
/*
#include <fcntl.h>

int	main()
{
	int	fd;

	fd = open("testputendl.txt", O_RDWR | O_TRUNC | O_CREAT, 0777);
	ft_putendl_fd("C'est la vie", fd);
	close (fd);
	return (0);
}
*/
