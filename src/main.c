/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 16:50:13 by arudyi            #+#    #+#             */
/*   Updated: 2019/04/22 20:28:04 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"
#include <stdio.h>

void    print(t_vector a)
{
	printf("{ %lf, %lf, %lf , %lf }\n", a.x, a.y, a.z, a.w);
}

t_vector ft_normalize_vector(t_vector vec)
{
    double len;

    len = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
    vec.x /= len;
    vec.y /= len;
    vec.z /= len;
    
    return (vec);
}

int exit_program(t_elem *s_pixel)
{
	//free(s_pixel);
	exit(1);
    return (0);
}

int mouse_press(int key, int x, int y, t_elem *s_pixel)
{
    if (key == 1)
        s_pixel->keys.but1_press = 1;
    if (key == 2)
        s_pixel->keys.but2_press = 1;
    ft_after_mouse(s_pixel, x, y, key);
    ft_refresh(s_pixel);
    ft_main_draw(s_pixel);
    return (0);
}

void ft_after_mouse(t_elem *s_pixel, int x, int y, int key)
{
    int i;

    //printf("Hi\n");
    i = ft_get_object(s_pixel, x, y);
    if (s_pixel->is_intersect == 1)
    {
        if (s_pixel->keys.but1_press == 1 && key == 4)
        {
            //printf("Hi1\n");
            if (s_pixel->arr_object3d[i].type_of_data == 0)
            {
                ((t_sphere *)s_pixel->arr_object3d[i].data)->center.z += 20;
            }
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
        if (s_pixel->keys.but1_press == 1 && key == 5)
        {
            //printf("Hi2\n");
            if (s_pixel->arr_object3d[i].type_of_data == 0)
            {
                ((t_sphere *)s_pixel->arr_object3d[i].data)->center.z -= 20;
            }
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
        s_pixel->is_intersect = 0;
    }
}

int mouse_release(int key, int x, int y, t_elem *s_pixel)
{
    if (key == 1)
        s_pixel->keys.but1_press = 0;
    if (key == 2)
        s_pixel->keys.but2_press = 0;
    ft_refresh(s_pixel);
    ft_main_draw(s_pixel);
    return (0);
}

int ft_get_object(t_elem *s_pixel, int x, int y)
{
    t_vector direction;
    int i;
    int k;
    double t;
    double tmp;
  
    t = DBL_MAX;
    i = -1;
    while (++i < s_pixel->nbr_of_obj)
    {
        direction = ft_canvas_to_viewport(x, y);
        direction = ft_rotate_camera(direction, s_pixel);
        if (s_pixel->arr_object3d[i].type_of_data == 0)
        {
            if ((tmp = ft_intersect_ray_sphere(s_pixel->player.position, s_pixel, direction, i)) > 0)
            {
                if (tmp < t && tmp >= 0)
                {
                    t = tmp;
                    s_pixel->is_intersect = 1;
                    k = i;
                }
            }
        }
        if (s_pixel->arr_object3d[i].type_of_data == 3)
        {
            if ((tmp = ft_intersect_ray_cone(s_pixel->player.position, s_pixel, direction, i)) > 0)
            {
                if (tmp < t && tmp >= 0)
                {
                    t = tmp;
                    s_pixel->is_intersect = 1;
                    k = i;
                }
            }
        }
        if (s_pixel->arr_object3d[i].type_of_data == 1)
        {
            if ((tmp = ft_intersect_ray_cylinder(s_pixel->player.position, s_pixel, direction, i)) > 0)
            {
                if (tmp < t && tmp >= 0)
                {
                    t = tmp;
                    s_pixel->is_intersect = 1;
                    k = i;
                }
            }
        }
    }
    if (s_pixel->is_intersect == 1)
        return (k);
    return (-1);
}

int mouse_move(int x, int y, t_elem *s_pixel)
{
    static double pre_x = 0;
    static double pre_y = 0;
    static int first = 0;
    int i;

    if (first++ == 0)
    {
        pre_x = x;
        pre_y = y;
    }
    if (s_pixel->keys.but1_press == 1)
    {
        i = ft_get_object(s_pixel, x, y);
        if (s_pixel->is_intersect == 1)
        {
            //printf("HI\n");
            if (s_pixel->arr_object3d[i].type_of_data == 0)
            {
                ((t_sphere *)s_pixel->arr_object3d[i].data)->center.x += x - pre_x;
                ((t_sphere *)s_pixel->arr_object3d[i].data)->center.y += pre_y - y;
            }
            if (s_pixel->arr_object3d[i].type_of_data == 1)
            {
                ((t_cylinder *)s_pixel->arr_object3d[i].data)->p1.x += x - pre_x;
                ((t_cylinder *)s_pixel->arr_object3d[i].data)->p1.y += pre_y - y;
                ((t_cylinder *)s_pixel->arr_object3d[i].data)->p2.x += x - pre_x;
                ((t_cylinder *)s_pixel->arr_object3d[i].data)->p2.y += pre_y - y;
            }
            if (s_pixel->arr_object3d[i].type_of_data == 3)
            {
                ((t_cone *)s_pixel->arr_object3d[i].data)->p1.x += (x - pre_x);
                ((t_cone *)s_pixel->arr_object3d[i].data)->p1.y += (pre_y - y);
                ((t_cone *)s_pixel->arr_object3d[i].data)->p2.x += (x - pre_x);
                ((t_cone *)s_pixel->arr_object3d[i].data)->p2.y += (pre_y - y);
                //print(((t_cone *)s_pixel->arr_object3d[i].data)->p1);
                //print(((t_cone *)s_pixel->arr_object3d[i].data)->p2);
            }
            s_pixel->is_intersect = 0;
        }
    }
    pre_x = x;
    pre_y = y;
    ft_refresh(s_pixel);
    ft_main_draw(s_pixel);
    return (0);
}

void ft_refresh(t_elem *s_pixel)
{
    int bits_per_pixel;
	int endian;

	mlx_destroy_image(s_pixel->mlx_ptr, s_pixel->img_ptr);
	s_pixel->img_ptr = mlx_new_image(s_pixel->mlx_ptr, WIDTH, HEIGHT);
	s_pixel->begin_str = mlx_get_data_addr(s_pixel->img_ptr, &bits_per_pixel,
	&s_pixel->size_line, &endian);
}

void ft_wait_for_input(t_elem *s_pixel)
{
    char *line;
    int res;

    res = get_next_line(0, &line);
    //printf("%d\n", res);
    if (res == 1)
    {
        //printf("%s\n", line);
        if (ft_validate_input(line, s_pixel) == 1)
        {
            //printf("WIN\n");
            ft_refresh(s_pixel);
            ft_main_draw(s_pixel);
        }
    }
}

void ft_change_position(int key, t_elem *s_pixel)
{
    double angle1;
    double angle2;

    angle1 = s_pixel->player.angle_gor / 180 * 3.14;
    angle2 = s_pixel->player.angle_ver / 180 * 3.14;
    if (key == 12)
        s_pixel->player.position.y += 20;//up
    if (key == 6)
        s_pixel->player.position.y -= 20;//down
    if (key == 13)
    {
        s_pixel->player.position.x = s_pixel->player.position.x + 40 * sin(angle1);
        s_pixel->player.position.z = s_pixel->player.position.z + 40 * cos(angle1);
        s_pixel->player.position.y = s_pixel->player.position.y + 40 * sin(angle2);
    }
    if (key == 1)
    {
        s_pixel->player.position.x = s_pixel->player.position.x + -40 * sin(angle1);
        s_pixel->player.position.z = s_pixel->player.position.z + -40 * cos(angle1);
        s_pixel->player.position.y = s_pixel->player.position.y + -40 * sin(angle2);
    }
    if (key == 0)
        s_pixel->player.angle_gor = (s_pixel->player.angle_gor <= 0) ? 360 : s_pixel->player.angle_gor - 1;
    if (key == 2)
        s_pixel->player.angle_gor = (s_pixel->player.angle_gor >= 360) ? 1 : s_pixel->player.angle_gor + 1;
    if (key == 8)
        s_pixel->player.angle_ver = (s_pixel->player.angle_ver <= 0) ? 360 : s_pixel->player.angle_ver - 1;
    if (key == 14)
        s_pixel->player.angle_ver = (s_pixel->player.angle_ver >= 360) ? 1 : s_pixel->player.angle_ver + 1;
}

void ft_change_object(int key, t_elem *s_pixel)
{

}

void ft_change_light(int key, t_elem *s_pixel)
{
    int i;

    i = -1;
    if (key == 18)
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

void ft_change_specular(int key, t_elem *s_pixel)
{
    int i;

    i = -1;
    if (key == 20)
    {
        while (++i < s_pixel->nbr_of_obj)
        {
            s_pixel->arr_object3d[i].specular -= 20;
            if (s_pixel->arr_object3d[i].specular < 0)
                s_pixel->arr_object3d[i].specular = 0;   
        }
    }
    else
    {
        while (++i < s_pixel->nbr_of_obj)
        {
            s_pixel->arr_object3d[i].specular += 20;
            if (s_pixel->arr_object3d[i].specular >= 300)
                s_pixel->arr_object3d[i].specular = 300; 
        }
    }
}

void ft_change_reflective(int key, t_elem *s_pixel)
{
    int i;

    i = -1;
    if (key == 23)
    {
        while (++i < s_pixel->nbr_of_obj)
        {
            if (s_pixel->arr_object3d[i].type_of_data == 2)
                continue ;
            s_pixel->arr_object3d[i].reflective -= 0.1;
            if (s_pixel->arr_object3d[i].reflective < 0)
                s_pixel->arr_object3d[i].reflective = 0;   
        }
    }
    else
    {
        while (++i < s_pixel->nbr_of_obj)
        {
            if (s_pixel->arr_object3d[i].type_of_data == 2)
                continue ;
            s_pixel->arr_object3d[i].reflective += 0.1;
            if (s_pixel->arr_object3d[i].reflective >= 1)
                s_pixel->arr_object3d[i].reflective = 1; 
        }
    }
}

int	ft_check_key(int key, t_elem *s_pixel)
{
	if (key == 53)
		exit_program(s_pixel);
    if (key == 10)
        ft_wait_for_input(s_pixel);
    if (key == 0 || key == 1 || key == 2 || key == 13 || key == 12 || key == 6 || key == 14 || key == 8)
        ft_change_position(key, s_pixel);
    //if (key == 78 || key == 69)
        //ft_change_object(key, s_pixel);
    if (key == 18 || key == 19)
        ft_change_light(key, s_pixel);
    if (key == 20 || key == 21)
        ft_change_specular(key, s_pixel);
    if (key == 23 || key == 22)
        ft_change_reflective(key, s_pixel);
    ft_refresh(s_pixel);
    ft_main_draw(s_pixel);
	return (0);
}

void    ft_pixel_to_image(t_elem *s_pixel, int x, int y, int color)
{
	int index;

	index = s_pixel->size_line * y + x * 4;
	*(unsigned *)(s_pixel->begin_str + index) = color;
}

double  ft_dot_product(t_vector vec1, t_vector vec2)
{
    double nbr;

    nbr = vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
    return (nbr);
}

double ft_intersect_ray_sphere(t_vector position, t_elem *s_pixel, t_vector direction, int i)
{
    double t1;
    double t2;
    double a;
    double b;
    double c;
    double discriminant;
    double radius;
    t_vector oc;

    oc = position - ((t_sphere *)s_pixel->arr_object3d[i].data)->center;
    radius = ((t_sphere *)s_pixel->arr_object3d[i].data)->radius;
    a = ft_dot_product(direction, direction);
    b = 2 * ft_dot_product(oc, direction);
    c = ft_dot_product(oc, oc) - radius * radius;
    discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return (-1);
    t1 = (-b + sqrt(discriminant)) / (2 * a);
    t2 = (-b - sqrt(discriminant)) / (2 * a);
    if (t1 >= 0 && t2 >= 0)
    {
        if (t1 < t2)
            return (t1);
        return (t2);
    }
    else
    {
        if (t1 >= 0 && t2 < 0)
            return (t1);
        if (t1 < 0 && t2 >= 0)
            return (t2);
    }
    return (-1);
}

double ft_intersect_ray_plane(t_vector position, t_elem *s_pixel, t_vector direction, int i)
{
    t_vector x;
    t_vector normal;
    double k1;
    double k2;

    x = position - ((t_plane *)s_pixel->arr_object3d[i].data)->point;
    normal = ft_normalize_vector(((t_plane *)s_pixel->arr_object3d[i].data)->normal - ((t_plane *)s_pixel->arr_object3d[i].data)->point);
    k1 = ft_dot_product(-x, normal);
    k2 = ft_dot_product(direction, normal);
    if (k2 == 0)
        return (-1);
    return (k1 / k2);
}

double ft_intersect_ray_cone(t_vector position, t_elem *s_pixel, t_vector direction, int i)
{
    double a;
    double b;
    double c;
    double t1;
    double t2;
    double discriminant;
    double k;
    double m1;
    double m2;
    t_vector x;
    t_vector v;
    
    v = ft_normalize_vector(((t_cone *)s_pixel->arr_object3d[i].data)->p2 - ((t_cone *)s_pixel->arr_object3d[i].data)->p1); // v axis unit_vector
    //direction = ft_normalize_vector(direction);
    x = position - ((t_cone *)s_pixel->arr_object3d[i].data)->p1;

    k = tan(((t_cone *)s_pixel->arr_object3d[i].data)->angle / 2.0 / 180.0 * 3.14);
    
    a = ft_dot_product(direction, direction) - (1.0 + k * k) * pow(ft_dot_product(direction, v), 2);
    b = ft_dot_product(direction, x) - (1.0 + k * k) * ft_dot_product(direction, v) * ft_dot_product(x, v);
    b = b * 2.0;
    c = ft_dot_product(x, x) - (1.0 + k * k) * pow(ft_dot_product(x, v), 2);

    discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return (-1);
    /*if (discriminant == 0)
        return (-b / 2 * a);*/
    t1 = (-b + sqrt(discriminant)) / (2 * a);
    t2 = (-b - sqrt(discriminant)) / (2 * a);
   
    m1 = ft_dot_product((position + direction * t1) - ((t_cone *)s_pixel->arr_object3d[i].data)->p1, v);//projection on axis
    m2 = ft_dot_product((position + direction * t2) - ((t_cone *)s_pixel->arr_object3d[i].data)->p1, v);
    if (t1 >= 0 && t2 >= 0)
    {
        if (t1 <= t2)
            if (0 < m1 && m1 <=  ((t_cone *)s_pixel->arr_object3d[i].data)->height)
                return (t1);
        if (t2 < t1)
            if (0 < m2 && m2 <= ((t_cone *)s_pixel->arr_object3d[i].data)->height)
                return (t2);
    }
    else
    {
        if (t1 >= 0 && t2 < 0)
            if (0 < m1 && m1 <= ((t_cone *)s_pixel->arr_object3d[i].data)->height)
                return (t1);
        if (t1 < 0 && t2 >= 0)
            if (0 < m2 && m2 <= ((t_cone *)s_pixel->arr_object3d[i].data)->height)
                return (t2);
    }
    return (-1);
}

double ft_intersect_ray_cylinder(t_vector position, t_elem *s_pixel, t_vector direction, int i)
{
    double kx;
    double kz;
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
    v = ft_normalize_vector(((t_cylinder *)s_pixel->arr_object3d[i].data)->p1 - ((t_cylinder *)s_pixel->arr_object3d[i].data)->p2);
    x = position - ((t_cylinder *)s_pixel->arr_object3d[i].data)->p1;
    kx = position.x - ((t_cylinder *)s_pixel->arr_object3d[i].data)->p1.x;
    kz = position.z - ((t_cylinder *)s_pixel->arr_object3d[i].data)->p1.z;
    a = direction.x * direction.x + direction.z * direction.z;
    b = (direction.x) * kx + (direction.z) * kz;
    b = b * 2;
    c = pow(kx, 2) + pow(kz, 2) - pow(radius, 2);
    discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return (-1);
    t1 = (-b + sqrt(discriminant)) / (2 * a);
    t2 = (-b - sqrt(discriminant)) / (2 * a);

    m1 = ft_dot_product(direction, v) * t1 + ft_dot_product(x, v);
    m2 = ft_dot_product(direction, v) * t2 + ft_dot_product(x, v);

    if (t1 >= 0 && t2 >= 0)
    {
        if (t1 <= t2)
            if (0 <= m1 && m1 <= ((t_cylinder *)s_pixel->arr_object3d[i].data)->height)
                return (t1);
        if (t2 < t1)
            if (0 <= m2 && m2 <= ((t_cylinder *)s_pixel->arr_object3d[i].data)->height)
                return (t2);
    }
    else
    {
        if (t1 >= 0 && t2 < 0)
            if (0 <= m1 && m1 <= ((t_cylinder *)s_pixel->arr_object3d[i].data)->height)
                return (t1);
        if (t1 < 0 && t2 >= 0)
            if (0 <= m2 && m2 <= ((t_cylinder *)s_pixel->arr_object3d[i].data)->height)
                return (t2);
    }
    return (-1);
}

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
        t_max = ft_vector_len(ray_light);
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
            if (tmp < t_max && tmp >= DBL_MIN)
                return (1);//shadow
        }
        else if (s_pixel->arr_object3d[k].type_of_data == 1)
        {
            tmp = ft_intersect_ray_cylinder(position, s_pixel, ray_light, k);
            if (tmp < t_max && tmp >= DBL_MIN)
                return (1);//shadow
        }
        else if (s_pixel->arr_object3d[k].type_of_data == 2)
        {
            tmp = ft_intersect_ray_plane(position, s_pixel, ray_light, k);
            if (tmp < t_max && tmp >= DBL_MIN)
                return (1);//shadow
        }
        else if (s_pixel->arr_object3d[k].type_of_data == 3)
        {
            tmp = ft_intersect_ray_cone(position, s_pixel, ray_light, k);
            if (tmp < t_max && tmp >= DBL_MIN)
                return (1);//shadow
        }
    }
    //no_shadow
    return (0);
}

t_vector ft_reflect_ray(t_vector r, t_vector normal)
{
    return (2 * normal * ft_dot_product(normal, r) - r);
}

int ft_trace_ray(t_vector position, t_elem *s_pixel, t_vector direction, int depth)
{
    int i;
    double t;
    double tmp;
    double local_color;
    double reflect;
    t_vector normal;
    double m;

    local_color = 0x000000;
    i = -1;
    t = s_pixel->t_max;
    ////local color
    while (++i < s_pixel->nbr_of_obj)
    {
        if (s_pixel->arr_object3d[i].type_of_data == 0)
        {
            tmp = ft_intersect_ray_sphere(position, s_pixel, direction, i);
            if (tmp < t && tmp >= s_pixel->t_min)
            {
                //printf("sphere = %f\n", tmp);
                t = tmp;
                normal = ft_normalize_vector((position + direction * t) - ((t_sphere *)s_pixel->arr_object3d[i].data)->center);
                s_pixel->normal_now = normal;
                s_pixel->is_intersect = 1;
                local_color = s_pixel->arr_object3d[i].color;
                reflect = s_pixel->arr_object3d[i].reflective;
                s_pixel->obj_now = i;
            }
        }
        else if (s_pixel->arr_object3d[i].type_of_data == 1)
        {
            tmp = ft_intersect_ray_cylinder(position, s_pixel, direction, i);
            if (tmp < t && tmp >= s_pixel->t_min)
            {
                t = tmp;
                t_vector vec = ft_normalize_vector(((t_cylinder *)s_pixel->arr_object3d[i].data)->p2 - ((t_cylinder *)s_pixel->arr_object3d[i].data)->p1);
                m = ft_dot_product((position + direction * t) - ((t_cylinder *)s_pixel->arr_object3d[i].data)->p1, vec);
                normal = ft_normalize_vector(((position + direction * t) - ((t_cylinder *)s_pixel->arr_object3d[i].data)->p1 - (vec * m)));//////////////
                s_pixel->normal_now = normal;
                s_pixel->is_intersect = 1;
                local_color = s_pixel->arr_object3d[i].color;
                reflect = s_pixel->arr_object3d[i].reflective;
                s_pixel->obj_now = i;
            }
        }
        else if (s_pixel->arr_object3d[i].type_of_data == 2)
        {
            tmp = ft_intersect_ray_plane(position, s_pixel, direction, i);
            if (tmp < t && tmp >= s_pixel->t_min)
            {
                //printf("plane = %f\n", tmp);
                t = tmp;
                normal = ft_normalize_vector((position + direction * t) + (((t_plane *)s_pixel->arr_object3d[i].data)->normal));
                s_pixel->normal_now = normal;
                s_pixel->is_intersect = 1;
                local_color = s_pixel->arr_object3d[i].color;
                reflect = s_pixel->arr_object3d[i].reflective;
                s_pixel->obj_now = i;
            }
        }
        else if (s_pixel->arr_object3d[i].type_of_data == 3)
        {
            tmp = ft_intersect_ray_cone(position, s_pixel, direction, i);
            if (tmp < t && tmp >= s_pixel->t_min)
            {
                t = tmp;
                t_vector vec1 = (position + (direction * t)) - ((t_cone *)s_pixel->arr_object3d[i].data)->p1;
                t_vector vec2 = ft_normalize_vector(((t_cone *)s_pixel->arr_object3d[i].data)->p2 - ((t_cone *)s_pixel->arr_object3d[i].data)->p1);
                m = ft_vector_len(vec1) / cos(((t_cone *)s_pixel->arr_object3d[i].data)->angle / 2.0 / 180.0 * 3.14);
                normal = ft_normalize_vector(vec1 - (vec2 * m));
                s_pixel->is_intersect = 1;
                s_pixel->normal_now = normal;
                local_color = s_pixel->arr_object3d[i].color;
                reflect = s_pixel->arr_object3d[i].reflective;
                s_pixel->obj_now = i;
            }
        }
    }
    //s_pixel->color_now = local_color;
    if (s_pixel->is_intersect == 0)
        return (local_color);
    //////not reflective or depth <= 0 ====>exit
    local_color = ft_lighting(local_color, t, s_pixel, position + direction * t, direction);
    if (depth < 0 || reflect < 0.0)
        return (local_color);
    /// reflect color
    t_vector r = ft_reflect_ray(-direction, normal);
    s_pixel->t_max = DBL_MAX;
    s_pixel->t_min = 0.00001;//DBL_MIN;
    double reflect_color1 = ft_trace_ray(position + direction * t, s_pixel, r, depth - 1);    
    return (ft_add_color(ft_change_color(local_color, (1.0 - reflect)), ft_change_color(reflect_color1, reflect)));
}

unsigned ft_add_color(unsigned color1, unsigned color2)
{
    unsigned new_color;
    unsigned r1;
    unsigned g1;
    unsigned b1;
    unsigned r2;
    unsigned g2;
    unsigned b2;

    r1 = color1 >> 16;
    g1 = color1 << 16 >> 24;
    b1 = color1 << 24 >> 24;

    r2 = color2 >> 16;
    g2 = color2 << 16 >> 24;
    b2 = color2 << 24 >> 24;

    r1 += r2;
    if (r1 > 255)
        r1 = 255;
    g1 += g2;
    if (g1 > 255)
        g1 = 255;
    b1 += b2;
    if (b1 > 255)
        b1 = 255;
    new_color = (r1 << 16) | (g1 << 8) | (b1 << 0);
    return (new_color);
}

int ft_lighting(int color, int t, t_elem *s_pixel, t_vector position, t_vector direction)
{
    int i;
    double k;
    double n_dot_l;
    double r_dot_v;
    t_vector normal;
    t_vector ray_light;
    t_vector r;
    
    normal = s_pixel->normal_now;
    k = 0.1;
    i = -1;
    while (++i < s_pixel->nbr_of_light)
    {
        if (s_pixel->arr_light[i].type_of_light == 0)
            k += s_pixel->arr_light[i].intensity;
        else
        {
            if (s_pixel->arr_light[i].type_of_light == 1)
                ray_light = s_pixel->arr_light[i].position - position;
            else
                ray_light = s_pixel->arr_light[i].position;
            //////shadow
            if (ft_is_shadow(s_pixel, t, direction, i) == 1)
               continue ;
            /////////Diffuse
            n_dot_l = ft_dot_product(normal, ray_light);
            if (n_dot_l > 0)//> 0
                k += s_pixel->arr_light[i].intensity * n_dot_l / ft_vector_len(ray_light);
            //specular
            if (s_pixel->arr_object3d[s_pixel->obj_now].specular > 0)
            {
                r = 2 * normal * ft_dot_product(normal, ray_light) - ray_light;
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

double ft_vector_len(t_vector vec)
{
    double len;

    len = sqrt(ft_dot_product(vec, vec)); 
    return (len);
}

unsigned ft_change_color(unsigned color, double k)
{
    unsigned r;
    unsigned g;
    unsigned b;

    r = color >> 16;
    g = color << 16 >> 24;
    b = color << 24 >> 24;
    
    r *= k;
    if (r > 255)
        r = 255;
    g *= k;
    if (g > 255)
        g = 255;
    b *= k;
    if (b > 255)
        b = 255;
    color = (r << 16) | (g << 8) | (b << 0);
    return (color);
}

void ft_draw_display(t_elem *s_pixel, int x, int y)
{
    t_vector direction;
    int color;

    s_pixel->t_max = DBL_MAX;
    s_pixel->t_min = 0;
    while (++x < WIDTH)
    {
        y = -1;
        while (++y < HEIGHT)
        {
            direction = ft_canvas_to_viewport(x, y);
            direction = ft_rotate_camera(direction, s_pixel);
            color = ft_trace_ray(s_pixel->player.position, s_pixel, direction, s_pixel->depth_recursive);
            if (s_pixel->is_intersect == 1)
            {
                s_pixel->t_max = DBL_MAX;
                s_pixel->t_min = 0;
                ft_pixel_to_image(s_pixel, x, y, color);
                s_pixel->is_intersect = 0;
            }
            else
                ft_pixel_to_image(s_pixel, x, y, 0x000000);   
        }
    }
    s_pixel->player.rotate_left = 0;
    s_pixel->player.rotate_right = 0;
}

t_vector ft_canvas_to_viewport(double x, double y) 
{
    t_vector direction;

    direction.x = x / WIDTH - 0.5;
    direction.y = 0.5 + -y / HEIGHT;
    direction.z = 1;
    return (direction);
}

t_vector ft_rotate_camera(t_vector direction, t_elem *s_pixel)/*nop*/
{
    double new_x;
    double new_y;
    double new_z;
    double angle1;
    double angle2;

    angle1 = s_pixel->player.angle_gor / 180.0 * 3.14;
    angle2 = s_pixel->player.angle_ver / 180.0 * 3.14;
  
    //gor
    new_x = direction.x * cos(angle1) + direction.z * sin(angle1);
    new_y = direction.y;
    new_z = -direction.x * sin(angle1) + direction.z * cos(angle1);
    direction.x = new_x;
    direction.y = new_y;
    direction.z = new_z;
    //ver
    new_x = direction.x;
    new_y = direction.y * cos(angle2) + direction.z * sin(angle2);
    new_z = -direction.y * sin(angle2) + direction.z * cos(angle2);
    direction.x = new_x;
    direction.y = new_y;
    direction.z = new_z;
    return (direction);
}

int ft_validate_input(char *line, t_elem *s_pixel)/*op*/
{
    static int i = 0;
    static int k = 0;
    t_sphere *s_sphere;
    t_plane *plane;
    t_cone *cone;
    t_cylinder *cylinder;

    if (s_pixel->nbr_of_obj > 98)
    {
        write(1, "A lot of objects\n", 17);
        return (0);
    }
    else if (ft_strcmp(line, "add sphere") == 0)
    {
        s_sphere = (t_sphere *)malloc(sizeof(t_sphere));
        s_sphere->center.x = s_pixel->player.position.x;
        s_sphere->center.y = s_pixel->player.position.y;
        s_sphere->center.z = s_pixel->player.position.z + 1000;
        s_sphere->radius = 100.0;
        s_pixel->arr_object3d[i].reflective = 0.5;////////////////////////////
        s_pixel->arr_object3d[i].specular = 100;
        s_pixel->arr_object3d[i].color = 0x999900;
        s_pixel->arr_object3d[i].type_of_data = 0;
        s_pixel->arr_object3d[i].data = (t_sphere *)s_sphere;
        s_pixel->nbr_of_obj++;
        i++;
        return (1);
    }
    else if (ft_strcmp(line, "add cylinder") == 0)
    {
        cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
        
        cylinder->p1.x = s_pixel->player.position.x;
        cylinder->p1.y = s_pixel->player.position.y;
        cylinder->p1.z = s_pixel->player.position.z + 1000;

        cylinder->p2.x = s_pixel->player.position.x;
        cylinder->p2.y = s_pixel->player.position.y + 1;
        cylinder->p2.z = s_pixel->player.position.z + 1000;

        cylinder->radius = 50;
        cylinder->height = 250;
        s_pixel->arr_object3d[i].reflective = 0.5;//0.7
        s_pixel->arr_object3d[i].specular = 100;
        s_pixel->arr_object3d[i].color = 0x007700;
        s_pixel->arr_object3d[i].type_of_data = 1;
        s_pixel->arr_object3d[i].data = (t_cylinder *)cylinder;
        s_pixel->nbr_of_obj++;
        i++;
        return (1);
    }
    else if (ft_strcmp(line, "add plane") == 0)
    {
        plane = (t_plane *)malloc(sizeof(t_plane));
        plane->point.x = 0;
        plane->point.y = -300; 
        plane->point.z = 1000;
        plane->normal.x = 0;
        plane->normal.y = -299;
        plane->normal.z = 1000;
        s_pixel->arr_object3d[i].reflective = 0.5;
        s_pixel->arr_object3d[i].specular = 100; // 200
        s_pixel->arr_object3d[i].color = 0x999999;
        s_pixel->arr_object3d[i].type_of_data = 2;
        s_pixel->arr_object3d[i].data = (t_plane *)plane;
        s_pixel->nbr_of_obj++;
        i++;
        return (1);
    }
    else if (ft_strcmp(line, "add cone") == 0)
    {
        cone = (t_cone *)malloc(sizeof(t_cone));

        cone->p1.x = s_pixel->player.position.x;
        cone->p1.y = s_pixel->player.position.y - 1;
        cone->p1.z = s_pixel->player.position.z + 1000;

        cone->p2.x = s_pixel->player.position.x;
        cone->p2.y = s_pixel->player.position.y - 2;
        cone->p2.z = s_pixel->player.position.z + 1000;
    
        cone->height = 200;
        cone->angle = 45;
        s_pixel->arr_object3d[i].reflective = 0.5;
        s_pixel->arr_object3d[i].specular = 100;
        s_pixel->arr_object3d[i].color = 0x005599;
        s_pixel->arr_object3d[i].data = (t_cone *)cone;
        s_pixel->arr_object3d[i].type_of_data = 3;
        s_pixel->nbr_of_obj++;
        i++;
        return (1);
    }
    else if (ft_strcmp(line, "add ambient light") == 0)
    {
        if (k > 8)
        {
            write(1, "Light max!\n", 11);
            return (0);
        }
        s_pixel->arr_light[k].type_of_light = 0;
        s_pixel->arr_light[k].intensity = 0.3;
        s_pixel->nbr_of_light++;
        k++;
        return (1);
    }
    else if (ft_strcmp(line, "add point light") == 0)
    {
        if (k > 8)
        {
            write(1, "Light max!\n", 11);
            return (0);
        }
        s_pixel->arr_light[k].type_of_light = 1;
        s_pixel->arr_light[k].intensity = 1.0;
        s_pixel->arr_light[k].position.x = s_pixel->player.position.x;
        s_pixel->arr_light[k].position.y = s_pixel->player.position.y;
        s_pixel->arr_light[k].position.z = s_pixel->player.position.z + 1000;
        s_pixel->nbr_of_light++;
        k++;
        return (1);
    }
    else if (ft_strcmp(line, "add directional light") == 0)
    {
        if (k > 8)
        {
            write(1, "Light max!\n", 11);
            return (0);
        }
        s_pixel->arr_light[k].type_of_light = 2;
        s_pixel->arr_light[k].intensity = 1.0;
        s_pixel->arr_light[k].position.x = 50000;
        s_pixel->arr_light[k].position.y = 50000;
        s_pixel->arr_light[k].position.z = 50000;
        s_pixel->nbr_of_light++;
        k++;
        return (1);
    }
    return (0);
}

void ft_main_draw(t_elem *s_pixel)
{
	ft_draw_display(s_pixel, -1, -1);
	mlx_put_image_to_window(s_pixel->mlx_ptr, s_pixel->win_ptr, s_pixel->img_ptr, 0, 0);
    //system("leaks rtv1");
    //exit(1);//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    mlx_hook(s_pixel->win_ptr, 4, 5, mouse_press, s_pixel);
	mlx_hook(s_pixel->win_ptr, 5, 5, mouse_release, s_pixel);
	mlx_hook(s_pixel->win_ptr, 6, 5, mouse_move, s_pixel);
    mlx_hook(s_pixel->win_ptr, 2, 5, ft_check_key, s_pixel);
	mlx_hook(s_pixel->win_ptr, 17, 1L << 17, exit_program, s_pixel);
    mlx_loop(s_pixel->mlx_ptr);
}

void ft_prepare_programm(t_elem *s_pixel)
{
	int bits_per_pixel;
	int endian;

	s_pixel->mlx_ptr = mlx_init();
	s_pixel->win_ptr = mlx_new_window(s_pixel->mlx_ptr, WIDTH, HEIGHT, "rtv1");
	s_pixel->img_ptr = mlx_new_image(s_pixel->mlx_ptr, WIDTH, HEIGHT);
	s_pixel->begin_str = mlx_get_data_addr(s_pixel->img_ptr, &bits_per_pixel, &s_pixel->size_line, &endian);
    s_pixel->player.position = (t_vector){0, 0, 0};
    s_pixel->is_intersect = 0;
    s_pixel->depth_recursive = 3;
    s_pixel->player.angle_gor = 0;
    s_pixel->player.angle_ver = 0;
    s_pixel->player.pov = (t_vector){0, 0, 1};
    s_pixel->nbr_of_obj = 0;
    s_pixel->nbr_of_light = 0;
    s_pixel->player.rotate_right = 0;
    s_pixel->player.rotate_left = 0;
    ft_validate_input("add plane", s_pixel);
    //ft_validate_input("add point light", s_pixel);
    ft_validate_input("add directional light", s_pixel);
    //ft_validate_input("add cone", s_pixel);
    ft_validate_input("add sphere", s_pixel);
    //ft_validate_input("add cylinder", s_pixel);
    ft_main_draw(s_pixel);
}

int main(void)
{
	t_elem          *s_pixel;

	if (!(s_pixel = (t_elem *)malloc(sizeof(t_elem))))
		exit(0);
    ft_prepare_programm(s_pixel);
	return (0);
}