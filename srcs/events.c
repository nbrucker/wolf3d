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

int		ft_input(int key, t_env *env)
{
	env->ratio_x = sin(env->angle * M_PI / 180) / 10;
	env->ratio_y = cos(env->angle * M_PI / 180) * -1 / 10;
	if (key == 53)
		exit(0);
	else if (key == 13)
	{
		if (ft_intab(env, env->player_x + env->ratio_x, env->player_y))
			env->player_x += env->ratio_x;
		if (ft_intab(env, env->player_x, env->player_y + env->ratio_y))
			env->player_y += env->ratio_y;
	}
	else if (key == 1)
	{
		if (ft_intab(env, env->player_x - env->ratio_x, env->player_y))
			env->player_x -= env->ratio_x;
		if (ft_intab(env, env->player_x, env->player_y - env->ratio_y))
			env->player_y -= env->ratio_y;
	}
	else if (key == 2)
		env->angle += 5;
	else if (key == 0)
		env->angle -= 5;
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
