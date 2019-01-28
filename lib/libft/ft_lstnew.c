/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 17:24:22 by arudyi            #+#    #+#             */
/*   Updated: 2018/10/28 18:11:50 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *node;

	node = (t_list *)malloc(sizeof(*node));
	if (node == NULL)
		return (NULL);
	if (content)
	{
		if (!(node->content = malloc(content_size)))
			return (NULL);
		node->content = ft_memcpy(node->content, content, content_size);
		node->content_size = content_size;
		node->next = NULL;
		return (node);
	}
	node->content = NULL;
	node->content_size = 0;
	node->next = NULL;
	return (node);
}
