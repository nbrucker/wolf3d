/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 14:03:15 by nbrucker          #+#    #+#             */
/*   Updated: 2018/04/07 14:03:15 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf3d.h"

void	ft_check_map(t_env *env)
{
	int i;

	i = 0;
	while (i < env->map_x)
	{
		if (env->map[0][i] < 1 || env->map[env->map_y - 1][i] < 1)
			ft_error("Map error");
		i++;
	}
	i = 0;
	while (i < env->map_y)
	{
		if (env->map[i][0] < 1 || env->map[i][env->map_x - 1] < 1)
			ft_error("Map error");
		i++;
	}
}

void	ft_add(t_line **ptr, char *line)
{
	t_line *new;

	if ((new = (t_line*)malloc(sizeof(t_line))) == NULL)
		ft_error("Malloc error");
	if (*ptr)
		(*ptr)->next = new;
	new->previous = *ptr;
	*ptr = new;
	new->next = NULL;
	if ((new->split = ft_strsplit(line, ' ')) == NULL)
		ft_error("Malloc error");
	ft_check_split(new->split);
}

int		*ft_char_to_int(char **split, int len)
{
	int		i;
	int		*new;
	char	*tmp;

	if (!(new = (int*)malloc(sizeof(int) * len)))
		ft_error("Malloc error");
	i = 0;
	while (i < len)
	{
		new[i] = ft_atoi(split[i]);
		tmp = ft_itoa(new[i]);
		if (ft_strcmp(tmp, split[i]) != 0)
			ft_error("Map error");
		free(tmp);
		i++;
	}
	return (new);
}

int		**ft_list_to_map(t_env *env, t_line *line)
{
	int		**map;

	if (!(map = (int**)malloc(sizeof(int*) * (ft_listlen(line) + 1))))
		ft_error("Malloc error");
	env->map_y = 0;
	env->map_x = 0;
	if (line && line->split)
		env->map_x = ft_maplen(line->split);
	while (line)
	{
		if (ft_maplen(line->split) != env->map_x)
			ft_error("Map error");
		map[env->map_y] = ft_char_to_int(line->split, env->map_x);
		env->map_y++;
		line = line->next;
	}
	if (env->map_y < 3 || env->map_x < 3)
		ft_error("Map error");
	map[env->map_y] = 0;
	return (map);
}

void	ft_get_map(t_env *env, char *file)
{
	int		fd;
	int		ret;
	char	*line;
	t_line	*ptr;

	if ((fd = open(file, O_RDONLY)) == -1)
		ft_error("Error opening file");
	line = NULL;
	ptr = NULL;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		ft_add(&ptr, line);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	if (ret == -1)
		ft_error("Error reading file");
	if (close(fd) == -1)
		ft_error("Error closing file");
	while (ptr && ptr->previous)
		ptr = ptr->previous;
	env->map = ft_list_to_map(env, ptr);
	ft_freelist(ptr);
}
