/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 18:36:49 by arudyi            #+#    #+#             */
/*   Updated: 2018/12/29 12:36:50 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strchr_before(char *str, char c)
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

static	int	read_line(int fd, char **dep, char **line)
{
	char	*tmp;

	if (ft_strchr(dep[fd], '\n'))
	{
		*line = ft_strchr_before(dep[fd], '\n');
		tmp = ft_strchr(dep[fd], '\n');
		tmp = ft_strdup(tmp + 1);
		free(dep[fd]);
		dep[fd] = tmp;
		if (dep[fd][0] == '\0')
			ft_strdel(&(dep[fd]));
	}
	else if (!(ft_strchr(dep[fd], '\n')))
	{
		*line = ft_strdup(dep[fd]);
		ft_strdel(&(dep[fd]));
	}
	return (1);
}

int			get_next_line(int fd, char **line)
{
	char		*tmp;
	static char	*dep[OPEN_MAX];
	int			count;
	char		buf[BUFF_SIZE + 1];

	if (fd < 0 || line == NULL)
		return (-1);
	*line = NULL;
	while ((count = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[count] = '\0';
		if (dep[fd] == NULL)
			dep[fd] = ft_strnew(1);
		tmp = ft_strjoin(dep[fd], buf);
		free(dep[fd]);
		dep[fd] = tmp;
		if (ft_strchr(tmp, '\n'))
			break ;
	}
	if (count < 0)
		return (-1);
	if ((count == 0) && (dep[fd] == NULL))
		return (0);
	return (read_line(fd, dep, line));
}
