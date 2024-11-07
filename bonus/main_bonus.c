/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:19:24 by memotyle          #+#    #+#             */
/*   Updated: 2024/11/07 18:19:46 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int ac, char **av, char **env)
{
	int		fd_input;
	int		fd_output;
	int		i;

	if (ac < 5)
		ft_error(1);
	if (ft_strcmp(av[1], "here_doc") == 0)
	{
		if (ac < 6)
			ft_error(1);
		i = 3;
		fd_output = open_file(av[ac - 1], 2);
		ft_here_doc(av);
	}
	else
	{
		i = 2;
		fd_input = open_file(av[1], 0);
		fd_output = open_file(av[ac - 1], 1);
		dup2(fd_input, STDIN_FILENO);
	}
	while (i < ac - 2)
		ft_pipes(av[i++], env);
	dup2(fd_output, STDOUT_FILENO);
	ex_cmd(env, av[ac - 2]);
}
