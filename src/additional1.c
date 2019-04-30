/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 14:34:33 by arudyi            #+#    #+#             */
/*   Updated: 2019/04/30 16:46:27 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

t_vector	ft_canvas_to_viewport(double x, double y)
{
	t_vector direction;

	direction.x = x / WIDTH - 0.5;
	direction.y = 0.5 + -y / HEIGHT;
	direction.z = 1;
	return (direction);
}

t_vector	ft_rotate_camera(t_vector direction, t_elem *s_pixel)
{
	double new_x;
	double new_y;
	double new_z;
	double angle1;
	double angle2;

	angle1 = s_pixel->player.angle_gor / 180.0 * 3.14;
	angle2 = s_pixel->player.angle_ver / 180.0 * 3.14;
	new_x = direction.x * cos(angle1) + direction.z * sin(angle1);
	new_y = direction.y;
	new_z = -direction.x * sin(angle1) + direction.z * cos(angle1);
	direction.x = new_x;
	direction.y = new_y;
	direction.z = new_z;
	new_x = direction.x;
	new_y = direction.y * cos(angle2) + direction.z * sin(angle2);
	new_z = -direction.y * sin(angle2) + direction.z * cos(angle2);
	direction.x = new_x;
	direction.y = new_y;
	direction.z = new_z;
	return (direction);
}

unsigned	ft_change_color(unsigned color, double k)
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

unsigned	ft_add_color(unsigned color1, unsigned color2, unsigned new_color,
unsigned r1)
{
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

int			exit_program(t_elem *s_pixel)
{
	SDL_FreeSurface(s_pixel->surface);
	SDL_DestroyWindow(s_pixel->window);
	SDL_DestroyRenderer(s_pixel->renderrer);
	SDL_Quit();
	system("leaks RTv1");
	exit(1);
	return (0);
}
