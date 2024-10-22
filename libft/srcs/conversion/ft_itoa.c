/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melinamotylewski <melinamotylewski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:27:53 by memotyle          #+#    #+#             */
/*   Updated: 2024/09/25 17:41:03 by melinamotyl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_number(int n)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*rempli_chaine(char *str, int n, int sign, int j)
{
	int	i;

	i = j - 1;
	if (sign == 1)
		str[0] = '-';
	while (n > 0)
	{
		str[i] = n % 10 + '0';
		n = n / 10;
		i--;
	}
	str[j] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	int		j;
	char	*str;
	int		sign;

	j = 0;
	sign = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	j = count_number(n);
	if (n < 0)
	{
		n = n * -1;
		j = 1 + count_number(n);
		sign = 1;
	}
	else
		j = count_number(n);
	str = malloc(sizeof(char) * (j + 1));
	if (!str)
		return (NULL);
	rempli_chaine(str, n, sign, j);
	return (str);
}
