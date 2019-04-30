/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 14:18:56 by arudyi            #+#    #+#             */
/*   Updated: 2019/04/30 17:09:24 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

/*int		ft_find_denom_cone(t_elem *s_pixel, int i)
{
	double denom;

	denom = ((t_cone *)s_pixel->arr_object3d[i].data)->b * ((t_cone *)s_pixel->
	arr_object3d[i].data)->b - 4 * ((t_cone *)s_pixel->arr_object3d[i].data)->a
	* ((t_cone *)s_pixel->arr_object3d[i].data)->c;
	if (denom < 0)
		return (-1);
	return (denom);
}

int		ft_find_cone2(t_elem *s_pixel, int i, double m1, double m2)
{
	double t1;
	double t2;

	t1 = ((t_cone *)s_pixel->arr_object3d[i].data)->t1;
	t2 = ((t_cone *)s_pixel->arr_object3d[i].data)->t2;
	if (t1 >= 0 && t2 >= 0)
	{
		if (t1 < t2)
			if (0 <= m1 && m1 <= ((t_cone *)s_pixel->arr_object3d[i].data)->
			height)
				return (t1);
		if (0 <= m2 && m2 <= ((t_cone *)s_pixel->arr_object3d[i].data)->height)
			return (t2);
	}
	else
	{
		if (t1 >= 0 && t2 < 0)
			if (0 <= m1 && m1 <= ((t_cone *)s_pixel->arr_object3d[i].data)->
			height)
				return (t1);
		if (0 <= m2 && m2 <= ((t_cone *)s_pixel->arr_object3d[i].data)->height)
			return (t2);
	}
	return (-1);
}

int		ft_find_cone1(t_elem *s_pixel, double denom, int i, t_vector direction)
{
	double m1;
	double m2;
	double t1;
	double t2;

	t1 = (-((t_cone *)s_pixel->arr_object3d[i].data)->b + sqrt(denom)) /
	(2 * ((t_cone *)s_pixel->arr_object3d[i].data)->a);
	t2 = (-((t_cone *)s_pixel->arr_object3d[i].data)->b - sqrt(denom)) /
	(2 * ((t_cone *)s_pixel->arr_object3d[i].data)->a);
	((t_cone *)s_pixel->arr_object3d[i].data)->t1 = t1;
	((t_cone *)s_pixel->arr_object3d[i].data)->t2 = t2;
	m1 = ft_dot_product((s_pixel->player.position + direction * t1) - ((t_cone
	*)s_pixel->arr_object3d[i].data)->p1, ((t_cone *)s_pixel->arr_object3d[i].
	data)->v);
	m2 = ft_dot_product((s_pixel->player.position + direction * t2) - ((t_cone
	*)s_pixel->arr_object3d[i].data)->p1, ((t_cone *)s_pixel->arr_object3d[i].
	data)->v);
	return (ft_find_cone2(s_pixel, i, m1, m2));
}*/

double	ft_intersect_ray_cone(t_vector position, t_elem *s_pixel, t_vector direction, int i)
{
	double m1;
	double m2;
	double t1;
	double t2;
	double a;
	double b;
	double c;
	double		k;
	double		denom;
	t_vector	x;
	t_vector	v;

	v = ft_normalize_vector(((t_cone *)s_pixel->arr_object3d[i].data)->p2 - ((t_cone *)s_pixel->arr_object3d[i].data)->p1);
	//((t_cone *)s_pixel->arr_object3d[i].data)->v = v;
	x = position - ((t_cone *)s_pixel->arr_object3d[i].data)->p1;
	k = tan(((t_cone *)s_pixel->arr_object3d[i].data)->angle / 2.0 / 180.0 * 3.14);
	a = DOT(direction, direction) - (1.0 + k * k) * pow(DOT(direction, v), 2);
	b = 2.0 * (DOT(direction, x) - (1.0 + k * k) * DOT(direction, v) * DOT(x, v));
	c = DOT(x, x) - (1.0 + k * k) * pow(DOT(x, v), 2);
	
	denom = b * b - 4 * a * c;
	if (denom < 0)
		return (-1);

	t1 = (-b + sqrt(denom)) / (2 * a);
	t2 = (-b - sqrt(denom)) / (2 * a);
	//((t_cone *)s_pixel->arr_object3d[i].data)->t1 = t1;
	//((t_cone *)s_pixel->arr_object3d[i].data)->t2 = t2;
	m1 = ft_dot_product((position + direction * t1) - ((t_cone *)s_pixel->arr_object3d[i].data)->p1, v);
	m2 = ft_dot_product((position + direction * t2) - ((t_cone *)s_pixel->arr_object3d[i].data)->p1, v);
	//return (ft_find_cone1(s_pixel, denom, i, direction));
	if (t1 >= 0 && t2 >= 0)
	{
		if (t1 < t2)
			if (0 <= m1 && m1 <= ((t_cone *)s_pixel->arr_object3d[i].data)->height)
				return (t1);
		if (0 <= m2 && m2 <= ((t_cone *)s_pixel->arr_object3d[i].data)->height)
			return (t2);
	}
	else
	{
		if (t1 >= 0 && t2 < 0)
			if (0 <= m1 && m1 <= ((t_cone *)s_pixel->arr_object3d[i].data)->height)
				return (t1);
		if (0 <= m2 && m2 <= ((t_cone *)s_pixel->arr_object3d[i].data)->height)
			return (t2);
	}
	return (-1);
}
