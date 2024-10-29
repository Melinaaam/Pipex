/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:11:22 by memotyle          #+#    #+#             */
/*   Updated: 2024/10/29 19:03:54 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_file(char *av, int pid)
{
	int	fd;

	if (pid == 0)
		fd = open(av, O_RDONLY);
	if (pid == 1)
		fd = open(av, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		perror("No such file or directory\n");
	return (fd);
}

//ft pour trouver le chemin de cmd passe en av
char	**path_cmd(char **env)
{
	int		i;
	char	*full_path;
	char	**split_path;

	i = 0;
	full_path = NULL;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
		{
			full_path = ft_strdup(env[i] + 5);
			if (!full_path)
				return (NULL);
			break ;
		}
		i++;
	}
	if (ft_strlen(full_path) == 0 || full_path == NULL)
		split_path = ft_split(".", ':');
	else
	{
		split_path = ft_split(full_path, ':');
		free(full_path);
	}
	return (split_path);
}

char	*check_cmd(char **path, char *cmd, char *temp)
{
	char	*path_cmd;
	int		i;

	i = 0;
	if (!temp | !cmd | !*path | !path)
		return (NULL);
	while (path[i] && path)
	{
		path_cmd = ft_strjoin(path[i], temp);
		if (!path_cmd)
			return (NULL);
		if (access(path_cmd, F_OK | X_OK) == 0)
			return (path_cmd);
		free(path_cmd);
		i++;
	}
	return (ft_strdup(""));
}

void	ft_exit(char **path, char **cmd, char *temp)
{
	if (*cmd && cmd)
		perror(*cmd);
	ft_free(path, cmd, temp);
	exit(EXIT_FAILURE);
}

void	ft_free(char **path, char **cmd, char *temp)
{
	int	i;

	i = 0;
	if (path)
	{
		while (path[i])
			free(path[i++]);
		free(path);
	}
	i = 0;
	if (cmd)
	{
		while (cmd[i])
			free(cmd[i++]);
		free(cmd);
	}
	if (temp)
		free(temp);
}

void	ft_error(int *fd, char *av, char **path)
{
	close(fd[0]);
	close(fd[1]);
	ft_free(path, NULL, NULL);
	perror(av);
	exit(EXIT_FAILURE);
}
