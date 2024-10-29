/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:21:23 by memotyle          #+#    #+#             */
/*   Updated: 2024/10/29 19:05:46 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

//ft pour executer cmd : utiliation de execve
	//remplace le processus actuel par un nouveau proramme
	//utilise par le p enfant apres l'appel a fork pourexeuter une commane
void	ex_cmd(char *cmd, char **env)
{
	char	**split_cmd;
	char	*path;

	split_cmd = ft_split(cmd, ' ');
	path = path_cmd(env);
	if (execve(path, split_cmd, env) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(split_cmd[0], 2);
		ft_free(split_cmd);
		exit (0);
	}
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
	ex_cmd(av[3],av[3]);
}

void	pipes(char *cmd, char **env)
{
	pid_t	pid;
	int		p_fd[2];
	char	**path;

	path = NULL;
	path = path_cmd(env);

	if (pipe(p_fd) == -1)
		exit (0);
	pid = fork();
	if (pid == -1);
		exit (0);
	if (!pid)
	{
		close(p_fd[0]);
		dup2(p_fd[1], 1);
		ex_cmd(cmd, env);
	}
	else
	{
		close (p_fd[1]);
		dup2(p_fd[0], 0);
	}
}

int	main(int ac, char **av, char **env)
{
	int	i;
	int	fd_in;
	int	fd_out;
	char	**path;

	path = NULL;
	path = path_cmd(env);
	if (ac == 5)
	{
		i = 2;
		fd_in = open_file(av[1], 0);
		fd_out = open_file(av[ac - 1], 1);
		dup2(fd_in, 0);
		while (i < ac - 2)
			pipes(av[i++], env);
		dup2(fd_out, 1);
		ex_cmd(av[ac - 2], env);
		return (0);
	}
	exit(EXIT_FAILURE);
}
