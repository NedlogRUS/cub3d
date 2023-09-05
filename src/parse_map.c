/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 17:47:55 by adavitav          #+#    #+#             */
/*   Updated: 2023/09/05 18:02:02 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	check_map(char **line, t_map *map)
{
	char		*save;
	char const	*nl;
	static int	player_flag = 0;

	save = *line;
	nl = ft_strdup("\n");
	*line = ft_strtrim(*line, nl);
	free(save);
	save = *line;
	while (*save)
	{
		if ((*save == 'N' || *save == 'S' || *save == 'W' || *save == 'E')
			&& player_flag == 0)
		{
			player_flag = 1;
			map->spawn_orient = *save;
		}
		else if (*save != '1' && *save != '0' && *save != ' ')
			parse_error("Extra characters");
		save++;
	}
	free((char *)nl);
	return (1);
}



void	check_map_final(int fd, char *line)
{
	if (!line)
		return ;
	free(line);
	line = get_next_line(fd);
	while (line && *line)
	{
		if (*line != '\n')
			parse_error("something comes after map file");
		free(line);
		line = get_next_line(fd);
	}
}

void	check_walls(t_map *map, int x, int y, t_data *c3d)
{
	while (map->map_arr[y])
	{
		x = 0;
		while (map->map_arr[y][x])
		{
			if (map->map_arr[y][x] == map->spawn_orient)
			{
				c3d->posX = y + 0.5;
				c3d->posY = x + 0.5;
				map->map_arr[y][x] = '0';
			}
			if (map->map_arr[y][x] == '0')
			{
				if (y == 0 || y == arrsize(map->map_arr))
					parse_error("Map should be enclosed with walls");
				check_positions(map->map_arr[y - 1][x], map->spawn_orient);
				check_positions(map->map_arr[y + 1][x], map->spawn_orient);
				check_positions(map->map_arr[y][x - 1], map->spawn_orient);
				check_positions(map->map_arr[y][x + 1], map->spawn_orient);
			}
			x++;
		}
		y++;
	}
}

void	add_line(t_map *map, char *to_add)
{
	static int	size = 1;
	char		**new_arr;

	new_arr = NULL;
	if (size == 1)
	{
		map->map_arr = (char **)malloc(sizeof(char *) * (size + 1));
		map->map_arr[0] = to_add;
		map->map_arr[1] = NULL;
		size++;
		return ;
	}
	else
	{
		new_arr = (char **)malloc(sizeof(char *) * (size + 1));
		arrcpy(map->map_arr, new_arr);
		new_arr[size - 1] = to_add;
		new_arr[size] = NULL;
		free_arr(map->map_arr);
		map->map_arr = new_arr;
		size++;
		return ;
	}
}

void	parse_map(t_map *map, t_data *c3d)
{
	char	*line;
	int		i;

	line = get_next_line(map->fd);
	i = 0;
	while (*line == '\n')
	{
		free(line);
		line = get_next_line(map->fd);
	}
	if (!line)
		parse_error("No map");
	while (check_map(&line, map))
	{
		add_line(map, line);
		line = get_next_line(map->fd);
		if (!line || *line == '\n')
		{
			check_map_final(map->fd, line);
			break ;
		}
		i++;
	}
	check_walls(map, 0, 0, c3d);
}
