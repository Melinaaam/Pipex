/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:20:26 by memotyle          #+#    #+#             */
/*   Updated: 2024/10/29 14:25:35 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PIPEX_H
# define PIPEX_H

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

int		open_file(char *av, int id);
void	child_p(char **av, int *fd, char **env);
void	parent_p(char **av, int *fd, char **env);

//pipex
char	**path_cmd(char **env);
void	ex_cmd(char **path, char **env, char *av);
char	*check_cmd(char **path, char *cmd, char *temp);
void	free_and_exit(char **path, char **cmd, char *tmp);
void	free_path(char **path, char **cmd, char *tmp);
void	error(int *fd, char *av, char **path);

//utils
size_t	ftt_strlen(const char *s);
char	*ftt_strnstr(const char *big, const char *little, size_t len);
char	*ftt_strdup(const char *s);
char	*ftt_substr(char const *s, unsigned int start, size_t len);
char	*ftt_strjoin(char const *s1, char const *s2);
char	**ftt_split(char const *s, char c);
#endif

