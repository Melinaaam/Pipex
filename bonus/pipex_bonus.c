/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:21:23 by memotyle          #+#    #+#             */
/*   Updated: 2024/10/30 14:45:44 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

//ft pour executer cmd : utiliation de execve
	//remplace le processus actuel par un nouveau proramme
	//utilise par le p enfant apres l'appel a fork pourexeuter une commane
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

void	childs_process()

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
