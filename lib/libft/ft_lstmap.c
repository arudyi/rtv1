/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 12:18:29 by arudyi            #+#    #+#             */
/*   Updated: 2018/10/29 13:17:36 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*start;
	t_list	*temp;

	new = NULL;
	temp = NULL;
	start = NULL;
	temp = f(lst);
	if (!(new = ft_lstnew(temp->content, temp->content_size)) || lst == NULL)
		return (NULL);
	start = new;
	lst = lst->next;
	while (lst)
	{
		temp = f(lst);
		if (!(new->next = ft_lstnew(temp->content, temp->content_size)))
			return (NULL);
		lst = lst->next;
		new = new->next;
	}
	return (start);
}
