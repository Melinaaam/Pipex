/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:19:39 by memotyle          #+#    #+#             */
/*   Updated: 2024/10/22 18:06:26 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main()
{
	// if (ac > 1)
	// 	open_file(*av, 1);
	int id = fork();
	if (id != 0)
		fork();
	ft_printf("Pipex\n");
	//ft_printf("Pipex frome id : %d\n", id);
	// if (id == 0)
	// 	ft_printf("Pipex from the child process\n");
	// else
	// 	ft_printf("Pipex from the parent process\n");
	return (0);
}
