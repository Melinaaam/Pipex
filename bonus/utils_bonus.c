/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melinamotylewski <melinamotylewski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:21:30 by memotyle          #+#    #+#             */
/*   Updated: 2024/11/07 13:07:44 by melinamotyl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	open_file(char *av, int pross)
{
	int	fd;

	if (pross == 0)
		fd = open(av, O_RDONLY);
	if (pross == 1)
		fd = open(av, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (pross == 2)
		fd = open(av, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
	{
		perror(av);
		exit(EXIT_FAILURE);
	}
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
	if (!full_path || ft_strlen(full_path) == 0)
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
	if (!temp || !cmd || !path || !*path)
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
	ft_free_paths(path);
	ft_free(cmd, temp);
	exit(EXIT_FAILURE);
}

void	ft_free(char **cmd, char *temp)
{
	int	i;

	if (cmd)
	{
		i = 0;
		while (cmd[i])
		{
			free(cmd[i]);
			cmd[i] = NULL;
			i++;
		}
		free(cmd);
	}
	if (temp)
	{
		free(temp);
		temp = NULL;
	}
}


void	ft_free_paths(char **paths)
{
	int	i;

	if (paths)
	{
		i = 0;
		while (paths[i])
		{
			free(paths[i]);
			paths[i] = NULL;
			i++;
		}
		free(paths);
		paths = NULL;
	}
}
