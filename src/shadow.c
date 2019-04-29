/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 14:24:55 by arudyi            #+#    #+#             */
/*   Updated: 2019/04/29 14:24:57 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

int ft_is_shadow(t_elem *s_pixel, double t, t_vector direction, int i)
{
    int k;
    double tmp;
    double t_max;
    t_vector ray_light;
    t_vector position;

    position = s_pixel->player.position + direction * t;////
    if (s_pixel->arr_light[i].type_of_light == 1)
    {   
        ray_light = s_pixel->arr_light[i].position - position;
        t_max = 1;
    }
    else if (s_pixel->arr_light[i].type_of_light == 2)
    {
        ray_light = s_pixel->arr_light[i].position;
        t_max = DBL_MAX;
    }
    k = -1;
    while (++k < s_pixel->nbr_of_obj)
    {
        if (s_pixel->arr_object3d[k].type_of_data == 0)
        {
            tmp = ft_intersect_ray_sphere(position, s_pixel, ray_light, k);
            if (tmp < t_max && tmp >= 0.00001)
                return (1);//shadow
        }
        else if (s_pixel->arr_object3d[k].type_of_data == 1)
        {
            tmp = ft_intersect_ray_cylinder(position, s_pixel, ray_light, k);
            if (tmp < t_max && tmp >= 0.00001)
                return (1);//shadow
        }
        else if (s_pixel->arr_object3d[k].type_of_data == 2)
        {
            tmp = ft_intersect_ray_plane(position, s_pixel, ray_light, k);
            if (tmp < t_max && tmp >= 0.00001)
                return (1);//shadow
        }
        else if (s_pixel->arr_object3d[k].type_of_data == 3)
        {
            tmp = ft_intersect_ray_cone(position, s_pixel, ray_light, k);
            if (tmp < t_max && tmp >= 0.00001)
                return (1);//shadow
        }
    }
    //no_shadow
    return (0);
}