/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <nbrucker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 12:25:43 by nbrucker          #+#    #+#             */
/*   Updated: 2018/05/09 10:44:25 by dolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "mlx.h"
#include "libft.h"

void	ft_init_mlx_2(t_env *env, int bpp, int s_l, int endian)
{
	void	*ptr;

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

void	ft_init_mlx(t_env *env)
{
	int		bpp;
	int		s_l;
	int		endian;

	if ((env->mlx = mlx_init()) == NULL)
		ft_error("MLX Error");
	if ((env->win = mlx_new_window(env->mlx, WIDTH, HEIGHT, "wolf3d")) == NULL)
		ft_error("MLX Error");
	if ((env->image = mlx_new_image(env->mlx, WIDTH, HEIGHT)) == NULL)
		ft_error("MLX Error");
	if ((env->str = mlx_get_data_addr(env->image, &bpp, &s_l, &endian)) == NULL)
		ft_error("MLX Error");
	env->angle = 135;
	ft_init_mlx_2(env, bpp, s_l, endian);
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
				env->player_y = y + 0.1;
				env->player_x = x + 0.1;
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
	return ((env->texture[x]) + (env->texture[x + 1] << 8) +
		(env->texture[x + 2] << 16));
}
