/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:19:39 by memotyle          #+#    #+#             */
/*   Updated: 2024/10/28 14:02:15 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


int	open_file(char *av, int pid)
{
	ft_printf(RED "open file\n" RESET);
	printf("Trying to open: %s\n", av);
	int	fd;

	ft_printf("pid : [%d]\n", pid);
	if (pid == 0)//child process
	{
		fd = open(av, O_RDONLY);
		ft_printf("pid2 : [%d]\n", pid);
	}
	if (pid == 1)//parent process
		fd = open(av, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		ft_printf("Erreur lors de l'ouverture du fichier %s : %s\n", av, strerror(errno));
		exit(1);
	}
	ft_printf("fd : [%d]\n", fd);
	return (fd);
}
void	child_p(char **av, int *fd, char **env)
{
	ft_printf("child process\n");
	int		infile;
	char	**path;

	path = path_cmd(env);
	if (!path)
		exit(EXIT_FAILURE);//ajout gestion fuite memoire
	infile = open_file(av[1], 0);
	ft_printf(RED "after open infile\n" RESET);
	if (infile == -1)
	{
		ft_printf(RED "echec  infile\n" RESET);
		close (fd[0]);
		close (fd[1]);
		free_path(path);
		exit(EXIT_FAILURE);
	}
	ft_printf(RED "here child\n" RESET);
	dup2(infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	ft_printf(RED "after dup\n" RESET);
	close (infile); //close fichier infile apres l'avoir lu
	close (fd[1]);//fermer ecriture tube
	//execute cmd : execute(path, env, av[2]);
	ex_cmd(*path, env, &av[2]);
}

void	parent_p(char **av, int *fd, char **env)
{
	ft_printf(GREEN "\nparent process\n" RESET);
	int 	outfile;
	char	**path;

	path = path_cmd(env);
	if (!path)
		exit(EXIT_FAILURE);


	outfile = open_file(av[4], 0);
	if (outfile == -1)
	{
		ft_printf(RED "aechec\n" RESET);
		close (fd[0]);
		close (fd[1]);
		free_path(path);
		exit(EXIT_FAILURE);
	}
	ft_printf(GREEN "after open outfile\n" RESET);
	dup2(outfile, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);

	close (outfile);
	close(fd[1]);//ferme tube d'ecriture
	ex_cmd(*path, env, &av[3]);
	//execve(*path, &av[3], env);
}

int	main(int ac, char **av, char **env)
{
	ft_printf("begin main\n");
	printf("file1: %s\n", av[1]);
	printf("cmd1: %s\n", av[2]);
	printf("cmd2: %s\n", av[3]);
	printf("outfile: %s\n", av[4]);

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
		child_p(av, fd, env);
	pid2 = fork();
	if (pid2 == -1)
		return (1);
	if (pid2 == 0)
		parent_p(av, fd, env);
	close (fd[0]);
	close (fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
