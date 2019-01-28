/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 18:57:01 by arudyi            #+#    #+#             */
/*   Updated: 2018/10/27 12:04:39 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char	*str;
	size_t	i;

	i = 0;
	str = NULL;
	if (size)
	{
		str = (char *)malloc(size);
		if (str == NULL)
			return (NULL);
		while (i < size)
		{
			str[i] = 0;
			i++;
		}
	}
	return ((void*)str);
}
