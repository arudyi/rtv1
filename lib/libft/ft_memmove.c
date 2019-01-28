/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 17:49:15 by arudyi            #+#    #+#             */
/*   Updated: 2018/10/26 15:55:32 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	i = 0;
	str1 = (unsigned char *)dst;
	str2 = (unsigned char *)src;
	if (str1 > str2)
	{
		while ((int)(len--) > 0)
			*(str1 + len) = *(str2 + len);
	}
	else
		while (i < len)
		{
			*(str1 + i) = *(str2 + i);
			i++;
		}
	return (dst);
}
