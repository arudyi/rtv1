/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 14:31:06 by arudyi            #+#    #+#             */
/*   Updated: 2019/04/29 17:13:15 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

t_vector	ft_normalize_vector(t_vector vec)
{
	double len;

	len = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	vec.x /= len;
	vec.y /= len;
	vec.z /= len;
	return (vec);
}

double		ft_dot_product(t_vector vec1, t_vector vec2)
{
	double nbr;

	nbr = vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
	return (nbr);
}

t_vector	ft_reflect_ray(t_vector r, t_vector normal)
{
	return (2 * normal * ft_dot_product(normal, r) - r);
}

double		ft_vector_len(t_vector vec)
{
	double len;

	len = sqrt(ft_dot_product(vec, vec));
	return (len);
}
