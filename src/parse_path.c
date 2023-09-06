/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 17:48:17 by adavitav          #+#    #+#             */
/*   Updated: 2023/09/06 14:39:12 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	id_check(char *ids)
{
	while (*ids)
	{
		if (*ids != ' ')
			return (1);
		ids++;
	}
	return (0);
}

void	trim_stuff(t_map *map)
{
	char		*save;
	char const	*nl;

	save = map->n_path;
	nl = ft_strdup("\n");
	map->n_path = ft_strtrim(map->n_path, nl);
	free(save);
	save = map->s_path;
	map->s_path = ft_strtrim(map->s_path, nl);
	free(save);
	save = map->w_path;
	map->w_path = ft_strtrim(map->w_path, nl);
	free(save);
	save = map->e_path;
	map->e_path = ft_strtrim(map->e_path, nl);
	free(save);
	save = map->ccolor;
	map->ccolor = ft_strtrim(map->ccolor, nl);
	free(save);
	save = map->fcolor;
	map->fcolor = ft_strtrim(map->fcolor, nl);
	free(save);
	free((void *)nl);
}

int	add_info(char to_remove, t_map *map, char *ids, char *line)
{
	printf("%s, %c\n", ids, to_remove);
	while (*ids != to_remove && *ids)
		ids++;
	printf("[%s]\n", ids);
	if (!*ids)
		parse_error("Same id twice");
	*ids = ' ';
	space_skip(&line);
	if (*line == '\0' || *line == '\n')
		parse_error("Nothing comes after identifier");
	if (to_remove == 'N')
		map->n_path = ft_strdup(line);
	else if (to_remove == 'S')
		map->s_path = ft_strdup(line);
	else if (to_remove == 'W')
		map->w_path = ft_strdup(line);
	else if (to_remove == 'E')
		map->e_path = ft_strdup(line);
	else if (to_remove == 'C')
		map->ccolor = ft_strdup(line);
	else if (to_remove == 'F')
		map->fcolor = ft_strdup(line);
	return (1);
}

int	get_info(char *line, char *ids, t_map *map)
{
	if (*line == '\n')
		return (1);
	if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		return (add_info('N', map, ids, line + 2));
	else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		return (add_info('S', map, ids, line + 2));
	else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		return (add_info('W', map, ids, line + 2));
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		return (add_info('E', map, ids, line + 2));
	else if (line[0] == 'F' && line[1] == ' ')
		return (add_info('F', map, ids, line + 1));
	else if (line[0] == 'C' && line[1] == ' ')
		return (add_info('C', map, ids, line + 1));
	else
		parse_error("invalid identifier");
	return (0);
}

void	get_texts_colors(t_map *map)
{
	char	*ids;

	ids = ft_strdup("NSWEFC");
	map->line = get_next_line(map->fd);
	if (!map->line)
		parse_error("Empty file");
	while (get_info(map->line, ids, map) == 1 && id_check(ids) == 1)
	{
		free(map->line);
		map->line = get_next_line(map->fd);
		if (!map->line)
			parse_error("Empty file");
	}
	trim_stuff(map);
	free(ids);
}
