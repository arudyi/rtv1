/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 14:48:10 by arudyi            #+#    #+#             */
/*   Updated: 2019/05/01 13:32:41 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

void	ft_change_light(t_elem *s_pixel)
{
	int i;

	i = -1;
	if (s_pixel->event.key.keysym.sym == SDLK_1)
	{
		while (++i < s_pixel->nbr_of_light)
		{
			s_pixel->arr_light[i].intensity -= 0.1;
			if (s_pixel->arr_light[i].intensity < 0)
				s_pixel->arr_light[i].intensity = 0;
		}
	}
	else
	{
		while (++i < s_pixel->nbr_of_light)
		{
			s_pixel->arr_light[i].intensity += 0.1;
			if (s_pixel->arr_light[i].intensity >= 2)
				s_pixel->arr_light[i].intensity = 2;
		}
	}
}

void	ft_change_specular(t_elem *s_pixel)
{
	int i;

	i = s_pixel->figure_now;
	if (s_pixel->event.key.keysym.sym == SDLK_3)
	{
		if (i > -1)
		{
			s_pixel->arr_object3d[i].specular -= 20;
			if (s_pixel->arr_object3d[i].specular < 0)
				s_pixel->arr_object3d[i].specular = 0;
		}
	}
	else
	{
		if (i > -1)
		{
			s_pixel->arr_object3d[i].specular += 20;
			if (s_pixel->arr_object3d[i].specular >= 300)
				s_pixel->arr_object3d[i].specular = 300;
		}
	}
}

void	ft_change_reflective(t_elem *s_pixel)
{
	int i;

	i = s_pixel->figure_now;
	if (s_pixel->event.key.keysym.sym == SDLK_5)
	{
		if (i > -1)
		{
			s_pixel->arr_object3d[i].reflective -= 0.1;
			if (s_pixel->arr_object3d[i].reflective < 0)
				s_pixel->arr_object3d[i].reflective = 0;
		}
	}
	else
	{
		if (i > -1)
		{
			s_pixel->arr_object3d[i].reflective += 0.1;
			if (s_pixel->arr_object3d[i].reflective >= 1)
				s_pixel->arr_object3d[i].reflective = 1;
		}
	}
}
