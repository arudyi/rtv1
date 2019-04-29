/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_input1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 20:47:27 by arudyi            #+#    #+#             */
/*   Updated: 2019/04/29 20:47:35 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

void	ft_mouse_press(t_elem *s_pixel)
{
	if (s_pixel->event.button.button == SDL_BUTTON_LEFT)
	{
		s_pixel->figure_now = ft_get_object(s_pixel, s_pixel->event.motion.x,
		s_pixel->event.motion.y);
		s_pixel->keys.but1_press = 1;
	}
	if (s_pixel->event.button.button == SDL_BUTTON_RIGHT)
		s_pixel->figure_now = -1;
}
