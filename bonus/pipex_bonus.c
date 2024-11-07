/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:21:23 by memotyle          #+#    #+#             */
/*   Updated: 2024/11/07 17:27:15 by memotyle         ###   ########.fr       */
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

void	pipe_heredoc(char **av, int *pipe_fd)
{
	char	*read_p;

	close(pipe_fd[0]);
	while (1)
	{
		read_p = get_next_line(0);
		if (ft_strncmp(read_p, av[2], ft_strlen(av[2])) == 0 && read_p[ft_strlen(av[2])] == '\n')
		{
			free(read_p);
			exit (EXIT_FAILURE);
		}
		ft_putstr_fd(read_p, pipe_fd[1]);
		free(read_p);
	}
}
void	ft_here_doc(char **av)
{
	pid_t	pid;
	int		fds[2];

	if (pipe(fds) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (!pid)
		pipe_heredoc(av, fds);
	else
	{
		close (fds[1]);
		dup2(fds[0], 0);
		wait (NULL);
	}
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
	int	fd_input;
	int	fd_output;
	int	i;
	char	**path;

	if (ac < 5)
	{
		ft_putstr_fd("Error: not enough arguments\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (ft_strcmp(av[1], "here_doc") == 0)
	{
		if (ac < 6)
			exit(EXIT_FAILURE);
		i = 3;
		fd_output = open_file(av[ac - 1], 2);
		ft_here_doc(av);
	}
	else
	{
		i = 2;
		fd_input = open_file(av[1], 0);
		fd_output = open_file(av[ac - 1], 1);
		dup2(fd_input, STDIN_FILENO);
	}
	path = path_cmd(env);
	while (i < ac - 2)
		ft_pipes(av[i++], env, path);

	dup2(fd_output, STDOUT_FILENO);
	close(fd_output);
	if (fd_input != -1)
		close (fd_input);
	ex_cmd(env, av[ac - 2], path);
	return (0);
}
