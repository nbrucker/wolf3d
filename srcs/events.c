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
	if (key == 53)
		exit(0);
	(void)env;
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
