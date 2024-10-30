/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:21:03 by memotyle          #+#    #+#             */
/*   Updated: 2024/10/30 12:32:27 by memotyle         ###   ########.fr       */
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
char	**path_cmd(char **env);
char	*check_cmd(char **path, char *cmd, char *temp);
void	ft_exit(char **path, char **cmd, char *tmp);
void	ft_free(char **path, char **cmd, char *temp);
void	ft_error(int *fd, char *av, char **path);
int		open_file(char *av, int id);

//pipex.c
void	ex_cmd(char **path, char **env, char *av);
void	first_child(char **av, int *fd, char **env);
void	second_child(char **av, int *fd, char **env);
#endif
