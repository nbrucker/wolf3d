/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 14:01:05 by nbrucker          #+#    #+#             */
/*   Updated: 2018/04/07 14:01:06 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_freechar(char **map)
{
	int i;

	if (map == NULL)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	ft_freelist(t_line *line)
{
	t_line *next;

	while (line)
	{
		next = line->next;
		ft_freechar(line->split);
		free(line);
		line = next;
	}
}

void	ft_freeint(int **map, int len)
{
	int i;

	if (map == NULL)
		return ;
	i = 0;
	while (i < len)
	{
		free(map[i]);
		i++;
	}
	free(map);
}
