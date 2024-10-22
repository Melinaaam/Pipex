/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melinamotylewski <melinamotylewski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:38:47 by memotyle          #+#    #+#             */
/*   Updated: 2024/09/25 18:25:51 by melinamotyl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;
	t_list	*temp2;

	if (!lst)
		return ;
	temp = *lst;
	while (temp)
	{
		temp2 = temp->next;
		if (del)
			del(temp->content);
		free(temp);
		temp = temp2;
	}
	*lst = NULL;
}
