/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 14:18:18 by arudyi            #+#    #+#             */
/*   Updated: 2019/04/30 17:07:30 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

double		ft_find_sphere(t_elem *s_pixel, int i, double denom)
{
	double t1;
	double t2;

	t1 = (-((t_sphere *)s_pixel->arr_object3d[i].data)->b + sqrt(denom)) /
	(2 * ((t_sphere *)s_pixel->arr_object3d[i].data)->a);
	t2 = (-((t_sphere *)s_pixel->arr_object3d[i].data)->b - sqrt(denom)) /
	(2 * ((t_sphere *)s_pixel->arr_object3d[i].data)->a);
	if (t1 >= 0 && t2 >= 0)
	{
		if (t1 < t2)
			return (t1);
		return (t2);
	}
	else
	{
		if (t1 >= 0 && t2 < 0)
			return (t1);
		if (t1 < 0 && t2 >= 0)
			return (t2);
	}
	return (-1);
}

double		ft_intersect_ray_sphere(t_vector position, t_elem *s_pixel,
t_vector direction, int i)
{
	double		a;
	double		b;
	double		c;
	double		denom;
	t_vector	oc;

	oc = position - ((t_sphere *)s_pixel->arr_object3d[i].data)->center;
	a = DOT(direction, direction);
	b = 2 * DOT(oc, direction);
	c = DOT(oc, oc) - pow(((t_sphere *)s_pixel->
	arr_object3d[i].data)->radius, 2);
	((t_sphere *)s_pixel->arr_object3d[i].data)->b = b;
	((t_sphere *)s_pixel->arr_object3d[i].data)->a = a;
	denom = b * b - 4 * a * c;
	if (denom < 0)
		return (-1);
	return (ft_find_sphere(s_pixel, i, denom));
}
