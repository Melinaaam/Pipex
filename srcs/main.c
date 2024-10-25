/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:19:39 by memotyle          #+#    #+#             */
/*   Updated: 2024/10/25 16:28:47 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


int	open_file(char *av, int pid)
{
	int	fd;

	if (pid == 0)//child process
		fd = open(av, O_RDONLY, 0777);
	if (pid == 1)//parent process
		fd = open(av, O_WRONLY | O_TRUNC | O_CREAT , 0777);
	else
		fd = -1;
	return (fd);
}
void	child_p(char **av, int *fd, char **env)
{
	int		infile;
	char	**path;

	path = path_cmd(env);
	if (!path)
		exit(EXIT_FAILURE);//ajout gestion fuite memoire
	// int y = 0;
	// while (path[y])
	// {
	// 	ft_printf(YELLOW "path in child p : %s\n" RESET, path[y]);
	// 	y++;
	// }
	infile = open_file(av[1], 0);
	if (infile == -1)
	{
		close (fd[0]);
		close (fd[1]);
		//free_path;
		exit(EXIT_FAILURE);
	}
	dup2(infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);

	close (infile); //close fichier infile apres l'avoir lu
	close (fd[1]);//fermer ecriture tube
	//execute cmd : execute(path, env, av[2]);
	execve(*path, &av[2], env);
}

void	parent_p(char **av, int *fd, char **env)
{
	int 	outfile;
	char	**path;

	path = path_cmd(env);
	if (!path)
		exit(EXIT_FAILURE);


	outfile = open_file(av[1], 0);
	if (outfile == -1)
	{
		close (fd[0]);
		close (fd[1]);
		//free_path;
		exit(EXIT_FAILURE);
	}
	dup2(outfile, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);

	close (outfile);
	close(fd[1]);//ferme tube d'ecriture
	//execute cmd : execute(path, env, av[3]);
	execve(*path, &av[3], env);
}

int	main(int ac, char **av, char **env)
{
	int fd[2];
	int	pid1;
	int pid2;

	if (ac != 5)
		return (ft_printf(RED "Not enought arguments : need 5 !\n" RESET), 1);
	if (pipe(fd) == -1)
		return (1);
	pid1 = fork();
	if (pid1 == -1)
		return (1);
	if (pid1 == 0)
		child_p(&av[2], fd, env);
	pid2 = fork();
	if (pid2 == -1)
		return (1);
	if (pid2 == 0)
		//parent_p
	close (fd[0]);
	close (fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
