/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 13:43:35 by arudyi            #+#    #+#             */
/*   Updated: 2018/10/27 13:57:37 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t len1;

	if (*needle == '\0')
		return ((char *)haystack);
	len1 = ft_strlen(needle);
	while (*haystack != '\0' && len >= len1)
	{
		if (*haystack == *needle && ft_memcmp(haystack, needle, len1) == 0)
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (NULL);
}
