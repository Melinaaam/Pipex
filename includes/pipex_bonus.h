/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melinamotylewski <melinamotylewski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:21:03 by memotyle          #+#    #+#             */
/*   Updated: 2024/11/07 13:57:05 by melinamotyl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include "libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <stdlib.h>

# define RESET "\e[0m"
# define RED "\e[1;91m"

# define GREEN "\e[1;92m"
# define YELLOW "\e[1;93m"
# define BLUE "\e[1;94m"
# define MAGENTA "\e[1;95m"
# define CYAN "\e[1;96m"

//utils.c
int	open_file(char *av, int pid);
char	**path_cmd(char **env);
char	*check_cmd(char **path, char *cmd, char *temp);
void	ft_exit(char **path, char **cmd, char *temp);
void	ft_free(char **cmd, char *temp);
void	ft_free_paths(char **paths);


//pipex.c
void	ex_cmd(char **env, char *av, char **path);
void	ft_pipes(char *cmd, char **env, char **path);
void	forked(char **av, char **env, int **pipes, int cmd_count);
void	execute_command(char **av, char **env, int **pipes, int i, int cmd_count, char **path);
void	close_pipes(int **pipes, int pipe_count);
void	wait_process(int cmd_count);



#endif
