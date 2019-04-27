/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 16:50:13 by arudyi            #+#    #+#             */
/*   Updated: 2019/04/27 19:32:14 by arudyi           ###   ########.fr       */
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
    SDL_FreeSurface(s_pixel->surface);
    SDL_DestroyWindow(s_pixel->window);
    SDL_DestroyRenderer(s_pixel->renderrer);
    SDL_Quit();
	system("leaks RTv1");
    exit(1);
    return (0);
}

void ft_mouse_press(t_elem *s_pixel)
{
    if (s_pixel->event.button.button == SDL_BUTTON_LEFT)
    {
        s_pixel->figure_now = ft_get_object(s_pixel, s_pixel->event.motion.x, s_pixel->event.motion.y);
        s_pixel->keys.but1_press = 1;
    }
    if (s_pixel->event.button.button == SDL_BUTTON_RIGHT)
    {
        s_pixel->figure_now = -1;
    }
}

void ft_mouse_wheel(t_elem *s_pixel)
{
    int i;
    
    i = s_pixel->figure_now;
    if (i >= 0)
    {
        if (s_pixel->event.wheel.x <= 0 && s_pixel->event.wheel.y >= 0)
        {
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
        else
        {
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
    }
}

void ft_mouse_release(t_elem *s_pixel)
{
    if (s_pixel->event.button.button == SDL_BUTTON_LEFT)
    {
        s_pixel->is_intersect = 0;
        s_pixel->keys.but1_press = 0;
    }
    if (s_pixel->event.button.button == SDL_BUTTON_RIGHT)
    {
        s_pixel->is_intersect = 0;
    }
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
        if (s_pixel->arr_object3d[i].type_of_data == 2)
        {
            if ((tmp = ft_intersect_ray_plane(s_pixel->player.position, s_pixel, direction, i)) > 0)
            {
                if (tmp < t && tmp >= 0)
                {
                    t = tmp;
                    s_pixel->is_intersect = 1;
                    k = i;
                }
            }
        }
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

void ft_mouse_move(t_elem *s_pixel)
{
    int i;

    i = s_pixel->figure_now;
    if (i >= 0)
    {
        if (s_pixel->arr_object3d[i].type_of_data == 0)
        {
            ((t_sphere *)s_pixel->arr_object3d[i].data)->center.x += s_pixel->event.motion.xrel;
            ((t_sphere *)s_pixel->arr_object3d[i].data)->center.y -= s_pixel->event.motion.yrel;
        }
        if (s_pixel->arr_object3d[i].type_of_data == 2)
        {
            ((t_plane *)s_pixel->arr_object3d[i].data)->point.y -= s_pixel->event.motion.yrel;
            ((t_plane *)s_pixel->arr_object3d[i].data)->normal.y -= s_pixel->event.motion.yrel;
        }
        if (s_pixel->arr_object3d[i].type_of_data == 1)
        {
            ((t_cylinder *)s_pixel->arr_object3d[i].data)->p1.x += s_pixel->event.motion.xrel;
            ((t_cylinder *)s_pixel->arr_object3d[i].data)->p1.y -= s_pixel->event.motion.yrel;
            ((t_cylinder *)s_pixel->arr_object3d[i].data)->p2.x += s_pixel->event.motion.xrel;
            ((t_cylinder *)s_pixel->arr_object3d[i].data)->p2.y -= s_pixel->event.motion.yrel;
        }
        if (s_pixel->arr_object3d[i].type_of_data == 3)
        {
            ((t_cone *)s_pixel->arr_object3d[i].data)->p1.x += s_pixel->event.motion.xrel;
            ((t_cone *)s_pixel->arr_object3d[i].data)->p1.y -= s_pixel->event.motion.yrel;
            ((t_cone *)s_pixel->arr_object3d[i].data)->p2.x += s_pixel->event.motion.xrel;
            ((t_cone *)s_pixel->arr_object3d[i].data)->p2.y -= s_pixel->event.motion.yrel;
        }
    }
}

void ft_wait_for_input(t_elem *s_pixel)
{
    char *line;
    int res;

    res = get_next_line(0, &line);
    if (res == 1)
    {
        ft_validate_input(line, s_pixel);
        free(line);
    }
}

void ft_change_position(t_elem *s_pixel)
{
    double angle1;
    double angle2;

    angle1 = s_pixel->player.angle_gor / 180 * 3.14;
    angle2 = s_pixel->player.angle_ver / 180 * 3.14;
    if (s_pixel->event.key.keysym.sym == SDLK_q)
        s_pixel->player.position.y += 20;//up
    if (s_pixel->event.key.keysym.sym == SDLK_z)
        s_pixel->player.position.y -= 20;//down
    if (s_pixel->event.key.keysym.sym == SDLK_w) // forward
    {
        s_pixel->player.position.x = s_pixel->player.position.x + 40 * sin(angle1);
        s_pixel->player.position.z = s_pixel->player.position.z + 40 * cos(angle1);
        s_pixel->player.position.y = s_pixel->player.position.y + 40 * sin(angle2);
    }
    if (s_pixel->event.key.keysym.sym == SDLK_s) // back
    {
        s_pixel->player.position.x = s_pixel->player.position.x + -40 * sin(angle1);
        s_pixel->player.position.z = s_pixel->player.position.z + -40 * cos(angle1);
        s_pixel->player.position.y = s_pixel->player.position.y + -40 * sin(angle2);
    }
    if (s_pixel->event.key.keysym.sym == SDLK_a) // left
        s_pixel->player.angle_gor = (s_pixel->player.angle_gor <= 0) ? 360 : s_pixel->player.angle_gor - 1;
    if (s_pixel->event.key.keysym.sym == SDLK_d) // right
        s_pixel->player.angle_gor = (s_pixel->player.angle_gor >= 360) ? 1 : s_pixel->player.angle_gor + 1;
    if (s_pixel->event.key.keysym.sym == SDLK_c)// c
        s_pixel->player.angle_ver = (s_pixel->player.angle_ver <= 0) ? 360 : s_pixel->player.angle_ver - 1;
    if (s_pixel->event.key.keysym.sym == SDLK_e) // e
        s_pixel->player.angle_ver = (s_pixel->player.angle_ver >= 360) ? 1 : s_pixel->player.angle_ver + 1;
}

void ft_change_object(t_elem *s_pixel)
{
    double angle_x = 0;
    double angle_z = 0;
    int i;
    double new_x;
    double new_y;
    double new_z;

    i = s_pixel->figure_now;
    if (i > -1)
    {
        if (s_pixel->event.key.keysym.sym == SDLK_UP || s_pixel->event.key.keysym.sym == SDLK_DOWN)
        {
            if (s_pixel->event.key.keysym.sym == SDLK_UP)
                angle_x = 1.0;
            else
                angle_x = -1.0;
            if (s_pixel->arr_object3d[i].type_of_data == 1)
            {
                new_y = ((t_cylinder *)s_pixel->arr_object3d[i].data)->p2.y * cos(angle_x / 180 * 3.14) + ((t_cylinder *)s_pixel->arr_object3d[i].data)->p2.z * sin(angle_x / 180 * 3.14);
                new_z = -((t_cylinder *)s_pixel->arr_object3d[i].data)->p2.y * sin(angle_x / 180 * 3.14) + ((t_cylinder *)s_pixel->arr_object3d[i].data)->p2.z * cos(angle_x / 180 * 3.14);
                ((t_cylinder *)s_pixel->arr_object3d[i].data)->p2.y = new_y;
                ((t_cylinder *)s_pixel->arr_object3d[i].data)->p2.z = new_z;
            }
            else if (s_pixel->arr_object3d[i].type_of_data == 3)
            {
                new_y = ((t_cone *)s_pixel->arr_object3d[i].data)->p2.y * cos(angle_x / 180 * 3.14) + ((t_cone *)s_pixel->arr_object3d[i].data)->p2.z * sin(angle_x / 180 * 3.14);
                new_z = -((t_cone *)s_pixel->arr_object3d[i].data)->p2.y * sin(angle_x / 180 * 3.14) + ((t_cone *)s_pixel->arr_object3d[i].data)->p2.z * cos(angle_x / 180 * 3.14);
                ((t_cone *)s_pixel->arr_object3d[i].data)->p2.y = new_y;
                ((t_cone *)s_pixel->arr_object3d[i].data)->p2.z = new_z;
            }
            else if (s_pixel->arr_object3d[i].type_of_data == 2)
            {
                new_y = ((t_plane *)s_pixel->arr_object3d[i].data)->normal.y * cos(angle_x / 180 * 3.14) + ((t_plane *)s_pixel->arr_object3d[i].data)->normal.z * sin(angle_x / 180 * 3.14);
                new_z = -((t_plane *)s_pixel->arr_object3d[i].data)->normal.y * sin(angle_x / 180 * 3.14) + ((t_plane *)s_pixel->arr_object3d[i].data)->normal.z * cos(angle_x / 180 * 3.14);
                ((t_plane *)s_pixel->arr_object3d[i].data)->normal.y = new_y;
                ((t_plane *)s_pixel->arr_object3d[i].data)->normal.z = new_z;
            }
        }
        else if (s_pixel->event.key.keysym.sym == SDLK_LEFT || s_pixel->event.key.keysym.sym == SDLK_RIGHT)
        {
            if (s_pixel->event.key.keysym.sym == SDLK_LEFT)
                angle_z = 1.0;
            else
                angle_z = -1.0;
            if (s_pixel->arr_object3d[i].type_of_data == 1)
            {
                new_x = ((t_cylinder *)s_pixel->arr_object3d[i].data)->p2.x * cos(angle_z / 180 * 3.14) + ((t_cylinder *)s_pixel->arr_object3d[i].data)->p2.y * sin(angle_z / 180 * 3.14);
                new_y = -((t_cylinder *)s_pixel->arr_object3d[i].data)->p2.x * sin(angle_z / 180 * 3.14) + ((t_cylinder *)s_pixel->arr_object3d[i].data)->p2.y * cos(angle_z / 180 * 3.14);
                ((t_cylinder *)s_pixel->arr_object3d[i].data)->p2.x = new_x;
                ((t_cylinder *)s_pixel->arr_object3d[i].data)->p2.y = new_y;
            
            }
            if (s_pixel->arr_object3d[i].type_of_data == 3)
            {
                new_x = ((t_cone *)s_pixel->arr_object3d[i].data)->p2.x * cos(angle_z / 180 * 3.14) + ((t_cone *)s_pixel->arr_object3d[i].data)->p2.y * sin(angle_z / 180 * 3.14);
                new_y = -((t_cone *)s_pixel->arr_object3d[i].data)->p2.x * sin(angle_z / 180 * 3.14) + ((t_cone *)s_pixel->arr_object3d[i].data)->p2.y * cos(angle_z / 180 * 3.14);
                ((t_cone *)s_pixel->arr_object3d[i].data)->p2.x = new_x;
                ((t_cone *)s_pixel->arr_object3d[i].data)->p2.y = new_y;
            }
            if (s_pixel->arr_object3d[i].type_of_data == 2)
            {
                new_x = ((t_plane *)s_pixel->arr_object3d[i].data)->normal.x * cos(angle_z / 180 * 3.14) + ((t_plane *)s_pixel->arr_object3d[i].data)->normal.y * sin(angle_z / 180 * 3.14);
                new_y = -((t_plane *)s_pixel->arr_object3d[i].data)->normal.x * sin(angle_z / 180 * 3.14) + ((t_plane *)s_pixel->arr_object3d[i].data)->normal.y * cos(angle_z / 180 * 3.14);
                ((t_plane *)s_pixel->arr_object3d[i].data)->normal.x = new_x;
                ((t_plane *)s_pixel->arr_object3d[i].data)->normal.y = new_y;
            
            }
        }
    }
}

void ft_change_light(t_elem *s_pixel)
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

void ft_change_specular(t_elem *s_pixel)
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

void ft_change_reflective(t_elem *s_pixel)
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

void ft_change_obj_size(t_elem *s_pixel)
{
    int i;

    i = s_pixel->figure_now;
    if (i > -1)
    {
        if (s_pixel->arr_object3d[i].type_of_data == 0)
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
        else if (s_pixel->arr_object3d[i].type_of_data == 1)
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
        else if (s_pixel->arr_object3d[i].type_of_data == 3)
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
    }
}

void	ft_check_key(t_elem *s_pixel)
{
	if (s_pixel->event.key.keysym.sym == SDLK_ESCAPE)
		exit_program(s_pixel);
    else if (s_pixel->event.key.keysym.sym == SDLK_BACKSPACE)
        ft_wait_for_input(s_pixel);
    else if (s_pixel->event.key.keysym.sym == SDLK_DOWN || s_pixel->event.key.keysym.sym == SDLK_UP || s_pixel->event.key.keysym.sym == SDLK_LEFT || s_pixel->event.key.keysym.sym == SDLK_RIGHT)
        ft_change_object(s_pixel);
    else if (s_pixel->event.key.keysym.sym == SDLK_1 || s_pixel->event.key.keysym.sym == SDLK_2)
        ft_change_light(s_pixel);
    else if (s_pixel->event.key.keysym.sym == SDLK_3 || s_pixel->event.key.keysym.sym == SDLK_4)
        ft_change_specular(s_pixel);
    else if (s_pixel->event.key.keysym.sym == SDLK_5 || s_pixel->event.key.keysym.sym == SDLK_6)
        ft_change_reflective(s_pixel);
    else if (s_pixel->event.key.keysym.sym == SDLK_KP_PLUS || s_pixel->event.key.keysym.sym == SDLK_KP_MINUS)
        ft_change_obj_size(s_pixel);
    else
        ft_change_position(s_pixel);
}

void    ft_draw_pixel(t_elem *s_pixel, int x, int y, int color)
{
	int index;

    SDL_LockSurface(s_pixel->surface);
    index = s_pixel->surface->pitch * y + x * s_pixel->surface->format->BytesPerPixel; // x * 4
	*(unsigned *)(s_pixel->surface->pixels + index) = color;
    SDL_UnlockSurface(s_pixel->surface);
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
    double result;

    x = position - ((t_plane *)s_pixel->arr_object3d[i].data)->point;
    normal = ft_normalize_vector(((t_plane *)s_pixel->arr_object3d[i].data)->normal - ((t_plane *)s_pixel->arr_object3d[i].data)->point);
    
    k1 = ft_dot_product(-x, normal);
    k2 = ft_dot_product(direction, normal);
    
    if (k2 == 0)
        return (-1);
    result = k1 / k2;
    if ((ft_dot_product(direction, normal) * ft_dot_product(x, normal)) > 0)
        return (-1);
    return (result);
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
    x = position - ((t_cone *)s_pixel->arr_object3d[i].data)->p1;

    k = tan(((t_cone *)s_pixel->arr_object3d[i].data)->angle / 2.0 / 180.0 * 3.14);
    
    a = ft_dot_product(direction, direction) - (1.0 + k * k) * pow(ft_dot_product(direction, v), 2);
    b = ft_dot_product(direction, x) - (1.0 + k * k) * ft_dot_product(direction, v) * ft_dot_product(x, v);
    b = b * 2.0;
    c = ft_dot_product(x, x) - (1.0 + k * k) * pow(ft_dot_product(x, v), 2);

    discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return (-1);
    t1 = (-b + sqrt(discriminant)) / (2 * a);
    t2 = (-b - sqrt(discriminant)) / (2 * a);
   
    m1 = ft_dot_product((position + direction * t1) - ((t_cone *)s_pixel->arr_object3d[i].data)->p1, v);
    m2 = ft_dot_product((position + direction * t2) - ((t_cone *)s_pixel->arr_object3d[i].data)->p1, v);
    if (t1 >= 0 && t2 >= 0)
    {
        if (t1 < t2)
            if (0 <= m1 && m1 <= ((t_cone *)s_pixel->arr_object3d[i].data)->height)
                return (t1);
        if (0 <= m2 && m2 <= ((t_cone *)s_pixel->arr_object3d[i].data)->height)
            return (t2);
    }
    else
    {
        if (t1 >= 0 && t2 < 0)
            if (0 <= m1 && m1 <= ((t_cone *)s_pixel->arr_object3d[i].data)->height)
                return (t1);
        if (0 <= m2 && m2 <= ((t_cone *)s_pixel->arr_object3d[i].data)->height)
            return (t2);
    }
    return (-1);
}

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
                normal = ft_normalize_vector( (position + direction * t) - ((t_cylinder *)s_pixel->arr_object3d[i].data)->p1 - (vec * m) );//////////////
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
                t = tmp;
                normal = (position + direction * t) + ( ((t_plane *)s_pixel->arr_object3d[i].data)->normal - ((t_plane *)s_pixel->arr_object3d[i].data)->point);
                /*if (ft_dot_product(direction, ((t_plane *)s_pixel->arr_object3d[i].data)->normal) < 0)
                    normal *= -1;*/
                s_pixel->normal_now = ft_normalize_vector(normal);
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
    if (s_pixel->is_intersect == 0)
        return (local_color);
    //////not reflective or depth <= 0 ====>exit
    local_color = ft_lighting(local_color, t, s_pixel, direction);
    if (depth < 0 || reflect < 0.0)
        return (local_color);
    /// reflect color
    if (s_pixel->is_reflect == 0)
        return (local_color);
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

int ft_lighting(int color, int t, t_elem *s_pixel, t_vector direction)
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
                ray_light = s_pixel->arr_light[i].position - (s_pixel->player.position + direction * t);
            else
                ray_light = s_pixel->arr_light[i].position;
            //////shadow
            if (s_pixel->is_shadow == 1)
                if (ft_is_shadow(s_pixel, t, direction, i) == 1)
                    continue ;
            /////////Diffuse
            n_dot_l = ft_dot_product(normal, ray_light);
            if (n_dot_l >= 0)//> 0
                k += s_pixel->arr_light[i].intensity * n_dot_l / ft_vector_len(ray_light);
            //specular
            if (s_pixel->arr_object3d[s_pixel->obj_now].specular > 0 && s_pixel->is_specular == 1)
            {
                r = 2.0 * normal * ft_dot_product(normal, ray_light) - ray_light;
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

void *ft_draw_display(void *data)
{
    t_elem *s_pixel = (t_elem *)data;
    t_vector direction;
    int color;
    int x;
    int y;

    if (s_pixel->i == THREADS)
        s_pixel->i = 0;
    s_pixel->t_max = DBL_MAX;
    s_pixel->t_min = 0;
    x = ((WIDTH / THREADS) * s_pixel->i) - 1;
    int x1 = ((WIDTH / THREADS) * (++s_pixel->i));
    while (++x < x1)
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
                ft_draw_pixel(s_pixel, x, y, color);
                s_pixel->is_intersect = 0;
            }
            else
                ft_draw_pixel(s_pixel, x, y, 0x000000);   
        }
    }
    s_pixel->player.rotate_left = 0;
    s_pixel->player.rotate_right = 0;
    return (0);
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

void ft_validate_input(char *line, t_elem *s_pixel)
{
    static int i = 0;
    static int k = 0;
    t_sphere *s_sphere;
    t_plane *plane;
    t_cone *cone;
    t_cylinder *cylinder;

    if (s_pixel->nbr_of_obj > 98)
        write(1, "A lot of objects\n", 17);
    else if (ft_strcmp(line, "add sphere") == 0)
    {
        s_sphere = (t_sphere *)malloc(sizeof(t_sphere));
        s_sphere->center.x = s_pixel->player.position.x + 200;
        s_sphere->center.y = s_pixel->player.position.y;
        s_sphere->center.z = s_pixel->player.position.z + 1000;
        s_sphere->radius = 100.0;
        s_pixel->arr_object3d[i].reflective = 0.0;////////////////////////////
        s_pixel->arr_object3d[i].specular = 100;
        s_pixel->arr_object3d[i].color = 0x999900;
        s_pixel->arr_object3d[i].type_of_data = 0;
        s_pixel->arr_object3d[i].data = (t_sphere *)s_sphere;
        s_pixel->nbr_of_obj++;
        i++;
    }
    else if (ft_strcmp(line, "add cylinder") == 0)
    {
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
        i++;
    }
    else if (ft_strcmp(line, "add plane") == 0)
    {
        plane = (t_plane *)malloc(sizeof(t_plane));
        plane->point.x = s_pixel->player.position.x;
        plane->point.y = s_pixel->player.position.y - 300; 
        plane->point.z = s_pixel->player.position.z + 1000;
        plane->normal.x = s_pixel->player.position.x;
        plane->normal.y = s_pixel->player.position.y - 299;
        plane->normal.z = s_pixel->player.position.x + 1000;
        s_pixel->arr_object3d[i].reflective = 0;
        s_pixel->arr_object3d[i].specular = -1; // 200
        s_pixel->arr_object3d[i].color = 0x999999;
        s_pixel->arr_object3d[i].type_of_data = 2;
        s_pixel->arr_object3d[i].data = (t_plane *)plane;
        s_pixel->nbr_of_obj++;
        i++;
    }
    else if (ft_strcmp(line, "add cone") == 0)
    {
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
        i++;
    }
    else if (ft_strcmp(line, "add ambient light") == 0)
    {
        if (k > 8)
            write(1, "Light max!\n", 11);
        s_pixel->arr_light[k].type_of_light = 0;
        s_pixel->arr_light[k].intensity = 0.3;
        s_pixel->nbr_of_light++;
        k++;
    }
    else if (ft_strcmp(line, "add point light") == 0)
    {
        if (k > 8)
            write(1, "Light max!\n", 11);
        s_pixel->arr_light[k].type_of_light = 1;
        s_pixel->arr_light[k].intensity = 1.0;
        s_pixel->arr_light[k].position.x = s_pixel->player.position.x;
        s_pixel->arr_light[k].position.y = s_pixel->player.position.y;
        s_pixel->arr_light[k].position.z = s_pixel->player.position.z + 1000;
        s_pixel->nbr_of_light++;
        k++;
    }
    else if (ft_strcmp(line, "add directional light") == 0)
    {
        if (k > 8)
            write(1, "Light max!\n", 11);
        s_pixel->arr_light[k].type_of_light = 2;
        s_pixel->arr_light[k].intensity = 1.0;
        s_pixel->arr_light[k].position.x = 50000;
        s_pixel->arr_light[k].position.y = 50000;
        s_pixel->arr_light[k].position.z = 50000;
        s_pixel->nbr_of_light++;
        k++;
    }
    else if (ft_strcmp(line, "add shadow") == 0)
        s_pixel->is_shadow = 1;
    else if (ft_strcmp(line, "delete shadow") == 0)
        s_pixel->is_shadow = 0;
    else if (ft_strcmp(line, "add reflect") == 0)
        s_pixel->is_reflect = 1;
    else if (ft_strcmp(line, "delete reflect") == 0)
        s_pixel->is_reflect = 0;
    else if (ft_strcmp(line, "add specular") == 0)
        s_pixel->is_specular = 1;
    else if (ft_strcmp(line, "delete specular") == 0)
        s_pixel->is_specular = 0;    
    ft_validate_light(s_pixel, -1, -1);
}

void ft_validate_light(t_elem *s_pixel, int i, int k)
{
    while (++i < s_pixel->nbr_of_obj)
    {
        if (s_pixel->arr_object3d[i].type_of_data == 3)
        {
            while (++k < s_pixel->nbr_of_light)
            {
                if (s_pixel->arr_light[k].type_of_light == 1)
                {
                    if (ft_check_if_equal(s_pixel->arr_light[k].position, ((t_cone *)s_pixel->arr_object3d[i].data)->p1) == 0)
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

int ft_check_if_equal(t_vector vec1, t_vector vec2)
{
    if (vec1.x == vec2.x)
        if (vec1.y == vec2.y)
            if (vec1.z == vec2.z)
                return (0);
    return (1);
}

void ft_image_on_screen(t_elem *s_pixel)
{
    SDL_Rect        sourceRectangle;
    SDL_Rect        destinationRectangle;
    SDL_Texture     *texture;

    texture = SDL_CreateTextureFromSurface(s_pixel->renderrer, s_pixel->surface);
    SDL_QueryTexture(texture, NULL, NULL, &sourceRectangle.w, &sourceRectangle.h);
    sourceRectangle.x = 0;
    sourceRectangle.y = 0;
    destinationRectangle.x = 0;
    destinationRectangle.y = 0;
    destinationRectangle.w = sourceRectangle.w;
    destinationRectangle.h = sourceRectangle.h;
    SDL_RenderClear(s_pixel->renderrer);
    SDL_RenderCopy(s_pixel->renderrer, texture, &sourceRectangle, &destinationRectangle);
    SDL_RenderPresent(s_pixel->renderrer);
    SDL_DestroyTexture(texture);
}

void ft_main_draw(t_elem *s_pixel)
{
    int i;
    pthread_t thread[THREADS];

    i = -1;
    while (++i < THREADS)
        pthread_create(&thread[i], NULL, ft_draw_display, (void*)s_pixel);
    while (1)
    {
        if (SDL_PollEvent(&s_pixel->event))
        {
            if (s_pixel->event.type == SDL_QUIT)
                exit_program(s_pixel);
            else if (s_pixel->event.type == SDL_KEYUP)
                ft_check_key(s_pixel);
            else if (s_pixel->event.type == SDL_MOUSEBUTTONUP)
                ft_mouse_press(s_pixel);
            else if (s_pixel->event.type == SDL_MOUSEBUTTONDOWN)
                ft_mouse_release(s_pixel);
            else if (s_pixel->event.type == SDL_MOUSEMOTION)
                ft_mouse_move(s_pixel);
            else if (s_pixel->event.type == SDL_MOUSEWHEEL)
                ft_mouse_wheel(s_pixel);
        }
        else
        {
            ft_draw_display(s_pixel);
            ft_image_on_screen(s_pixel);
        }
    }
    i = -1;
    while (++i < THREADS)
        pthread_join(thread[i], NULL);
}

void ft_prepare_programm(t_elem *s_pixel)
{
    s_pixel->window = 0;
    s_pixel->renderrer = 0;
    if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
    {
        s_pixel->window = SDL_CreateWindow("RTv1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
        if (s_pixel->window == 0)
        {
            SDL_Quit();
            exit(1);
        }
        s_pixel->renderrer = SDL_CreateRenderer(s_pixel->window, -1, SDL_RENDERER_ACCELERATED);
        if (s_pixel->renderrer == 0)
        {
            SDL_DestroyWindow(s_pixel->window);
            SDL_Quit();
            exit(1);
        }
        s_pixel->surface = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0, 0, 0, 0);
        s_pixel->player.position = (t_vector){0, 0, 0};
        s_pixel->is_intersect = 0;
        s_pixel->i = 0;
        s_pixel->is_shadow = 1;/////0
        s_pixel->is_reflect = 1;/////0
        s_pixel->is_specular = 1;/////0
        s_pixel->depth_recursive = 3;
        s_pixel->player.angle_gor = 0;
        s_pixel->player.angle_ver = 0;
        s_pixel->player.pov = (t_vector){0, 0, 1};
        s_pixel->nbr_of_obj = 0;
        s_pixel->nbr_of_light = 0;
        s_pixel->figure_now = -1;
        s_pixel->player.rotate_right = 0;
        s_pixel->player.rotate_left = 0;
        ft_validate_input("add plane", s_pixel);
        ft_validate_input("add point light", s_pixel);
        //ft_validate_input("add directional light", s_pixel);
        //ft_validate_input("add cone", s_pixel);
        ft_validate_input("add sphere", s_pixel);
        //ft_validate_input("add cylinder", s_pixel);
    }
    else
        exit(1);
}

int main(void)
{
	t_elem          *s_pixel;

	if (!(s_pixel = (t_elem *)malloc(sizeof(t_elem))))
		exit(0);
    ft_prepare_programm(s_pixel);
    ft_main_draw(s_pixel);
	return (0);
}