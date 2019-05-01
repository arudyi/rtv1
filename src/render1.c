/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 17:03:57 by arudyi            #+#    #+#             */
/*   Updated: 2019/05/01 12:45:03 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

void	ft_draw_pixel(t_elem *s_pixel, int x, int y, int color)
{
	int index;

	SDL_LockSurface(s_pixel->surface);
	index = s_pixel->surface->pitch * y + x * BYTE;
	*(unsigned *)(s_pixel->surface->pixels + index) = color;
	SDL_UnlockSurface(s_pixel->surface);
}

void	ft_image_on_screen(t_elem *s_pixel)
{
	SDL_Rect		sourcerectangle;
	SDL_Rect		destinationrectangle;
	SDL_Texture		*texture;

	texture = SDL_CreateTextureFromSurface(s_pixel->renderrer,
	s_pixel->surface);
	SDL_QueryTexture(texture, NULL, NULL, &sourcerectangle.w,
	&sourcerectangle.h);
	sourcerectangle.x = 0;
	sourcerectangle.y = 0;
	destinationrectangle.x = 0;
	destinationrectangle.y = 0;
	destinationrectangle.w = sourcerectangle.w;
	destinationrectangle.h = sourcerectangle.h;
	SDL_RenderClear(s_pixel->renderrer);
	SDL_RenderCopy(s_pixel->renderrer, texture, &sourcerectangle,
	&destinationrectangle);
	SDL_RenderPresent(s_pixel->renderrer);
	SDL_DestroyTexture(texture);
}

void	ft_get_trace(t_elem *s_pixel, t_trace *trace)
{
	trace->local_color = 0x000000;
	trace->t = s_pixel->t_max;
}

void	ft_get_t_min_max(t_elem *s_pixel)
{
	s_pixel->t_max = DBL_MAX;
	s_pixel->t_min = 0.00001;
}

int		ft_trace_ray1(t_elem *s_pixel, int depth, t_trace *trace,
t_vector position)
{
	t_vector	r;
	double		reflect_color1;

	r = ft_reflect_ray(-trace->direction, trace->normal);
	ft_get_t_min_max(s_pixel);
	reflect_color1 = ft_trace_ray(position + trace->direction * trace->t,
	s_pixel, r, depth - 1);
	return (ft_add_color(ft_change_color(trace->local_color, (1.0 - trace->
	reflect)), ft_change_color(reflect_color1, trace->reflect), 0, 0));
}
