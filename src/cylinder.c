/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 14:18:52 by arudyi            #+#    #+#             */
/*   Updated: 2019/05/01 13:18:05 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

double	ft_intersect_ray_cylinder3(t_elem *s_pixel, double m1, double m2, int i)
{
	if (T1_CYL >= 0 && T2_CYL >= 0)
	{
		if (T1_CYL <= T2_CYL)
			if (0 <= m1 && m1 <= HEIGHT_CYL)
				return (T1_CYL);
		if (0 <= m2 && m2 <= HEIGHT_CYL)
			return (T2_CYL);
	}
	else
	{
		if (T1_CYL >= 0 && T2_CYL < 0)
			if (0 <= m1 && m1 <= HEIGHT_CYL)
				return (T1_CYL);
		if (0 <= m2 && m2 <= HEIGHT_CYL)
			return (T2_CYL);
	}
	return (-1);
}

double	ft_intersect_ray_cylinder(t_vector position, t_elem *s_pixel,
t_vector direction, int i)
{
	double		discriminant;
	double		m1;
	double		m2;
	t_vector	v;
	t_vector	x;

	v = ft_normalize_vector(P2_CYL - P1_CYL);
	x = position - ((t_cylinder *)s_pixel->arr_object3d[i].data)->p1;
	A_CYL = DOT(direction, direction) - pow(DOT(direction, v), 2);
	B_CYL = 2.0 * (DOT(direction, x) - DOT(direction, v) * DOT(x, v));
	C_CYL = DOT(x, x) - pow(DOT(x, v), 2) - pow(RADIUS_CYL, 2);
	discriminant = pow(B_CYL, 2) - 4 * A_CYL * C_CYL;
	if (discriminant < 0)
		return (-1);
	T1_CYL = (-B_CYL + sqrt(discriminant)) / (2 * (double)A_CYL);
	T2_CYL = (-B_CYL - sqrt(discriminant)) / (2 * (double)A_CYL);
	m1 = ft_dot_product((position + direction * T1_CYL) - P1_CYL, v);
	m2 = ft_dot_product((position + direction * T2_CYL) - P1_CYL, v);
	return (ft_intersect_ray_cylinder3(s_pixel, m1, m2, i));
}
