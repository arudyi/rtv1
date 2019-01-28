/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 11:29:02 by arudyi            #+#    #+#             */
/*   Updated: 2018/10/29 11:52:40 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*node;
	t_list	*temp;

	node = (*alst);
	if (alst)
	{
		while (node)
		{
			temp = node->next;
			del(node->content, node->content_size);
			free(node);
			node = temp;
		}
		*alst = NULL;
	}
}
