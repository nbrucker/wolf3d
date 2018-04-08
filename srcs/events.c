/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 14:54:17 by nbrucker          #+#    #+#             */
/*   Updated: 2018/04/07 14:54:17 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "mlx.h"

void	ft_move(int key, t_env *env)
{
	double	angle;
	double	x;
	double	y;

	angle = env->angle * M_PI / 180;
	if (key == 0)
		angle -= M_PI_2;
	else if (key == 2)
		angle += M_PI_2;
	else if (key == 1)
		angle += M_PI;
	x = env->player_x + 0.5 * cos(angle);
	y = env->player_y + 0.5 * sin(angle);
	if (ft_intab(env, floor(x), floor(env->player_y)) &&
		env->map[(int)floor(env->player_y)][(int)floor(x)] < 1)
		env->player_x = x;
	if (ft_intab(env, floor(env->player_x), floor(y)) &&
		env->map[(int)floor(y)][(int)floor(env->player_x)] < 1)
		env->player_y = y;
}

int		ft_input(int key, t_env *env)
{
	if (key == 53)
		exit(0);
	else if (key == 13 || key == 1)
		ft_move(key, env);
	else if (key == 0)
		env->angle -= 5;
	else if (key == 2)
		env->angle += 5;
	ft_display(env);
	return (0);
}

int		ft_expose(t_env *env)
{
	mlx_put_image_to_window(env->mlx, env->win, env->image, 0, 0);
	return (0);
}

int		ft_exit(t_env *env)
{
	(void)env;
	exit(0);
	return (0);
}
