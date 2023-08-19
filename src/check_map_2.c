/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 18:27:28 by apanikov          #+#    #+#             */
/*   Updated: 2023/06/04 18:27:31 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	fill(t_map *map, char **m, unsigned int x, unsigned int y)
{
	if (!(m[y][x] == 'C' || m[y][x] == '0' || m[y][x] == 'E'
		|| m[y][x] == 'P'))
		return ;
	m[y][x] += 7;
	if (m[y][x] == 'L')
		return ;
	fill(map, map->mapchars, x - 1, y);
	fill(map, map->mapchars, x, y - 1);
	fill(map, map->mapchars, x, y + 1);
	fill(map, map->mapchars, x + 1, y);
}

int	check_mvp(t_map *map)
{
	while (map->mapchars[map->b_y])
	{
		while (map->mapchars[map->b_y][map->b_x])
		{
			if (map->mapchars[map->b_y][map->b_x] == 'P')
				break ;
			map->b_x += 1;
		}
		if (map->mapchars[map->b_y][map->b_x] == 'P')
			break ;
		map->b_x = 0;
		map->b_y += 1;
	}
	fill(map, map->mapchars, map->b_x, map->b_y);
	if (check_chr(map, 'C') != 0 || check_chr(map, 'E') != 0)
		return (1);
	return (0);
}

int	check_chr(t_map *map, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map->mapchars[i])
	{
		while (map->mapchars[i][j])
		{
			if (map->mapchars[i][j] == c)
				return (1);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}
