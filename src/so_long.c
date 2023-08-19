/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 18:28:10 by apanikov          #+#    #+#             */
/*   Updated: 2023/06/04 18:28:12 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_map	*new_map(unsigned int lines)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		return (NULL);
	map->mapchars = ft_calloc(lines + 1, sizeof(char *));
	if (!map->mapchars)
	{
		free(map);
		return (NULL);
	}
	map->lines = lines;
	return (map);
}

int	ft_line_counter(char *mapname)
{
	int		fd;
	int		line_counter;
	char	*tmp;

	line_counter = 0;
	fd = open(mapname, O_RDONLY);
	if (fd < 0)
		eror_out(NULL, "File does not exist!\n");
	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		line_counter++;
		free(tmp);
	}
	close(fd);
	return (line_counter);
}

void	read_map(t_game *sl, char *mapname)
{
	int				fd;
	char			*tmp;
	unsigned int	i;

	i = 0;
	sl->map = new_map(ft_line_counter(mapname));
	if (!sl->map)
		eror_out(NULL, "Map init failed!\n");
	fd = open(mapname, O_RDONLY);
	if (fd < 0)
		eror_out(NULL, "File does not exist!\n");
	while (i < sl->map->lines)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			eror_out(NULL, "tmp_var init failed!\n");
		sl->map->mapchars[i] = ft_strtrim(tmp, "\n");
		if (!sl->map->mapchars[i++])
			return ;
		free(tmp);
	}
	close(fd);
}

void	start_game(char *mapname)
{
	t_game	sl;

	ft_bzero(&sl, sizeof(t_game));
	read_map(&sl, mapname);
	check_map(&sl);
	srites_path(&sl);
	render_map(&sl);
	mlx_hook(sl.mlx->win, 2, 1L << 0, key_hook, &sl);
	mlx_hook(sl.mlx->win, 17, 1L << 0, clean_out, &sl);
	mlx_loop(sl.mlx->mlx);
}

int	main(int argc, char **argv)
{	
	if (argc != 2)
		eror_out(NULL, "Incorrect size of argument!\n");
	if (!mapname_validator(argv[1]) || mapname_validator(argv[1]) == 0)
		eror_out(NULL, "Name of mapfile must end in .ber !\n");
	start_game(argv[1]);
	return (0);
}
