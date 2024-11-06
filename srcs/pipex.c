/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:19:39 by memotyle          #+#    #+#             */
/*   Updated: 2024/11/06 09:53:44 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//ft pour executer cmd : utiliation de execve
	//remplace le processus actuel par un nouveau proramme
	//utilise par le p enfant apres l'appel a fork pourexeuter une commande
void	ex_cmd(char **path, char **env, char *av)
{
	char	*cmd_path;
	char	*temp;
	char	**cmd;

	cmd = ft_split(av, ' ');
	temp = ft_strjoin ("/", cmd[0]);
	if (!temp | !cmd | !*cmd)
		return (ft_exit(path, cmd, temp));
	cmd_path = check_cmd(path, *cmd, temp);
	if (!cmd_path)
		return (ft_exit(path, cmd, temp));
	if (cmd_path[0] == '\0')
	{
		free(cmd_path);
		cmd_path = ft_strdup(*cmd);
	}
	if (execve(cmd_path, cmd, env) == -1)
	{
		free(cmd_path);
		ft_exit(path, cmd, temp);
	}
	return (free(cmd_path), ft_free(path, cmd, temp));
}

void	second_child(char **av, int *fd, char **env)
{
	int		outfile;
	char	**path;

	path = NULL;
	path = path_cmd(env);
	if (!path)
		exit(127);
	outfile = open_file(av[4], 1);
	if (outfile == -1)
		ft_error(fd, av[4], path);
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close (outfile);
	close (fd[1]);
	ex_cmd(path, env, av[3]);
}

void	first_child(char **av, int *fd, char **env)
{
	int		infile;
	char	**path;

	path = NULL;
	path = path_cmd(env);
	if (!path)
		exit(127);
	infile = open_file(av[1], 0);
	if (infile == -1)
		ft_error(fd, av[1], path);
	dup2(infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close (infile);
	close (fd[0]);
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
			first_child(av, fd, env);
		pid2 = fork();
		if (pid2 == -1)
			exit(EXIT_FAILURE);
		if (pid2 == 0)
			second_child(av, fd, env);
		close (fd[0]);
		close (fd[1]);
		waitpid(pid1, NULL, 0);
		waitpid(pid2, NULL, 0);
		return (0);
	}
	exit(EXIT_FAILURE);
}
