/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_scene2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 17:44:48 by arudyi            #+#    #+#             */
/*   Updated: 2019/04/29 17:45:48 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

void	ft_change_obj_size(t_elem *s_pixel)
{
	int i;

	i = s_pixel->figure_now;
	if (i > -1)
	{
		if (s_pixel->arr_object3d[i].type_of_data == 0)
			ft_change_obj_size_sphere(s_pixel, i);
		else if (s_pixel->arr_object3d[i].type_of_data == 1)
			ft_change_obj_size_cylinder(s_pixel, i);
		else if (s_pixel->arr_object3d[i].type_of_data == 3)
			ft_change_obj_size_cone(s_pixel, i);
	}
}

void	ft_change_obj_size_sphere(t_elem *s_pixel, int i)
{
	if (s_pixel->event.key.keysym.sym == SDLK_KP_PLUS)
		((t_sphere *)s_pixel->arr_object3d[i].data)->radius += 10;
	else
		((t_sphere *)s_pixel->arr_object3d[i].data)->radius -= 10;
	if (((t_sphere *)s_pixel->arr_object3d[i].data)->radius < 10)
		((t_sphere *)s_pixel->arr_object3d[i].data)->radius += 10;
	if (((t_sphere *)s_pixel->arr_object3d[i].data)->radius > 300)
		((t_sphere *)s_pixel->arr_object3d[i].data)->radius -= 10;
}

void	ft_change_obj_size_cylinder(t_elem *s_pixel, int i)
{
	if (s_pixel->event.key.keysym.sym == SDLK_KP_PLUS)
		((t_cylinder *)s_pixel->arr_object3d[i].data)->height += 10;
	else
		((t_cylinder *)s_pixel->arr_object3d[i].data)->height -= 10;
	if (((t_cylinder *)s_pixel->arr_object3d[i].data)->height < 10)
		((t_cylinder *)s_pixel->arr_object3d[i].data)->height += 10;
	if (((t_cylinder *)s_pixel->arr_object3d[i].data)->height > 700)
		((t_cylinder *)s_pixel->arr_object3d[i].data)->height -= 10;
}

void	ft_change_obj_size_cone(t_elem *s_pixel, int i)
{
	if (s_pixel->event.key.keysym.sym == SDLK_KP_PLUS)
		((t_cone *)s_pixel->arr_object3d[i].data)->height += 10;
	else
		((t_cone *)s_pixel->arr_object3d[i].data)->height -= 10;
	if (((t_cone *)s_pixel->arr_object3d[i].data)->height < 10)
		((t_cone *)s_pixel->arr_object3d[i].data)->height += 10;
	if (((t_cone *)s_pixel->arr_object3d[i].data)->height > 700)
		((t_cone *)s_pixel->arr_object3d[i].data)->height -= 10;
}
