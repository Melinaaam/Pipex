/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:21:23 by memotyle          #+#    #+#             */
/*   Updated: 2024/11/07 20:18:41 by memotyle         ###   ########.fr       */
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

void	ex_cmd(char **env, char *av)
{
	char	*cmd_path;
	char	*temp;
	char	**cmd;
	char	**path;

	path = path_cmd(env);
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
	ft_free(cmd, temp, path);
}

void	pipe_heredoc(char **av, int *pipe_fd)
{
	char	*read_p;

	close(pipe_fd[0]);
	while (1)
	{
		read_p = get_next_line(0);
		if (ft_strncmp(read_p, av[2], ft_strlen(av[2])) == 0
			&& read_p[ft_strlen(av[2])] == '\n')
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

void	ft_pipes(char *cmd, char **env)
{
	pid_t	pid;
	int		fds[2];
	char	**path;

	path = path_cmd(env);
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
		ex_cmd(env, cmd);
	}
	else
	{
		close(fds[1]);
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
		waitpid(pid, NULL, 0);
	}
}
