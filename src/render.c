/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 14:18:26 by arudyi            #+#    #+#             */
/*   Updated: 2019/04/29 21:48:35 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

int		ft_trace_ray(t_vector position, t_elem *s_pixel, t_vector direction, int depth)
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
    t_vector r = ft_reflect_ray(-direction, normal);
    s_pixel->t_max = DBL_MAX;
    s_pixel->t_min = 0.00001;//DBL_MIN;
    double reflect_color1 = ft_trace_ray(position + direction * t, s_pixel, r, depth - 1);    
    return (ft_add_color(ft_change_color(local_color, (1.0 - reflect)), ft_change_color(reflect_color1, reflect), 0, 0));
}

void	ft_draw_pixel(t_elem *s_pixel, int x, int y, int color)
{
	int index;

	SDL_LockSurface(s_pixel->surface);
	index = s_pixel->surface->pitch * y + x * s_pixel->surface->format->BytesPerPixel;
	*(unsigned *)(s_pixel->surface->pixels + index) = color;
	SDL_UnlockSurface(s_pixel->surface);
}

void	ft_image_on_screen(t_elem *s_pixel)
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
