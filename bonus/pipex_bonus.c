/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melinamotylewski <melinamotylewski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:21:23 by memotyle          #+#    #+#             */
/*   Updated: 2024/11/07 13:56:46 by melinamotyl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

//ft pour executer cmd : utiliation de execve
	//remplace le processus actuel par un nouveau proramme
	//utilise par le p enfant apres l'appel a fork pourexeuter une commane
void	ex_cmd(char **env, char *av, char **path)
{
	char	*cmd_path;
	char	*temp;
	char	**cmd;

	cmd = ft_split(av, ' ');
	temp = ft_strjoin ("/", cmd[0]);
	if (!temp || !cmd || !*cmd)
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
	free(cmd_path);
	ft_free(cmd, temp);
	ft_free_paths(path);
}
//ft multi pipe
void	ft_pipes(char *cmd, char **env, char **path)
{
	pid_t	pid;
	int		fds[2];

	if (pipe(fds) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		close(fds[0]);
		dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);
		ex_cmd(env, cmd, path);
		// exit(EXIT_FAILURE);
	}
	else
	{
		close(fds[1]);
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
		waitpid(pid, NULL, 0);
	}
}


int	main(int ac, char **av, char **env)
{
	int	firsts_fd;
	int	last_fd;
	int	i;
	char	**path;

	if (ac < 5)
	{
		ft_putstr_fd("Error: not enough arguments\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	firsts_fd = open_file(av[1], 0);
	last_fd = open_file(av[ac - 1], 1);
	dup2(firsts_fd, STDIN_FILENO);
	close(firsts_fd);
	path = path_cmd(env);
	i = 2;
	while (i < ac - 2)
	{
		ft_pipes(av[i], env, path);
		i++;
	}
	dup2(last_fd, STDOUT_FILENO);
	close(last_fd);
	ex_cmd(env, av[ac - 2], path);
	return (0);
}
