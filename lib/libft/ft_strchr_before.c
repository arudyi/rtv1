/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_before.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 12:50:41 by arudyi            #+#    #+#             */
/*   Updated: 2018/11/07 12:52:05 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr_before(char *str, char c)
{
	int		i;
	char	*tmp;

	if (str && c)
	{
		i = -1;
		while (str[++i] != '\0')
			if (str[i] == c)
				break ;
		if (str[i] != c)
			return (NULL);
		if (!(tmp = (char *)malloc(sizeof(char) * i + 1)))
			return (NULL);
		i = -1;
		while (str[++i] != c)
			tmp[i] = str[i];
		tmp[i] = '\0';
		return (tmp);
	}
	return (NULL);
}
