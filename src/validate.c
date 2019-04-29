/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 14:17:53 by arudyi            #+#    #+#             */
/*   Updated: 2019/04/29 20:08:47 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

void	ft_validate_poi_light(t_elem *s_pixel, int k)
{
	if (k < 5)
	{
		s_pixel->arr_light[k].type_of_light = 1;
		s_pixel->arr_light[k].intensity = 1.0;
		s_pixel->arr_light[k].position.x = s_pixel->player.position.x;
		s_pixel->arr_light[k].position.y = s_pixel->player.position.y;
		s_pixel->arr_light[k].position.z = s_pixel->player.position.z + 1000;
		s_pixel->nbr_of_light++;
		s_pixel->player.k++;
	}
	else
		write(1, "Light max!\n", 11);
}

void	ft_validate_dir_light(t_elem *s_pixel, int k)
{
	if (k < 5)
	{
		s_pixel->arr_light[k].type_of_light = 2;
		s_pixel->arr_light[k].intensity = 1.0;
		s_pixel->arr_light[k].position.x = 50000;
		s_pixel->arr_light[k].position.y = 50000;
		s_pixel->arr_light[k].position.z = 50000;
		s_pixel->nbr_of_light++;
		s_pixel->player.k++;
	}
	else
		write(1, "Light max!\n", 11);
}

void	ft_validate_input(char *line, t_elem *s_pixel)
{
	if (s_pixel->nbr_of_obj > 9)
		write(1, "A lot of objects\n", 17);
	else if (ft_strcmp(line, "add sphere") == 0)
		ft_validate_sphere(s_pixel, s_pixel->player.i);
	else if (ft_strcmp(line, "add cylinder") == 0)
		ft_validate_cylinder(s_pixel, s_pixel->player.i);
	else if (ft_strcmp(line, "add plane") == 0)
		ft_validate_plane(s_pixel, s_pixel->player.i);
	else if (ft_strcmp(line, "add cone") == 0)
		ft_validate_cone(s_pixel, s_pixel->player.i);
	else if (ft_strcmp(line, "add ambient light") == 0)
		ft_validate_amb_light(s_pixel, s_pixel->player.k);
	else if (ft_strcmp(line, "add point light") == 0)
		ft_validate_poi_light(s_pixel, s_pixel->player.k);
	else if (ft_strcmp(line, "add directional light") == 0)
		ft_validate_dir_light(s_pixel, s_pixel->player.k);
	ft_validate_light(s_pixel, -1, -1);
}

void	ft_validate_light(t_elem *s_pixel, int i, int k)
{
	while (++i < s_pixel->nbr_of_obj)
	{
		if (s_pixel->arr_object3d[i].type_of_data == 3)
		{
			while (++k < s_pixel->nbr_of_light)
			{
				if (s_pixel->arr_light[k].type_of_light == 1)
				{
					if (ft_check_if_equal(s_pixel->arr_light[k].position,
					((t_cone *)s_pixel->arr_object3d[i].data)->p1) == 0)
					{
						s_pixel->arr_light[k].position.x += 1;
						s_pixel->arr_light[k].position.y += 1;
						s_pixel->arr_light[k].position.z += 1;
					}
				}
			}
		}
	}
}

int		ft_check_if_equal(t_vector vec1, t_vector vec2)
{
	if (vec1.x == vec2.x)
		if (vec1.y == vec2.y)
			if (vec1.z == vec2.z)
				return (0);
	return (1);
}
