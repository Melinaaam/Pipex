/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:11:22 by memotyle          #+#    #+#             */
/*   Updated: 2024/10/25 16:27:36 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//ft pour trouver le chemin de cmd passe en av
char	**path_cmd(char **env)
{
	int		i;
	char	*full_path = NULL;
	char	**split_path;

	//gestion de full path : pour trouver le full path, on cherche a partir de PATH=
	i = 0;
	while(env[i])
	{
		if (env[i][0] == 'P' && env[i][1] == 'A' && env[i][2] == 'T' && env[i][3] == 'H' & env[i][4] == '=')
		{
			full_path = ft_strdup(env[i] + 5);
			// ft_printf(BLUE "full_path : %s\n\n" RESET, full_path);
			if (!full_path)
				return (NULL);
			break;
		}
		i++;
	}

	//split path :
	if (ft_strlen(full_path) == 0 || full_path == NULL){
		split_path = ft_split(".", ':');
	}
	else{
		split_path = ft_split(full_path, ':');
		// i = 0;
		// ft_printf(MAGENTA "after split:\n" RESET);
		// while(split_path[i])
		// 	ft_printf(MAGENTA "split_path : %s\n" RESET, split_path[i++]);
		free(full_path);
	}
	// ft_printf(CYAN "IHERE\n" RESET);
	// i = 0;
	// while(split_path[i])
	// 	ft_printf(GREEN "split_path before return: %s\n" RESET, split_path[i++]);
	return (split_path);
}
// int id = fork();
	// if (id == 0)
	// {
	// 	close(fd[0]);
	// 	int x;
	// 	ft_printf("Input a number : ");
	// 	scanf("%d", &x);
	// 	if (write(fd[1], &x, sizeof(int)) == -1)
	// 		return(2);
	// 	close(fd[1]);
	// }
	// else
	// {
	// 	close(fd[1]);
	// 	int y;
	// 	if (read(fd[0], &y, sizeof(int)) == -1)
	// 		return 3;
	// 	y = y * 3;
	// 	close(fd[0]);
	// 	ft_printf("child : %d", y);
	// }



//ft pour executer cmd?
// void	ex_cmd(char *path, char **env, char **av)
// {

// }

void	free_path(char **path)
{
	int	i;

	i = 0;
	if(path)
	{
		free(path[i]);
		i++;
	}
	free(path);
	path = NULL;
}
