/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:21:03 by memotyle          #+#    #+#             */
/*   Updated: 2024/10/29 19:05:39 by memotyle         ###   ########.fr       */
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

//pipex
void	ex_cmd(char *cmd, char **env);
void	second_child(char **av, int *fd, char **env);
void	pipes(char *cmd, char **env);

//utils
int	open_file(char *av, int pid);
char	**path_cmd(char **env);
char	*check_cmd(char **path, char *cmd, char *temp);
void	ft_exit(int exit_e);
void	ft_free(char **tab);
void	ft_error(int *fd, char *av, char **path);
#endif
