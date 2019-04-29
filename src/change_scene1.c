/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_scene1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 17:43:48 by arudyi            #+#    #+#             */
/*   Updated: 2019/04/29 17:44:24 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

void	ft_change_object_up_down1(t_elem *s_pixel, int i, double angle_x)
{
	double y;
	double z;

	y = ((t_plane *)s_pixel->arr_object3d[i].data)->normal.y * cos(angle_x)
	+ ((t_plane *)s_pixel->arr_object3d[i].data)->normal.z * sin(angle_x);
	z = -((t_plane *)s_pixel->arr_object3d[i].data)->normal.y * sin(angle_x)
	+ ((t_plane *)s_pixel->arr_object3d[i].data)->normal.z * cos(angle_x);
	((t_plane *)s_pixel->arr_object3d[i].data)->normal.y = y;
	((t_plane *)s_pixel->arr_object3d[i].data)->normal.z = z;
}

void	ft_change_object_up_down(t_elem *s_pixel, int i, double angle_x)
{
	double y;
	double z;

	if (s_pixel->arr_object3d[i].type_of_data == 1)
	{
		y = ((t_cylinder *)s_pixel->arr_object3d[i].data)->p2.y * cos(angle_x) +
		((t_cylinder *)s_pixel->arr_object3d[i].data)->p2.z * sin(angle_x);
		z = -((t_cylinder *)s_pixel->arr_object3d[i].data)->p2.y * sin(angle_x)
		+ ((t_cylinder *)s_pixel->arr_object3d[i].data)->p2.z * cos(angle_x);
		((t_cylinder *)s_pixel->arr_object3d[i].data)->p2.y = y;
		((t_cylinder *)s_pixel->arr_object3d[i].data)->p2.z = z;
	}
	else if (s_pixel->arr_object3d[i].type_of_data == 3)
	{
		y = ((t_cone *)s_pixel->arr_object3d[i].data)->p2.y * cos(angle_x) +
		((t_cone *)s_pixel->arr_object3d[i].data)->p2.z * sin(angle_x);
		z = -((t_cone *)s_pixel->arr_object3d[i].data)->p2.y * sin(angle_x) +
		((t_cone *)s_pixel->arr_object3d[i].data)->p2.z * cos(angle_x);
		((t_cone *)s_pixel->arr_object3d[i].data)->p2.y = y;
		((t_cone *)s_pixel->arr_object3d[i].data)->p2.z = z;
	}
	else if (s_pixel->arr_object3d[i].type_of_data == 2)
		ft_change_object_up_down1(s_pixel, i, angle_x);
}

void	ft_change_object_left_right1(t_elem *s_pixel, int i, double angle_z)
{
	double x;
	double y;

	x = ((t_plane *)s_pixel->arr_object3d[i].data)->normal.x * cos(angle_z) +
	((t_plane *)s_pixel->arr_object3d[i].data)->normal.y * sin(angle_z);
	y = -((t_plane *)s_pixel->arr_object3d[i].data)->normal.x * sin(angle_z)
	+ ((t_plane *)s_pixel->arr_object3d[i].data)->normal.y * cos(angle_z);
	((t_plane *)s_pixel->arr_object3d[i].data)->normal.x = x;
	((t_plane *)s_pixel->arr_object3d[i].data)->normal.y = y;
}

void	ft_change_object_left_right(t_elem *s_pixel, int i, double angle_z)
{
	double x;
	double y;

	if (s_pixel->arr_object3d[i].type_of_data == 1)
	{
		x = ((t_cylinder *)s_pixel->arr_object3d[i].data)->p2.x * cos(angle_z) +
		((t_cylinder *)s_pixel->arr_object3d[i].data)->p2.y * sin(angle_z);
		y = -((t_cylinder *)s_pixel->arr_object3d[i].data)->p2.x * sin(angle_z)
		+ ((t_cylinder *)s_pixel->arr_object3d[i].data)->p2.y * cos(angle_z);
		((t_cylinder *)s_pixel->arr_object3d[i].data)->p2.x = x;
		((t_cylinder *)s_pixel->arr_object3d[i].data)->p2.y = y;
	}
	else if (s_pixel->arr_object3d[i].type_of_data == 3)
	{
		x = ((t_cone *)s_pixel->arr_object3d[i].data)->p2.x * cos(angle_z) +
		((t_cone *)s_pixel->arr_object3d[i].data)->p2.y * sin(angle_z);
		y = -((t_cone *)s_pixel->arr_object3d[i].data)->p2.x * sin(angle_z)
		+ ((t_cone *)s_pixel->arr_object3d[i].data)->p2.y * cos(angle_z);
		((t_cone *)s_pixel->arr_object3d[i].data)->p2.x = x;
		((t_cone *)s_pixel->arr_object3d[i].data)->p2.y = y;
	}
	else if (s_pixel->arr_object3d[i].type_of_data == 2)
		ft_change_object_left_right1(s_pixel, i, angle_z);
}

void	ft_change_object(t_elem *s_pixel, double angle_x, double angle_z, int i)
{
	i = s_pixel->figure_now;
	if (i > -1)
	{
		if (s_pixel->event.key.keysym.sym == SDLK_UP ||
		s_pixel->event.key.keysym.sym == SDLK_DOWN)
		{
			if (s_pixel->event.key.keysym.sym == SDLK_UP)
				angle_x = 1.0;
			else
				angle_x = -1.0;
			angle_x = angle_x / 180.0 * 3.14;
			ft_change_object_up_down(s_pixel, i, angle_x);
		}
		else if (s_pixel->event.key.keysym.sym == SDLK_LEFT ||
		s_pixel->event.key.keysym.sym == SDLK_RIGHT)
		{
			if (s_pixel->event.key.keysym.sym == SDLK_LEFT)
				angle_z = 1.0;
			else
				angle_z = -1.0;
			angle_z = angle_z / 180.0 * 3.14;
			ft_change_object_left_right(s_pixel, i, angle_z);
		}
	}
}
