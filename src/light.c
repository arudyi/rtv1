/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 14:18:45 by arudyi            #+#    #+#             */
/*   Updated: 2019/04/29 21:46:40 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

int ft_lighting(int color, int t, t_elem *s_pixel, t_vector direction)
{
    int i;
    double k;
    double n_dot_l;
    double r_dot_v;
    t_vector ray_light;
    t_vector r;

    k = 0.1;
    i = -1;
    while (++i < s_pixel->nbr_of_light)
    {
        if (s_pixel->arr_light[i].type_of_light == 0)
            k += s_pixel->arr_light[i].intensity;
        else
        {
			//ray_light = RAY_POS; (s_pixel->arr_light[i].type_of_light == 1) ? s_pixel->arr_light[i].position - (s_pixel->player.position + direction * t) : s_pixel->arr_light[i].position;
            if (s_pixel->arr_light[i].type_of_light == 1)
                ray_light = s_pixel->arr_light[i].position - (s_pixel->player.position + direction * t);
            else
                ray_light = s_pixel->arr_light[i].position;
            //////shadow
            if (ft_is_shadow(s_pixel, t, direction, i) == 1)
                continue ;
            /////////Diffuse
            n_dot_l = ft_dot_product(NORMAL, ray_light);
            if (n_dot_l >= 0)//> 0
                k += s_pixel->arr_light[i].intensity * n_dot_l / ft_vector_len(ray_light);
            //specular
            if (s_pixel->arr_object3d[s_pixel->obj_now].specular > 0)
            {
                r = 2.0 * NORMAL * ft_dot_product(NORMAL, ray_light) - ray_light;
                r_dot_v = ft_dot_product(r, -direction);
                if (r_dot_v > 0)
                {
                    k += s_pixel->arr_light[i].intensity * pow(r_dot_v / (ft_vector_len(r) * ft_vector_len(-direction)), s_pixel->arr_object3d[s_pixel->obj_now].specular);
                }
            }
        }
    }
    color = ft_change_color(color, k);
    return (color);
}