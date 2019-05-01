/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 20:08:22 by arudyi            #+#    #+#             */
/*   Updated: 2019/05/01 14:27:20 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

void	ft_validate_sphere(t_elem *s_pixel, int i)
{
	t_sphere *s_sphere;

	s_sphere = (t_sphere *)malloc(sizeof(t_sphere));
	s_sphere->center.x = s_pixel->player.position.x + 200;
	s_sphere->center.y = s_pixel->player.position.y;
	s_sphere->center.z = s_pixel->player.position.z + 1000;
	s_sphere->radius = 100.0;
	s_pixel->arr_object3d[i].reflective = 0.1;
	s_pixel->arr_object3d[i].specular = 100;
	s_pixel->arr_object3d[i].color = 0x999900;
	s_pixel->arr_object3d[i].type_of_data = 0;
	s_pixel->arr_object3d[i].data = (t_sphere *)s_sphere;
	s_pixel->nbr_of_obj++;
	s_pixel->player.i++;
}

void	ft_validate_cylinder(t_elem *s_pixel, int i)
{
	t_cylinder *cylinder;

	cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	cylinder->p1.x = s_pixel->player.position.x;
	cylinder->p1.y = s_pixel->player.position.y;
	cylinder->p1.z = s_pixel->player.position.z + 1000;
	cylinder->p2.x = s_pixel->player.position.x;
	cylinder->p2.y = s_pixel->player.position.y - 100;
	cylinder->p2.z = s_pixel->player.position.z + 1000;
	cylinder->radius = 50;
	cylinder->height = 250;
	s_pixel->arr_object3d[i].reflective = 0.5;
	s_pixel->arr_object3d[i].specular = 100;
	s_pixel->arr_object3d[i].color = 0x007700;
	s_pixel->arr_object3d[i].type_of_data = 1;
	s_pixel->arr_object3d[i].data = (t_cylinder *)cylinder;
	s_pixel->nbr_of_obj++;
	s_pixel->player.i++;
}

void	ft_validate_plane(t_elem *s_pixel, int i)
{
	t_plane *plane;

	plane = (t_plane *)malloc(sizeof(t_plane));
	plane->point.x = s_pixel->player.position.x;
	plane->point.y = s_pixel->player.position.y - 300;
	plane->point.z = s_pixel->player.position.z + 1000;
	plane->normal.x = s_pixel->player.position.x;
	plane->normal.y = s_pixel->player.position.y - 200;
	plane->normal.z = s_pixel->player.position.x + 1000;
	s_pixel->arr_object3d[i].reflective = 0;
	s_pixel->arr_object3d[i].specular = -1;
	s_pixel->arr_object3d[i].color = 0x999999;
	s_pixel->arr_object3d[i].type_of_data = 2;
	s_pixel->arr_object3d[i].data = (t_plane *)plane;
	s_pixel->nbr_of_obj++;
	s_pixel->player.i++;
}

void	ft_validate_cone(t_elem *s_pixel, int i)
{
	t_cone *cone;

	cone = (t_cone *)malloc(sizeof(t_cone));
	cone->p1.x = s_pixel->player.position.x;
	cone->p1.y = s_pixel->player.position.y;
	cone->p1.z = s_pixel->player.position.z + 1000;
	cone->p2.x = s_pixel->player.position.x;
	cone->p2.y = s_pixel->player.position.y - 100;
	cone->p2.z = s_pixel->player.position.z + 1000;
	cone->height = 250;
	cone->angle = 45;
	s_pixel->arr_object3d[i].reflective = 0.5;
	s_pixel->arr_object3d[i].specular = 100;
	s_pixel->arr_object3d[i].color = 0x005599;
	s_pixel->arr_object3d[i].data = (t_cone *)cone;
	s_pixel->arr_object3d[i].type_of_data = 3;
	s_pixel->nbr_of_obj++;
	s_pixel->player.i++;
}

void	ft_validate_amb_light(t_elem *s_pixel, int k)
{
	if (k < 5)
	{
		s_pixel->arr_light[k].type_of_light = 0;
		s_pixel->arr_light[k].intensity = 0.3;
		s_pixel->nbr_of_light++;
		s_pixel->player.k++;
	}
	else
		write(1, "Light max!\n", 11);
}
