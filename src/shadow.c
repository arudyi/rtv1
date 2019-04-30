/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 14:24:55 by arudyi            #+#    #+#             */
/*   Updated: 2019/04/30 15:27:38 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

t_vector	ft_get_ray_light(t_elem *s_pixel, int i, t_vector position)
{
	t_vector ray_light;

	if (TY_LI == 1)
		ray_light = P_L - position;
	if (TY_LI == 2)
		ray_light = P_L;
	return (ray_light);
}

double		ft_get_t_max(t_elem *s_pixel, int i)
{
	double t_max;

	if (TY_LI == 1)
		t_max = 1;
	if (TY_LI == 2)
		t_max = DBL_MAX;
	return (t_max);
}

int			ft_is_shadow2(t_elem *s_pixel, int k, t_vector pos, t_vector r_l)
{
	double tmp;

	if (TYPE_OBJ == 2)
	{
		tmp = ft_intersect_ray_plane(pos, s_pixel, r_l, k);
		if (tmp < T_MAX && tmp >= 0.00001)
			return (1);
	}
	else if (TYPE_OBJ == 3)
	{
		tmp = ft_intersect_ray_cone(pos, s_pixel, r_l, k);
		if (tmp < T_MAX && tmp >= 0.00001)
			return (1);
	}
	return (0);
}

int			ft_is_shadow1(t_elem *s_pixel, int k, t_vector pos, t_vector r_l)
{
	double tmp;

	if (TYPE_OBJ == 0)
	{
		tmp = ft_intersect_ray_sphere(pos, s_pixel, r_l, k);
		if (tmp < T_MAX && tmp >= 0.00001)
			return (1);
	}
	else if (TYPE_OBJ == 1)
	{
		tmp = ft_intersect_ray_cylinder(pos, s_pixel, r_l, k);
		if (tmp < T_MAX && tmp >= 0.00001)
			return (1);
	}
	else
	{
		if (ft_is_shadow2(s_pixel, k, pos, r_l) == 1)
			return (1);
	}
	return (0);
}

int			ft_is_shadow(t_elem *s_pixel, double t, t_vector direction, int i)
{
	int			k;
	t_vector	ray_light;
	t_vector	position;

	position = s_pixel->player.position + direction * t;
	ray_light = ft_get_ray_light(s_pixel, i, position);
	s_pixel->obj.t_max = ft_get_t_max(s_pixel, i);
	k = -1;
	while (++k < s_pixel->nbr_of_obj)
	{
		if (ft_is_shadow1(s_pixel, k, position, ray_light) == 1)
			return (1);
	}
	return (0);
}
