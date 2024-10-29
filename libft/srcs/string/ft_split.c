/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:07:59 by memotyle          #+#    #+#             */
/*   Updated: 2024/10/29 15:44:35 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static void	free_tab(char **tab, int i)
{
	while (i >= 0 && tab[i])
	{
		free(tab[i]);
		i--;
	}
	free(tab);
}

static int	count_words(const char *s, char c)
{
	int	count_words;
	int	i;

	count_words = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			count_words++;
			while (s[i] != '\0' && s[i] != c)
				i++;
		}
		if (s[i] == '\0')
			return (count_words);
		else
			i++;
	}
	return (count_words);
}

static char	**ft_tab(const char *s, char c, char **tab, int i)
{
	int		j;
	int		k;

	k = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			j = 0;
			while (s[i + j] && s[i + j] != c)
				j++;
			tab[k] = ft_substr(s, i, j);
			if (tab[k] == NULL)
			{
				free_tab(tab, k - 1);
				return (NULL);
			}
			k++;
			i += j;
		}
	}
	tab[k] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		len;

	if (!s)
		return (NULL);
	len = count_words(s, c);
	tab = (char **)malloc(sizeof (char *) * (len + 1));
	if (!tab)
		return (NULL);
	tab = ft_tab(s, c, tab, 0);
	if (!tab)
		return (NULL);
	return (tab);
}
