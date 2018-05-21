/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_the_wall.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <nbrucker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 12:25:43 by nbrucker          #+#    #+#             */
/*   Updated: 2018/05/09 09:42:38 by dolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "mlx.h"
#include "libft.h"

void	ft_trump(t_env *env, int x, int h)
{
	int y;
	int sy;

	y = 0;
	while (y < (HEIGHT / 2) - (h / 2) && y < HEIGHT)
	{
		ft_fill_pixel(env, x, y, 0xcfdeee);
		y++;
	}
	sy = y;
	while (y < (HEIGHT / 2) + (h / 2) && y < HEIGHT)
	{
		ft_fill_pixel(env, x, y, ft_color(env, y - sy, h));
		y++;
	}
	while (y < HEIGHT)
	{
		ft_fill_pixel(env, x, y, 0x767676);
		y++;
	}
}
