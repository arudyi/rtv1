/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 14:18:48 by arudyi            #+#    #+#             */
/*   Updated: 2019/04/30 13:22:57 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

void	ft_check_key(t_elem *s_pixel)
{
	int key;

	key = s_pixel->event.key.keysym.sym;
	if (ESC)
		exit_program(s_pixel);
	else if (BACKSPACE)
		ft_wait_for_input(s_pixel);
	else if (ARROW_UP || ARROW_LEFT)
		ft_change_object(s_pixel, 0.0, 0.0, -1);
	else if (LIGHT)
		ft_change_light(s_pixel);
	else if (SPECULAR)
		ft_change_specular(s_pixel);
	else if (REFLECT)
		ft_change_reflective(s_pixel);
	else if (SIZE)
		ft_change_obj_size(s_pixel);
	else
		ft_change_position(s_pixel, 0.0, 0.0);
}

void	ft_wait_for_input(t_elem *s_pixel)
{
	char	*line;
	int		res;

	res = get_next_line(0, &line);
	if (res >= 1)
	{
		ft_validate_input(line, s_pixel);
		free(line);
	}
}

void	ft_change_position1(t_elem *s_pixel)
{
	if (s_pixel->event.key.keysym.sym == SDLK_a)
		s_pixel->player.angle_gor = (s_pixel->player.angle_gor <= 0) ? 360 :
		s_pixel->player.angle_gor - 1;
	else if (s_pixel->event.key.keysym.sym == SDLK_d)
		s_pixel->player.angle_gor = (s_pixel->player.angle_gor >= 360) ? 1 :
		s_pixel->player.angle_gor + 1;
	else if (s_pixel->event.key.keysym.sym == SDLK_c)
		s_pixel->player.angle_ver = (s_pixel->player.angle_ver <= 0) ? 360 :
		s_pixel->player.angle_ver - 1;
	else if (s_pixel->event.key.keysym.sym == SDLK_e)
		s_pixel->player.angle_ver = (s_pixel->player.angle_ver >= 360) ? 1 :
		s_pixel->player.angle_ver + 1;
}

void	ft_change_position(t_elem *s_pixel, double a1, double a2)
{
	a1 = s_pixel->player.angle_gor / 180 * 3.14;
	a2 = s_pixel->player.angle_ver / 180 * 3.14;
	if (s_pixel->event.key.keysym.sym == SDLK_q)
		s_pixel->player.position.y += 20;
	else if (s_pixel->event.key.keysym.sym == SDLK_z)
		s_pixel->player.position.y -= 20;
	else if (s_pixel->event.key.keysym.sym == SDLK_w)
	{
		s_pixel->player.position.x = s_pixel->player.position.x + 40 * sin(a1);
		s_pixel->player.position.z = s_pixel->player.position.z + 40 * cos(a1);
		s_pixel->player.position.y = s_pixel->player.position.y + 40 * sin(a2);
	}
	else if (s_pixel->event.key.keysym.sym == SDLK_s)
	{
		s_pixel->player.position.x = s_pixel->player.position.x + -40 * sin(a1);
		s_pixel->player.position.z = s_pixel->player.position.z + -40 * cos(a1);
		s_pixel->player.position.y = s_pixel->player.position.y + -40 * sin(a2);
	}
	ft_change_position1(s_pixel);
}
