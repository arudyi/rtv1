/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 19:58:30 by arudyi            #+#    #+#             */
/*   Updated: 2019/04/29 20:33:03 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

void	ft_get_object_plane(t_elem *s_pixel, t_vector direction, int i)
{
	double tmp;

	if ((tmp = ft_intersect_ray_plane(s_pixel->player.position, s_pixel,
	direction, i)) > 0)
	{
		if (tmp < s_pixel->obj.t && tmp >= 0)
		{
			s_pixel->obj.t = tmp;
			s_pixel->is_intersect = 1;
			s_pixel->obj.k = i;
		}
	}
}

void	ft_get_object_sphere(t_elem *s_pixel, t_vector direction, int i)
{
	double tmp;

	if ((tmp = ft_intersect_ray_sphere(s_pixel->player.position, s_pixel,
	direction, i)) > 0)
	{
		if (tmp < s_pixel->obj.t && tmp >= 0)
		{
			s_pixel->obj.t = tmp;
			s_pixel->is_intersect = 1;
			s_pixel->obj.k = i;
		}
	}
}

void	ft_get_object_cone(t_elem *s_pixel, t_vector direction, int i)
{
	double tmp;

	if ((tmp = ft_intersect_ray_cone(s_pixel->player.position, s_pixel,
	direction, i)) > 0)
	{
		if (tmp < s_pixel->obj.t && tmp >= 0)
		{
			s_pixel->obj.t = tmp;
			s_pixel->is_intersect = 1;
			s_pixel->obj.k = i;
		}
	}
}

void	ft_get_object_cylinder(t_elem *s_pixel, t_vector direction, int i)
{
	double tmp;

	if ((tmp = ft_intersect_ray_cylinder(s_pixel->player.position, s_pixel,
	direction, i)) > 0)
	{
		if (tmp < s_pixel->obj.t && tmp >= 0)
		{
			s_pixel->obj.t = tmp;
			s_pixel->is_intersect = 1;
			s_pixel->obj.k = i;
		}
	}
}

int		ft_get_object(t_elem *s_pixel, int x, int y)
{
	int			i;
	t_vector	direction;

	s_pixel->obj.t = DBL_MAX;
	i = -1;
	while (++i < s_pixel->nbr_of_obj)
	{
		direction = ft_canvas_to_viewport(x, y);
		direction = ft_rotate_camera(direction, s_pixel);
		if (s_pixel->arr_object3d[i].type_of_data == 2)
			ft_get_object_plane(s_pixel, direction, i);
		else if (s_pixel->arr_object3d[i].type_of_data == 0)
			ft_get_object_sphere(s_pixel, direction, i);
		else if (s_pixel->arr_object3d[i].type_of_data == 3)
			ft_get_object_cone(s_pixel, direction, i);
		else if (s_pixel->arr_object3d[i].type_of_data == 1)
			ft_get_object_cylinder(s_pixel, direction, i);
	}
	if (s_pixel->is_intersect == 1)
		return (s_pixel->obj.k);
	return (-1);
}
