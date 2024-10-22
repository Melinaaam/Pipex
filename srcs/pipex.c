/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:11:22 by memotyle          #+#    #+#             */
/*   Updated: 2024/10/22 16:06:32 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_file(char *av, int id)
{
	int	fd;

	if (id == 0)
		fd = open(av, O_RDONLY);
	if (id == 1)
		fd = open("file1", O_WRONLY | O_TRUNC | O_CREAT , 0644);
	return (fd);
}
