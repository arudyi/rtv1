/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 14:18:37 by arudyi            #+#    #+#             */
/*   Updated: 2019/04/29 20:47:39 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

void	ft_mouse_wheel1(t_elem *s_pixel, int i)
{
	if (s_pixel->arr_object3d[i].type_of_data == 0)
		((t_sphere *)s_pixel->arr_object3d[i].data)->center.z -= 20;
	if (s_pixel->arr_object3d[i].type_of_data == 1)
	{
		((t_cylinder *)s_pixel->arr_object3d[i].data)->p1.z -= 20;
		((t_cylinder *)s_pixel->arr_object3d[i].data)->p2.z -= 20;
	}
	if (s_pixel->arr_object3d[i].type_of_data == 3)
	{
		((t_cone *)s_pixel->arr_object3d[i].data)->p1.z -= 20;
		((t_cone *)s_pixel->arr_object3d[i].data)->p2.z -= 20;
	}
}

void	ft_mouse_wheel(t_elem *s_pixel, int i)
{
	if (i >= 0)
	{
		if (s_pixel->event.wheel.x <= 0 && s_pixel->event.wheel.y >= 0)
		{
			if (s_pixel->arr_object3d[i].type_of_data == 0)
				((t_sphere *)s_pixel->arr_object3d[i].data)->center.z += 20;
			if (s_pixel->arr_object3d[i].type_of_data == 1)
			{
				((t_cylinder *)s_pixel->arr_object3d[i].data)->p1.z += 20;
				((t_cylinder *)s_pixel->arr_object3d[i].data)->p2.z += 20;
			}
			if (s_pixel->arr_object3d[i].type_of_data == 3)
			{
				((t_cone *)s_pixel->arr_object3d[i].data)->p1.z += 20;
				((t_cone *)s_pixel->arr_object3d[i].data)->p2.z += 20;
			}
		}
		else
			ft_mouse_wheel1(s_pixel, i);
	}
}

void	ft_mouse_release(t_elem *s_pixel)
{
	if (s_pixel->event.button.button == SDL_BUTTON_LEFT)
	{
		s_pixel->is_intersect = 0;
		s_pixel->keys.but1_press = 0;
	}
	if (s_pixel->event.button.button == SDL_BUTTON_RIGHT)
		s_pixel->is_intersect = 0;
}

void	ft_mouse_move1(t_elem *s_pixel, int i)
{
	double x;
	double y;

	x = s_pixel->event.motion.xrel;
	y = s_pixel->event.motion.yrel;
	if (s_pixel->arr_object3d[i].type_of_data == 1)
	{
		((t_cylinder *)s_pixel->arr_object3d[i].data)->p1.x += x;
		((t_cylinder *)s_pixel->arr_object3d[i].data)->p1.y -= y;
		((t_cylinder *)s_pixel->arr_object3d[i].data)->p2.x += x;
		((t_cylinder *)s_pixel->arr_object3d[i].data)->p2.y -= y;
	}
	else if (s_pixel->arr_object3d[i].type_of_data == 3)
	{
		((t_cone *)s_pixel->arr_object3d[i].data)->p1.x += x;
		((t_cone *)s_pixel->arr_object3d[i].data)->p1.y -= y;
		((t_cone *)s_pixel->arr_object3d[i].data)->p2.x += x;
		((t_cone *)s_pixel->arr_object3d[i].data)->p2.y -= y;
	}
}

void	ft_mouse_move(t_elem *s_pixel, int i)
{
	if (i >= 0)
	{
		if (s_pixel->arr_object3d[i].type_of_data == 0)
		{
			((t_sphere *)s_pixel->arr_object3d[i].data)->center.x +=
			s_pixel->event.motion.xrel;
			((t_sphere *)s_pixel->arr_object3d[i].data)->center.y -=
			s_pixel->event.motion.yrel;
		}
		else if (s_pixel->arr_object3d[i].type_of_data == 2)
		{
			((t_plane *)s_pixel->arr_object3d[i].data)->point.y -=
			s_pixel->event.motion.yrel;
			((t_plane *)s_pixel->arr_object3d[i].data)->normal.y -=
			s_pixel->event.motion.yrel;
		}
		else
			ft_mouse_move1(s_pixel, i);
	}
}
