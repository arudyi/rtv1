/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 14:18:30 by arudyi            #+#    #+#             */
/*   Updated: 2019/04/30 17:08:19 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

double	ft_intersect_ray_plane(t_vector position, t_elem *s_pixel,
t_vector direction, int i)
{
	t_vector	x;
	t_vector	normal;
	double		k1;
	double		k2;
	double		result;

	x = position - ((t_plane *)s_pixel->arr_object3d[i].data)->point;
	normal = ft_normalize_vector(((t_plane *)s_pixel->arr_object3d[i].data)->
	normal - ((t_plane *)s_pixel->arr_object3d[i].data)->point);
	k1 = DOT(-x, normal);
	k2 = DOT(direction, normal);
	if (k2 == 0)
		return (-1);
	result = k1 / k2;
	if ((DOT(direction, normal) * DOT(x, normal)) > 0)
		return (-1);
	return (result);
}
