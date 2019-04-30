/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 14:18:45 by arudyi            #+#    #+#             */
/*   Updated: 2019/04/30 14:52:09 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

double		ft_lightting1(t_elem *s_pixel, t_vector r_li, int i, t_vector dir)
{
	double		k;
	double		n_dot_l;
	t_vector	r;

	k = 0.0;
	n_dot_l = DOT(NORMAL, r_li);
	if (n_dot_l >= 0)
		k += L_INTE * n_dot_l / ft_vector_len(r_li);
	if (SPECU_OBJ > 0)
	{
		r = 2.0 * NORMAL * DOT(NORMAL, r_li) - r_li;
		n_dot_l = DOT(r, -dir);
		if (n_dot_l > 0)
			k += L_INTE * pow(n_dot_l / (LEN(r) * LEN(-dir)), SPECU_OBJ);
	}
	return (k);
}

int			ft_lighting(int color, int t, t_elem *s_pixel, t_vector dir)
{
	int			i;
	double		k;
	t_vector	r_li;

	k = 0.1;
	i = -1;
	while (++i < s_pixel->nbr_of_light)
	{
		if (TY_LI == 0)
			k += L_INTE;
		else
		{
			r_li = (TY_LI == 1) ? P_L - (P_POS + dir * t) : P_L;
			if (ft_is_shadow(s_pixel, t, dir, i) == 1)
				continue ;
			k += ft_lightting1(s_pixel, r_li, i, dir);
		}
	}
	color = ft_change_color(color, k);
	return (color);
}
