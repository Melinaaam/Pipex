/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:11:22 by memotyle          #+#    #+#             */
/*   Updated: 2024/10/29 15:56:58 by memotyle         ###   ########.fr       */
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
		if (ft_strnstr(env[i], "PATH=", 5))
		{
			full_path = ft_strdup(env[i] + 5);
			//ft_printf(BLUE "full_path : %s\n\n" RESET, full_path);
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


//ft pour executer cmd : utiiation de execve
	//remplace le processus actuel par un nouveau proramme
	//utilise par le p enfant apres l'appel a fork pourexeuter une commane
void	ex_cmd(char **path, char **env, char *av)
{
	char	*cmd_path;
	char	*temp;
	char	**cmd;

	cmd = ft_split(av, ' ');
	temp = ft_strjoin("/",cmd[0]);
	if (!temp | !cmd | !*cmd)
		return (free_and_exit(path, cmd, temp));

	cmd_path = check_cmd(path, *cmd, temp);
	if (!cmd_path)
		return (free_and_exit(path, cmd, temp));
	if (cmd_path[0] == '\0')
	{
		free(cmd_path);
		cmd_path = ft_strdup(*cmd);
	}
	if (execve(cmd_path, cmd, env) == -1)
	{
		free(cmd_path);
		free_and_exit(path, cmd, temp);
	}
	return (free(cmd_path), free_path(path, cmd, temp));
}

char	*check_cmd(char **path, char *cmd, char *temp)
{
	char	*path_cmd;
	int		i;

	i = 0;
	if(!temp | !cmd | !*path | !path)
		return (NULL);
	while(path[i] && path)
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

void	free_and_exit(char **path, char **cmd, char *temp)
{
	if (*cmd && cmd)
		perror(*cmd);
	free_path(path, cmd, temp);
	exit(EXIT_FAILURE);
}

void	free_path(char **path, char **cmd, char *temp)
{
	int	i;

	i = 0;
	if(path)
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


void	error(int *fd, char *av, char **path)
{
	close(fd[0]);
	close(fd[1]);
	free_path(path, NULL, NULL);
	perror(av);
	exit(EXIT_FAILURE);
}
