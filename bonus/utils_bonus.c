/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:21:30 by memotyle          #+#    #+#             */
/*   Updated: 2024/11/07 18:20:16 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
	ft_free(cmd, temp, path);
	exit(EXIT_FAILURE);
}

void	ft_error(int f_error)
{
	if (f_error == 1)
		ft_putstr_fd("Error: not enough arguments\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	ft_free(char **cmd, char *temp, char **paths)
{
	int	i;

	if (cmd || paths)
	{
		i = 0;
		while (cmd[i])
		{
			free(cmd[i]);
			cmd[i] = NULL;
			i++;
		}
		i = 0;
		while (paths[i])
		{
			free(paths[i]);
			paths[i] = NULL;
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
