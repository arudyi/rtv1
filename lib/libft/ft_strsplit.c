/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 19:10:15 by arudyi            #+#    #+#             */
/*   Updated: 2018/10/28 16:56:00 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(const char *str, char c)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == c && str[i + 1] != c)
			len++;
		i++;
	}
	if (str[0] != '\0')
		len++;
	return (len);
}

static char	*ft_word(const char *s, char c, int *i)
{
	char	*str;
	int		j;

	if (!(str = (char *)malloc(sizeof(str) * (ft_strlen(s)))))
		return (NULL);
	j = 0;
	while (s[*i] != c && s[*i])
	{
		str[j] = s[*i];
		j++;
		*i += 1;
	}
	str[j] = '\0';
	while (s[*i] == c && s[*i])
		*i += 1;
	return (str);
}

char		**ft_strsplit(const char *s, char c)
{
	int		i;
	int		j;
	int		len;
	char	**str;

	if (s)
	{
		i = 0;
		j = 0;
		len = ft_count_words(s, c);
		if (!(str = (char **)malloc(sizeof(s) * (len + 1))))
			return (NULL);
		while (s[i] == c && s[i])
			i++;
		while (j < len && s[i])
		{
			str[j] = ft_word(s, c, &i);
			j++;
		}
		str[j] = NULL;
		return (str);
	}
	return (NULL);
}
