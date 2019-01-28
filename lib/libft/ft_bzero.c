/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 13:07:57 by arudyi            #+#    #+#             */
/*   Updated: 2018/10/25 11:50:09 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_bzero(void *s, size_t n)
{
	unsigned char	*str;
	size_t			i;

	if (!n)
		return ;
	i = 0;
	str = (unsigned char*)s;
	while (i < n)
		*(str + i++) = '\0';
}
