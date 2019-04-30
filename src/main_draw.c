/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 14:38:01 by arudyi            #+#    #+#             */
/*   Updated: 2019/04/30 17:17:53 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

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
                ft_mouse_move(s_pixel, s_pixel->figure_now);
            else if (s_pixel->event.type == SDL_MOUSEWHEEL)
                ft_mouse_wheel(s_pixel, s_pixel->figure_now);
        }
        else
        {
			i = -1;
			while (++i < THREADS)
        		pthread_join(thread[i], NULL);//
			ft_draw_display(s_pixel);
            ft_image_on_screen(s_pixel);
        }
    }
}

void *ft_draw_display(void *data)
{
    t_elem *s_pixel;    
	t_vector direction;
    int color;
    int x;
    int y;
	static int i = 0;

	s_pixel = (t_elem *)malloc(sizeof(t_elem));
	*s_pixel = *((t_elem *)data);
	if (i == THREADS)
        i = 0;
	s_pixel->t_max = DBL_MAX;
    s_pixel->t_min = 0;
    x = ((WIDTH / THREADS) * i) - 1;
    int x1 = ((WIDTH / THREADS) * (++i));
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
	free(s_pixel);
	return (0);
}