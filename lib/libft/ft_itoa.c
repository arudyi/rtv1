/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 19:25:09 by arudyi            #+#    #+#             */
/*   Updated: 2018/10/28 12:55:58 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_length(int n)
{
	int i;

	i = 1;
	while (n /= 10)
		i++;
	return (i);
}

char		*ft_itoa(int n)
{
	char			*str;
	int				len;
	unsigned int	i;

	i = n;
	len = ft_get_length(n);
	if (n < 0)
	{
		len = len + 1;
		i = i * -1;
	}
	str = (char *)malloc(sizeof(char) * len + 1);
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	while (--len > -1)
	{
		str[len] = (i % 10) + '0';
		i = i / 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
