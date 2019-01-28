/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 13:44:05 by arudyi            #+#    #+#             */
/*   Updated: 2018/10/25 12:29:14 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*str1;
	char	*str2;
	size_t	i;

	if (n == 0)
		return (dst);
	str1 = (char *)dst;
	str2 = (char *)src;
	i = 0;
	while (i < n)
	{
		*(str1 + i) = *(str2 + i);
		i++;
	}
	return (dst);
}
