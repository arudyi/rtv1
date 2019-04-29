/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 14:18:52 by arudyi            #+#    #+#             */
/*   Updated: 2019/04/29 19:20:34 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

double ft_intersect_ray_cylinder(t_vector position, t_elem *s_pixel, t_vector direction, int i)
{
    double t1;
    double t2;
    double a;
    double b;
    double c;
    double radius;
    double discriminant;
    double m1;
    double m2;
    t_vector v;
    t_vector x;
 
    radius = ((t_cylinder *)s_pixel->arr_object3d[i].data)->radius;
    v = ft_normalize_vector(((t_cylinder *)s_pixel->arr_object3d[i].data)->p2 - ((t_cylinder *)s_pixel->arr_object3d[i].data)->p1);
    x = position - ((t_cylinder *)s_pixel->arr_object3d[i].data)->p1;

    a = ft_dot_product(direction, direction) - pow(ft_dot_product(direction, v), 2);
    b = 2.0 * (ft_dot_product(direction, x) - ft_dot_product(direction, v) * ft_dot_product(x, v));
    c = ft_dot_product(x, x) - pow(ft_dot_product(x, v), 2) - pow(radius, 2);
    
    discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return (-1);
    t1 = (-b + sqrt(discriminant)) / (2 * a);
    t2 = (-b - sqrt(discriminant)) / (2 * a);

    m1 = ft_dot_product((position + direction * t1) - ((t_cylinder *)s_pixel->arr_object3d[i].data)->p1, v);
    m2 = ft_dot_product((position + direction * t2) - ((t_cylinder *)s_pixel->arr_object3d[i].data)->p1, v);

    if (t1 >= 0 && t2 >= 0)
    {
        if (t1 <= t2)
            if (0 <= m1 && m1 <= ((t_cylinder *)s_pixel->arr_object3d[i].data)->height)
                return (t1);
        if (0 <= m2 && m2 <= ((t_cylinder *)s_pixel->arr_object3d[i].data)->height)
            return (t2);
    }
    else
    {
        if (t1 >= 0 && t2 < 0)
            if (0 <= m1 && m1 <= ((t_cylinder *)s_pixel->arr_object3d[i].data)->height)
                return (t1);
        if (0 <= m2 && m2 <= ((t_cylinder *)s_pixel->arr_object3d[i].data)->height)
            return (t2);
    }
    return (-1);
}