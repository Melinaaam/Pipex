/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:07:59 by memotyle          #+#    #+#             */
/*   Updated: 2024/09/27 11:12:59 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static char	**libere_tab(char **tab, int i)
{
	while (i >= 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
	return (NULL);
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
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		else
			i++;
	}
	return (count_words);
}

static char	*find_words(const char *s, int start, int end)
{
	char	*word;
	int		i;

	word = malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (start < end)
	{
		word[i] = s[start];
		i++;
		start++;
	}
	word[i] = '\0';
	return (word);
}

static char	**rempli_tab(const char *s, char c, char **tab)
{
	int		place_word;
	int		start;
	int		i;

	start = 0;
	i = 0;
	place_word = 1;
	while (s[i])
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i] != c && s[i] != '\0')
				i++;
			tab[place_word] = find_words(s, start, i);
			if (!tab[place_word])
				return (libere_tab(tab, place_word - 1));
			place_word++;
		}
		else
			i++;
	}
	tab[place_word] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = malloc(sizeof (char *) * (count_words(s, c) + 2));
	if (!tab)
		return (NULL);
	tab[0] = malloc(sizeof(char));
	if (!tab[0])
		return (NULL);
	tab[0][0] = '\0';
	tab = rempli_tab(s, c, tab);
	if (!tab)
		return (NULL);
	return (tab);
}
