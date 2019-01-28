/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 18:04:24 by arudyi            #+#    #+#             */
/*   Updated: 2018/10/27 14:28:52 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s_s1;
	unsigned char	*s_s2;

	s_s1 = (unsigned char*)s1;
	s_s2 = (unsigned char*)s2;
	while (n > 0 && *s_s1 == *s_s2)
	{
		s_s1++;
		s_s2++;
		n--;
	}
	if (n == 0)
		return (0);
	return (*s_s1 - *s_s2);
}
