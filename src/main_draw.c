/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 14:38:01 by arudyi            #+#    #+#             */
/*   Updated: 2019/05/01 14:05:21 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

void	ft_check_event(t_elem *s_pixel)
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
		ft_mouse_move(s_pixel, s_pixel->figure_now);
	else if (s_pixel->event.type == SDL_MOUSEWHEEL)
		ft_mouse_wheel(s_pixel, s_pixel->figure_now);
}

void	ft_main_draw(t_elem *s_pixel, int i)
{
	pthread_t thread[THREADS];

	while (++i < THREADS)
		pthread_create(&thread[i], NULL, ft_draw_display, (void*)s_pixel);
	while (1)
	{
		if (SDL_PollEvent(&s_pixel->event))
			ft_check_event(s_pixel);
		else
		{
			i = -1;
			while (++i < THREADS)
				pthread_join(thread[i], NULL);
			ft_draw_display(s_pixel);
			ft_image_on_screen(s_pixel);
		}
	}
}

void	ft_draw_display1(t_elem *s_pixel, int x, int x1)
{
	t_vector	direction;
	int			color;
	int			y;

	while (++x < x1)
	{
		y = -1;
		while (++y < HEIGHT)
		{
			direction = ft_canvas_to_viewport(x, y);
			direction = ft_rotate_camera(direction, s_pixel);
			color = ft_trace_ray(PLA_POS, s_pixel, direction,
			RECURSIVE);
			if (IS_INTERSECT == 1)
			{
				s_pixel->t_max = DBL_MAX;
				s_pixel->t_min = 0;
				ft_draw_pixel(s_pixel, x, y, color);
				IS_INTERSECT = 0;
			}
			else
				ft_draw_pixel(s_pixel, x, y, 0x000000);
		}
	}
}

void	*ft_draw_display(void *data)
{
	t_elem		*s_pixel;
	int			x;
	int			x1;
	static int	i = 0;

	s_pixel = (t_elem *)malloc(sizeof(t_elem));
	*s_pixel = *((t_elem *)data);
	if (i == THREADS)
		i = 0;
	s_pixel->t_max = DBL_MAX;
	s_pixel->t_min = 0;
	x = ((WIDTH / THREADS) * i) - 1;
	x1 = ((WIDTH / THREADS) * (++i));
	ft_draw_display1(s_pixel, x, x1);
	s_pixel->player.rotate_left = 0;
	s_pixel->player.rotate_right = 0;
	free(s_pixel);
	return (0);
}
