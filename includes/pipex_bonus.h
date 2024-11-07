/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:21:03 by memotyle          #+#    #+#             */
/*   Updated: 2024/11/07 18:25:47 by memotyle         ###   ########.fr       */
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

//utils_bonus.c
char	**path_cmd(char **env);
char	*check_cmd(char **path, char *cmd, char *temp);
void	ft_exit(char **path, char **cmd, char *temp);
void	ft_error(int f_error);
void	ft_free(char **cmd, char *temp, char **paths);
//pipex_bonus.c
int		open_file(char *av, int pross);
void	ex_cmd(char **env, char *av);
void	pipe_heredoc(char **av, int *pipe_fd);
void	ft_here_doc(char **av);
void	ft_pipes(char *cmd, char **env);

#endif
