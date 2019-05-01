/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 16:50:13 by arudyi            #+#    #+#             */
/*   Updated: 2019/05/01 13:46:49 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

void	ft_prepare_programm1(t_elem *s_pixel)
{
	s_pixel->surface = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0, 0, 0, 0);
	s_pixel->player.position = (t_vector){0, 0, 0};
	s_pixel->is_intersect = 0;
	s_pixel->i = 0;
	s_pixel->player.i = 0;
	s_pixel->player.k = 0;
	s_pixel->depth_recursive = 3;
	s_pixel->player.angle_gor = 0;
	s_pixel->player.angle_ver = 0;
	s_pixel->player.pov = (t_vector){0, 0, 1};
	s_pixel->nbr_of_obj = 0;
	s_pixel->nbr_of_light = 0;
	s_pixel->figure_now = -1;
	s_pixel->player.rotate_right = 0;
	s_pixel->player.rotate_left = 0;
	ft_validate_input("add cone", s_pixel);
	ft_validate_input("add cylinder", s_pixel);
	ft_validate_input("add sphere", s_pixel);
	ft_validate_input("add plane", s_pixel);
	ft_validate_input("add point light", s_pixel);
	ft_validate_input("add directional light", s_pixel);
}

void	ft_prepare_programm(t_elem *s_pixel)
{
	s_pixel->window = 0;
	s_pixel->renderrer = 0;
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		s_pixel->window = SDL_CreateWindow("RTv1", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
		if (s_pixel->window == 0)
		{
			SDL_Quit();
			exit(1);
		}
		s_pixel->renderrer = SDL_CreateRenderer(s_pixel->window, -1,
		SDL_RENDERER_ACCELERATED);
		if (s_pixel->renderrer == 0)
		{
			SDL_DestroyWindow(s_pixel->window);
			SDL_Quit();
			exit(1);
		}
		ft_prepare_programm1(s_pixel);
	}
	else
		exit(1);
}

int		main(void)
{
	t_elem	*s_pixel;

	if (!(s_pixel = (t_elem *)malloc(sizeof(t_elem))))
		exit(0);
	ft_prepare_programm(s_pixel);
	ft_main_draw(s_pixel, -1);
	return (0);
}
