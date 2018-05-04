/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 14:03:06 by nbrucker          #+#    #+#             */
/*   Updated: 2018/04/07 14:03:10 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "mlx.h"
#include "libft.h"

void	ft_fill_pixel(t_env *env, int x, int y, int color)
{
	int i;

	i = ((y * WIDTH) + x) * 4;
	if (i < 0 || i >= WIDTH * HEIGHT * 4)
		return ;
	env->str[i] = color & 0xFF;
	env->str[i + 1] = (color >> 8) & 0xFF;
	env->str[i + 2] = (color >> 16) & 0xFF;
}

void	ft_usage(void)
{
	ft_error("./wolf3d map");
}

int		ft_listlen(t_line *line)
{
	int i;

	i = 0;
	while (line)
	{
		line = line->next;
		i++;
	}
	return (i);
}

int		ft_maplen(char **s1)
{
	int i;

	if (s1 == NULL)
		return (0);
	i = 0;
	while (s1[i])
		i++;
	return (i);
}

void	ft_check_split(char **split)
{
	int		i;
	char	*tmp;

	i = 0;
	while (split[i])
	{
		if ((tmp = ft_itoa(ft_atoi(split[i]))) == NULL)
			ft_error("Malloc error");
		if (ft_strcmp(tmp, split[i]) != 0)
			ft_error("Map error");
		free(tmp);
		i++;
	}
}
