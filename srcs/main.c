/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <nbrucker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 12:25:43 by nbrucker          #+#    #+#             */
/*   Updated: 2018/05/09 09:41:45 by dolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "mlx.h"
#include "libft.h"

void	ft_get_texture2(t_env *env)
{
	if (env->side != 0)
	{
		if (env->ratio_y < 0)
		{
			env->texture = env->texture3;
			env->width_img = env->width_img3;
			env->height_img = env->height_img3;
		}
		else
		{
			env->texture = env->texture4;
			env->width_img = env->width_img4;
			env->height_img = env->height_img4;
		}
	}
}

void	ft_get_texture(t_env *env)
{
	if (env->side == 0)
	{
		if (env->ratio_x < 0)
		{
			env->texture = env->texture1;
			env->width_img = env->width_img1;
			env->height_img = env->height_img1;
		}
		else
		{
			env->texture = env->texture2;
			env->width_img = env->width_img2;
			env->height_img = env->height_img2;
		}
	}
	ft_get_texture2(env);
}

void	ft_while(t_env *env)
{
	while (ft_intab(env, env->round_x, env->round_y))
	{
		if (ft_intab(env, env->round_x, env->round_y +
			(env->ratio_y / 500)) == 0)
		{
			env->round_y += env->ratio_y / 500;
			env->side = 1;
			break ;
		}
		if (ft_intab(env, env->round_x +
			(env->ratio_x / 500), env->round_y) == 0)
		{
			env->round_x += env->ratio_x / 500;
			env->side = 0;
			break ;
		}
		env->round_x += env->ratio_x / 500;
		env->round_y += env->ratio_y / 500;
		if (env->ratio_x > env->ratio_y)
			env->side = 0;
		else
			env->side = 1;
	}
}

void	ft_display(t_env *env)
{
	int		x;
	double	angle;

	x = 0;
	angle = env->angle - 30;
	while (x < WIDTH)
	{
		angle = fmod(angle, 360);
		if (angle < 0)
			angle += 360;
		env->round_x = env->player_x;
		env->round_y = env->player_y;
		env->ratio_x = sin(angle * M_PI / 180);
		env->ratio_y = cos(angle * M_PI / 180) * -1;
		ft_while(env);
		env->distance = sqrt(pow(env->player_x - env->round_x, 2) +
			pow(env->player_y - env->round_y, 2));
		env->distance *= cos((angle - env->angle) * M_PI / 180);
		ft_get_texture(env);
		ft_trump(env, x, HEIGHT / env->distance);
		angle += 60 / (double)WIDTH;
		x++;
	}
	ft_expose(env);
}

int		main(int argc, char **argv)
{
	t_env	env;

	if (argc != 2)
		ft_usage();
	ft_get_map(&env, argv[1]);
	ft_check_map(&env);
	ft_get_position(&env);
	ft_init_mlx(&env);
	ft_display(&env);
	mlx_hook(env.win, 2, 3, ft_input, &env);
	mlx_hook(env.win, 17, 1L << 17, ft_exit, &env);
	mlx_expose_hook(env.win, ft_expose, &env);
	mlx_loop(env.mlx);
	ft_freeint(env.map, env.map_y);
	return (0);
}
