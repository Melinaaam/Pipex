/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:19:39 by memotyle          #+#    #+#             */
/*   Updated: 2024/10/29 15:56:07 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


int	open_file(char *av, int pid)
{
	int	fd;

	if (pid == 0)//child process
		fd = open(av, O_RDONLY);
	if (pid == 1)//parent process
		fd = open(av, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		perror("No such file or directory\n");
	return (fd);
}
void	parent_p(char **av, int *fd, char **env)
{
	int 	outfile;
	char	**path;

	path = NULL;
	path = path_cmd(env);
	if (!path)
		exit(127);
	outfile = open_file(av[4], 1);
	if (outfile == -1)
		error(fd, av[4], path);

	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);

	close (outfile);
	close(fd[1]);//ferme tube d'ecriture
	ex_cmd(path, env, av[3]);
}

void	child_p(char **av, int *fd, char **env)
{
	int		infile;
	char	**path;

	path = NULL;
	path = path_cmd(env);
	if (!path)
		exit(127);//ajout gestion fuite memoire
	infile = open_file(av[1], 0);
	if (infile == -1)
		error(fd, av[1], path);

	dup2(infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);

	close (infile); //close fichier infile apres l'avoir lu
	close (fd[0]);//fermer ecriture tube
	ex_cmd(path, env, av[2]);
}


int	main(int ac, char **av, char **env)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (ac == 5)
	{

		if (pipe(fd) == -1)
			exit(EXIT_FAILURE);
		pid1 = fork();
		if (pid1 == -1)
			exit(EXIT_FAILURE);
		if (pid1 == 0)
			child_p(av, fd, env);
		pid2 = fork();
		if (pid2 == -1)
			exit(EXIT_FAILURE);
		if (pid2 == 0)
			parent_p(av, fd, env);
		close (fd[0]);
		close (fd[1]);
		waitpid(pid1, NULL, 0);
		waitpid(pid2, NULL, 0);
		return (0);
	}
	exit(EXIT_FAILURE);
}
