/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 08:37:28 by memotyle          #+#    #+#             */
/*   Updated: 2024/05/30 14:53:36 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write (fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write (fd, "-", 1);
		n = n * -1;
	}
	if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	if (n <= 9 && n >= 0)
		ft_putchar_fd(n + '0', fd);
}
/*
#include <fcntl.h>

int	main()
{
	int	fd;

	fd = open("testputnbr.txt", O_TRUNC | O_RDWR | O_CREAT, 0777);
	ft_putnbr_fd(1474836, fd);
	close (fd);
	return(0);
}*/
