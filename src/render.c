/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 14:18:26 by arudyi            #+#    #+#             */
/*   Updated: 2019/04/30 19:46:17 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

void ft_sphere(t_elem *s_pixel, t_vector position, t_vector direction, t_trace *trace)
{
	double tmp;

	tmp = ft_intersect_ray_sphere(position, s_pixel, direction, trace->i);
	if (tmp < trace->t && tmp >= s_pixel->t_min)
	{
		trace->t = tmp;
		trace->normal = ft_normalize_vector((position + direction * trace->t) - ((t_sphere *)s_pixel->arr_object3d[trace->i].data)->center);
		s_pixel->normal_now = trace->normal;
		s_pixel->is_intersect = 1;
		trace->local_color = s_pixel->arr_object3d[trace->i].color;
		trace->reflect = s_pixel->arr_object3d[trace->i].reflective;
		s_pixel->obj_now = trace->i;	
	}
}

void ft_cylinder(t_elem *s_pixel, t_vector position, t_vector direction, t_trace *trace)
{
	double tmp;
	double m;
	t_vector vec;

	tmp = ft_intersect_ray_cylinder(position, s_pixel, direction, trace->i);
	if (tmp < trace->t && tmp >= s_pixel->t_min)
	{
		trace->t = tmp;
		vec = ft_normalize_vector(((t_cylinder *)s_pixel->arr_object3d[trace->i].data)->p2 - ((t_cylinder *)s_pixel->arr_object3d[trace->i].data)->p1);
		m = ft_dot_product((position + direction * trace->t) - ((t_cylinder *)s_pixel->arr_object3d[trace->i].data)->p1, vec);
		trace->normal = ft_normalize_vector( (position + direction * trace->t) - ((t_cylinder *)s_pixel->arr_object3d[trace->i].data)->p1 - (vec * m) );//////////////
		s_pixel->normal_now = trace->normal;
		s_pixel->is_intersect = 1;
		trace->local_color = s_pixel->arr_object3d[trace->i].color;
		trace->reflect = s_pixel->arr_object3d[trace->i].reflective;
		s_pixel->obj_now = trace->i;
	}
}

void ft_plane(t_elem *s_pixel, t_vector position, t_vector direction, t_trace *trace)
{
	double tmp;

	tmp = ft_intersect_ray_plane(position, s_pixel, direction, trace->i);
	if (tmp < trace->t && tmp >= s_pixel->t_min)
	{
		trace->t = tmp;
		trace->normal = (position + direction * trace->t) + (((t_plane *)s_pixel->arr_object3d[trace->i].data)->normal - ((t_plane *)s_pixel->arr_object3d[trace->i].data)->point);
		s_pixel->normal_now = ft_normalize_vector(trace->normal);
		s_pixel->is_intersect = 1;
		trace->local_color = s_pixel->arr_object3d[trace->i].color;
		trace->reflect = s_pixel->arr_object3d[trace->i].reflective;
		s_pixel->obj_now = trace->i;
	}
}

void ft_cone(t_elem *s_pixel, t_vector position, t_vector direction, t_trace *trace)
{
	double tmp;
	double m;
	t_vector vec1;
	t_vector vec2;

	tmp = ft_intersect_ray_cone(position, s_pixel, direction, trace->i);
	if (tmp < trace->t && tmp >= s_pixel->t_min)
	{
		trace->t = tmp;
		vec1 = (position + (direction * trace->t)) - ((t_cone *)s_pixel->arr_object3d[trace->i].data)->p1;
		vec2 = ft_normalize_vector(((t_cone *)s_pixel->arr_object3d[trace->i].data)->p2 - ((t_cone *)s_pixel->arr_object3d[trace->i].data)->p1);
		m = ft_vector_len(vec1) / cos(((t_cone *)s_pixel->arr_object3d[trace->i].data)->angle / 2.0 / 180.0 * 3.14);
		trace->normal = ft_normalize_vector(vec1 - (vec2 * m));
		s_pixel->is_intersect = 1;
		s_pixel->normal_now = trace->normal;
		trace->local_color = s_pixel->arr_object3d[trace->i].color;
		trace->reflect = s_pixel->arr_object3d[trace->i].reflective;
		s_pixel->obj_now = trace->i;
	}
}

void ft_get_trace(t_elem *s_pixel, t_trace *trace)
{
	trace->local_color = 0x000000;
	trace->t = s_pixel->t_max;
}

void ft_get_t_min_max(t_elem *s_pixel)
{
	s_pixel->t_max = DBL_MAX;
	s_pixel->t_min = 0.00001;
}

int		ft_trace_ray(t_vector position, t_elem *s_pixel, t_vector direction, int depth)
{/**//**//**//**//**//**/
	double		reflect_color1;
	t_trace		trace;
	int			i;
	t_vector	r;

	i = -1;
	ft_get_trace(s_pixel, &trace);
	while (++i < s_pixel->nbr_of_obj)
	{
		trace.i = i;
		if (s_pixel->arr_object3d[i].type_of_data == 0)
			ft_sphere(s_pixel, position, direction, &trace);
		else if (s_pixel->arr_object3d[i].type_of_data == 1)
			ft_cylinder(s_pixel, position, direction, &trace);
		else if (s_pixel->arr_object3d[i].type_of_data == 2)
			ft_plane(s_pixel, position, direction, &trace);
		else if (s_pixel->arr_object3d[i].type_of_data == 3)
			ft_cone(s_pixel, position, direction, &trace);
	}
	if (s_pixel->is_intersect == 0)
		return (trace.local_color);
	trace.local_color = ft_lighting(trace.local_color, trace.t, s_pixel, direction);
	if (depth < 0 || trace.reflect < 0.0)
		return (trace.local_color);
	r = ft_reflect_ray(-direction, trace.normal);
	ft_get_t_min_max(s_pixel);
	reflect_color1 = ft_trace_ray(position + direction * trace.t, s_pixel, r, depth - 1);    
	return (ft_add_color(ft_change_color(trace.local_color, (1.0 - trace.reflect)), ft_change_color(reflect_color1, trace.reflect), 0, 0));
}
