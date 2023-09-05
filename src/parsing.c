/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 17:48:27 by adavitav          #+#    #+#             */
/*   Updated: 2023/09/05 15:27:22 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	trim_spaces(char **col_arr)
{
	int		i;
	char	*save;

	i = 0;
	while (col_arr[i] != NULL)
	{
		save = col_arr[i];
		col_arr[i] = ft_strtrim(col_arr[i], " ");
		free(save);
		i++;
	}
}

void	fname_check(char *filename)
{
	if (ft_strlen(filename) == 4)
		parse_error("Wrong filename");
	while (*filename != '.')
		filename++;
	if (ft_strnstr(filename, ".cub", 4) == 0 || ft_strlen(filename) != 4)
		parse_error("Wrong file extension");
}

void	check_textures(char *arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if (arr[i] == ' ')
			parse_error("Found spaces in texture paths");
		i++;
	}
}
void	call_check_textures(t_map *map)
{
	check_textures(map->south_path);
	check_textures(map->west_path);
	check_textures(map->east_path);
	check_textures(map->north_path);
}

void	parsing(t_map *map, char **filename, int ac, t_data *c3d)
{
	c3d->posX = -1;
	if (ac != 2)
		parse_error("Wrong number of arguments");
	fname_check(filename[1]);
	map->fd = open(filename[1], O_RDONLY);
	if (map->fd == -1)
		parse_error("Open");
	get_texts_colors(map);
	call_check_textures(map);
	convert_colors(ft_split(map->ccolor, ','), ft_split(map->fcolor, ','), c3d);
	parse_map(map, c3d);
	if (c3d->posX == -1)
		parse_error("No player position");
	// set_pos(map);
	// convert_to_int(map);
}
