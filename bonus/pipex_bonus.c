/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:21:23 by memotyle          #+#    #+#             */
/*   Updated: 2024/11/06 19:49:22 by memotyle         ###   ########.fr       */
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
//ft multi pipe
void	ft_pipes(int cmd_count, int **pipes)
{
	int	i;

	i = 0;
	while(i < cmd_count -1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipe(pipes[i]))
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		i++;
	}

	i = 0;
	while (i < cmd_count - 1 )
	{
		if (pipe(pipes[i]))
			exit(EXIT_FAILURE);
	}
	i++;
}
//boucle de for
void	forked(char **av, char **env, int **pipes, int cmd_count, int ac)
{
	int	i;
	pid_t	pid;
	char	**path;

	path = NULL;
	path = path_cmd(env);
	if (!path)
		exit(127);

	i = 0;
	while (i < cmd_count)
	{
		pid = fork();
		if (pid == - 1)
			exit(EXIT_FAILURE);
		if (pid == 0)
			execute_command(av, env, pipes, i, cmd_count, ac);
		i++;
	}
}

void	execute_command(char **av, char **env, int **pipes, int i, int cmd_count, int ac)
{
	char	**path;
	int		infile;
	int		outfile;

	path = path_cmd(env);
	if (!path)
		exit(EXIT_FAILURE);

	// Configuration des redirections d'entrée
	if (i == 0)
	{
		// Première commande : lire depuis infile
		infile = open_file(av[1], 0);
		if (infile == -1)
			exit(EXIT_FAILURE);
		dup2(infile, STDIN_FILENO);
		close(infile);
	}
	else
	{
		// Autres commandes : lire depuis le pipe précédent
		dup2(pipes[i - 1][0], STDIN_FILENO);
	}

	// Configuration des redirections de sortie
	if (i == cmd_count - 1)
	{
		// Dernière commande : écrire dans outfile
		outfile = open_file(av[ac - 1], 1);
		if (outfile == -1)
			exit(EXIT_FAILURE);
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
	}
	else
	{
		// Autres commandes : écrire dans le pipe suivant
		dup2(pipes[i][1], STDOUT_FILENO);
	}

	// Fermeture des descripteurs de pipe inutilisés
	int j = 0;
	while (j < cmd_count - 1)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}

	// Appel de ex_cmd pour exécuter la commande
	ex_cmd(path, env, av[i + 2]);

	// Si execve échoue
	ft_free(path, NULL, NULL);
	exit(EXIT_FAILURE);
}

void	close_pipes(int cmd_count, int **pipes)
{
	int	i;

	i = 0;
	while(i < cmd_count - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void	wait_process(int cmd_count)
{
	int	i;

	i = 0;
	while(i < cmd_count)
	{
		wait(NULL);
		i++;
	}
}

int	main(int ac, char **av, char **env)
{
	int	cmd_count;
	int	**pipes;

	if (ac < 5)
		exit(EXIT_FAILURE);
	cmd_count = ac - 3;
	pipes = malloc(sizeof(int *) * (cmd_count - 1));
	if (!pipes)
		exit(EXIT_FAILURE);
	ft_pipes(cmd_count, pipes);
	forked(av, env, pipes, cmd_count, ac);
	close_pipes(cmd_count, pipes);
	wait_process(cmd_count);
	int	i;

	i = 0;
	while (i < cmd_count - 1)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
	return (0);
}
