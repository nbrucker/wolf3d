/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 12:25:43 by nbrucker          #+#    #+#             */
/*   Updated: 2018/04/07 12:25:43 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "mlx.h"
#include "libft.h"

void	ft_init_mlx(t_env *env)
{
	int		bpp;
	int		s_l;
	int		endian;
	void	*ptr;

	if ((env->mlx = mlx_init()) == NULL)
		ft_error("MLX Error");
	if ((env->win = mlx_new_window(env->mlx, WIDTH, HEIGHT, "wolf3d")) == NULL)
		ft_error("MLX Error");
	if ((env->image = mlx_new_image(env->mlx, WIDTH, HEIGHT)) == NULL)
		ft_error("MLX Error");
	if ((env->str = mlx_get_data_addr(env->image, &bpp, &s_l, &endian)) == NULL)
		ft_error("MLX Error");
	env->angle = 135;
	ptr = mlx_xpm_file_to_image(env->mlx, "textures/texture_1.xpm",
			&env->width_img1, &env->height_img1);
	env->texture1 = mlx_get_data_addr(ptr, &bpp,
			&s_l, &endian);
	ptr = mlx_xpm_file_to_image(env->mlx, "textures/texture_2.xpm",
			&env->width_img2, &env->height_img2);
	env->texture2 = mlx_get_data_addr(ptr, &bpp,
			&s_l, &endian);
	ptr = mlx_xpm_file_to_image(env->mlx, "textures/texture_3.xpm",
			&env->width_img3, &env->height_img3);
	env->texture3 = mlx_get_data_addr(ptr, &bpp,
			&s_l, &endian);
	ptr = mlx_xpm_file_to_image(env->mlx, "textures/texture_4.xpm",
			&env->width_img4, &env->height_img4);
	env->texture4 = mlx_get_data_addr(ptr, &bpp,
			&s_l, &endian);
}

void	ft_get_position(t_env *env)
{
	int x;
	int y;

	if (env->map_y < 3 || env->map_x < 3)
		ft_error("Map error");
	env->player_x = -1;
	env->player_y = -1;
	y = 1;
	while (y < env->map_y - 1 && env->player_y == -1 && env->player_x == -1)
	{
		x = 1;
		while (x < env->map_x - 1 && env->player_y == -1 && env->player_x == -1)
		{
			if (env->map[y][x] < 1)
			{
				env->player_y = y;
				env->player_x = x;
			}
			x++;
		}
		y++;
	}
	if (env->player_y == -1 || env->player_x == -1)
		ft_error("Map error");
}

int		ft_intab(t_env *env, double x, double y)
{
	int	rx;
	int ry;

	rx = (int)floor(x);
	ry = (int)floor(y);
	if (rx < 0 || ry < 0 || rx >= env->map_x || ry >= env->map_y)
		return (0);
	if (env->map[ry][rx] > 0)
		return (0);
	return (1);
}

int		ft_color(t_env *env, int y, int h)
{
	int	x;

	if (env->side == 1)
	{
		if (env->ratio_y < 0)
			x = fmod(env->round_x, 1) * env->width_img;
		else
			x = (1 - fmod(env->round_x, 1)) * env->width_img;
	}
	else
	{
		if (env->ratio_x < 0)
			x = (1 - fmod(env->round_y, 1)) * env->width_img;
		else
			x = fmod(env->round_y, 1) * env->width_img;
	}
	if (h >= HEIGHT)
		y = y + ((h - HEIGHT) / 2);
	y = (double)y / (double)h * env->height_img;
	x = ((y * env->width_img) + x) * 4;
	if (x < 0 || x >= env->width_img * env->height_img * 4)
		return (0);
	return ((env->texture[x]) + (env->texture[x + 1] << 8) + (env->texture[x + 2] << 16));
}

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
