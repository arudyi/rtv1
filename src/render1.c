/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 17:03:57 by arudyi            #+#    #+#             */
/*   Updated: 2019/04/30 17:04:09 by arudyi           ###   ########.fr       */
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