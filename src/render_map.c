/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 18:27:55 by apanikov          #+#    #+#             */
/*   Updated: 2023/06/04 18:27:58 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_sprites(t_game *sl)
{
	sl->sprite->field = file_to_image(sl, sl->sprite->path[0]);
	sl->sprite->wall = file_to_image(sl, sl->sprite->path[1]);
	sl->sprite->bear = file_to_image(sl, sl->sprite->path[2]);
	sl->sprite->bearr = file_to_image(sl, sl->sprite->path[3]);
	sl->sprite->honey = file_to_image(sl, sl->sprite->path[4]);
	sl->sprite->car = file_to_image(sl, sl->sprite->path[5]);
	sl->sprite->caronfire = file_to_image(sl, sl->sprite->path[6]);
	sl->sprite->bearincar = file_to_image(sl, sl->sprite->path[7]);
	sl->sprite->win = file_to_image(sl, sl->sprite->path[8]);
}

void	*file_to_image(t_game *sl, char *path)
{
	void	*img;
	int		img_width;
	int		img_height;

	img = mlx_xpm_file_to_image(sl->mlx->mlx, path, &img_width, &img_height);
	if (!img)
		eror_out(sl, "Image init failed!\n");
	return (img);
}

void	*chose_img(t_game *sl, char symbol)
{
	if (symbol == '1')
		return (sl->sprite->wall);
	else if (symbol == '7' || symbol == '0')
		return (sl->sprite->field);
	else if (symbol == 'W')
		return (sl->sprite->bear);
	else if (symbol == 'P')
		return (sl->sprite->bearr);
	else if (symbol == 'J')
		return (sl->sprite->honey);
	else if (symbol == 'L' && sl->map->num_honey > 0)
		return (sl->sprite->car);
	else if (symbol == 'L' && sl->map->num_honey == 0)
		return (sl->sprite->caronfire);
	else if (symbol == 'X')
		return (sl->sprite->bearincar);
	else
		return (NULL);
}

void	print_map(t_game *sl)
{
	unsigned int	x;
	unsigned int	y;
	char			symbol;
	void			*img;

	x = 0;
	y = 0;
	while (y < sl->map->lines)
	{
		while (x < sl->map->columns)
		{
			symbol = sl->map->mapchars[y][x];
			img = chose_img(sl, symbol);
			if (!img)
				eror_out(sl, "Image selection failed!\n");
			mlx_put_image_to_window(sl->mlx->mlx, sl->mlx->win, \
			img, x * 100, y * 100);
			x++;
		}
		x = 0;
		y++;
	}
	ft_putnbr_fd(sl->step_count, 1);
	ft_putstr_fd(" steps\n", 1);
}

void	render_map(t_game *sl)
{
	sl->mlx = ft_calloc(1, sizeof(t_data));
	if (!sl->mlx)
		eror_out(sl, "mlx init failed!\n");
	sl->mlx->mlx = mlx_init();
	if (!sl->mlx->mlx)
		eror_out(sl, "mlx_init failed!\n");
	sl->mlx->win = mlx_new_window(sl->mlx->mlx, \
	sl->map->columns * 100, sl->map->lines * 100, "so_long");
	init_sprites(sl);
	print_map(sl);
}
