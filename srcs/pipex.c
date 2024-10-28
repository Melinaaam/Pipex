/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:11:22 by memotyle          #+#    #+#             */
/*   Updated: 2024/10/28 13:54:42 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//ft pour trouver le chemin de cmd passe en av
char	**path_cmd(char **env)
{
	int		i;
	char	*full_path = NULL;
	char	**split_path;

	//gestion de full path : pour trouver le full path, on cherche a partir de PATH=
	i = 0;
	while(env[i])
	{
		if (env[i][0] == 'P' && env[i][1] == 'A' && env[i][2] == 'T' && env[i][3] == 'H' & env[i][4] == '=')
		{
			full_path = ft_strdup(env[i] + 5);
			ft_printf(BLUE "full_path : %s\n\n" RESET, full_path);
			if (!full_path)
				return (NULL);
			break;
		}
		i++;
	}

	//split path :
	if (ft_strlen(full_path) == 0 || full_path == NULL){
		split_path = ft_split(".", ':');
	}
	else{
		split_path = ft_split(full_path, ':');
		free(full_path);
	}
	return (split_path);
}


//ft pour executer cmd?
void	ex_cmd(char *path, char **env, char **av)
{
	printf(GREEN "ex cmd\n" RESET);

	char	*cmd_path;
	char	**cmd;

	cmd = ft_split(*av, ' ');
	cmd_path = check_cmd(&path, *cmd);
	if (!cmd_path)
	{
		free_path(&path);
		exit(EXIT_FAILURE);
	}
	if (cmd_path[0] == '\0')
	{
		free(cmd_path);
		cmd_path = ft_strdup(*cmd);
	}
	if (execve(cmd_path, cmd, env) == -1)
	{
		free_path(&path);
		exit(EXIT_FAILURE);
	}
	free(path);
	free(cmd);
	free(cmd_path);
}

char	*check_cmd(char **path, char *cmd)
{
	char	*path_cmd;
	int		i;

	i = 0;
	while(path[i])
	{
		path_cmd = malloc(ft_strlen(path[i] + ft_strlen(cmd) + 2));
		if (!path_cmd)
			return (NULL);
		ft_strlcpy(path_cmd, path[i], ft_strlen(path[i]));
		ft_strlcat(path_cmd, "/", sizeof(char));
		ft_strlcat(path_cmd, cmd, ft_strlen(cmd));
		if (access(path_cmd, F_OK | X_OK) == 0)
			return (path_cmd);
		free(path_cmd);
		i++;
	}
	return (NULL);
}

void	free_path(char **path)
{
	int	i;

	i = 0;
	if(path)
	{
		free(path[i]);
		i++;
	}
	free(path);
	path = NULL;
}
