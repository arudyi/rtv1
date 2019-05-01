/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 14:18:56 by arudyi            #+#    #+#             */
/*   Updated: 2019/05/01 13:31:21 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

double	ft_intersect_ray_cone3(t_elem *s_pixel, double m1, double m2, int i)
{
	if (T1_CONE >= 0 && T2_CONE >= 0)
	{
		if (T1_CONE < T2_CONE)
			if (0 <= m1 && m1 <= HEIGHT_CONE)
				return (T1_CONE);
		if (0 <= m2 && m2 <= HEIGHT_CONE)
			return (T2_CONE);
	}
	else
	{
		if (T1_CONE >= 0 && T2_CONE < 0)
			if (0 <= m1 && m1 <= HEIGHT_CONE)
				return (T1_CONE);
		if (0 <= m2 && m2 <= HEIGHT_CONE)
			return (T2_CONE);
	}
	return (-1);
}

double	ft_intersect_ray_cone(t_vector position, t_elem *s_pixel,
t_vector direction, int i)
{
	double		m1;
	double		m2;
	double		denom;
	t_vector	x;
	t_vector	v;

	v = ft_normalize_vector(P2_CONE - P1_CONE);
	x = position - P1_CONE;
	K_CONE = tan(((t_cone *)s_pixel->arr_object3d[i].data)->angle / 2.0 /
	180.0 * 3.14);
	A_CONE = DOT(direction, direction) - (1.0 + K_CONE * K_CONE) *
	pow(DOT(direction, v), 2);
	B_CONE = 2.0 * (DOT(direction, x) - (1.0 + K_CONE * K_CONE) *
	DOT(direction, v) * DOT(x, v));
	C_CONE = DOT(x, x) - (1.0 + K_CONE * K_CONE) * pow(DOT(x, v), 2);
	denom = pow(B_CONE, 2) - 4 * A_CONE * C_CONE;
	if (denom < 0)
		return (-1);
	T1_CONE = (-B_CONE + sqrt(denom)) / (2 * (double)A_CONE);
	T2_CONE = (-B_CONE - sqrt(denom)) / (2 * (double)A_CONE);
	m1 = ft_dot_product((position + direction * T1_CONE) - P1_CONE, v);
	m2 = ft_dot_product((position + direction * T2_CONE) - P1_CONE, v);
	return (ft_intersect_ray_cone3(s_pixel, m1, m2, i));
}
