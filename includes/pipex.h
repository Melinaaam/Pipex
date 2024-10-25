/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:20:26 by memotyle          #+#    #+#             */
/*   Updated: 2024/10/25 17:27:42 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include "libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>

# define RESET "\e[0m"
# define RED "\e[1;91m"

# define GREEN "\e[1;92m"
# define YELLOW "\e[1;93m"
# define BLUE "\e[1;94m"
# define MAGENTA "\e[1;95m"
# define CYAN "\e[1;96m"

int		open_file(char *av, int id);
void	child_p(char **av, int *fd, char **env);
void	parent_p(char **av, int *fd, char **env);

//pipex
char	**path_cmd(char **env);
void	free_path(char **path);
char	*check_cmd(char **path, char *cmd);
void	ex_cmd(char *path, char **env, char **av);
#endif
