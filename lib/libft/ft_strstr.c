/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 12:03:05 by arudyi            #+#    #+#             */
/*   Updated: 2018/10/27 14:07:24 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	char	*str1;
	char	*str2;

	if (*needle == '\0')
		return ((char *)haystack);
	while (*haystack != '\0')
	{
		str1 = (char *)haystack;
		str2 = (char *)needle;
		while (*str1 == *str2 && *str2 != '\0')
		{
			str1++;
			str2++;
		}
		if (*str2 == '\0')
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}
