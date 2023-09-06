/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 21:39:39 by apanikov          #+#    #+#             */
/*   Updated: 2023/09/06 15:01:58 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	initclaws(t_data *c3d)
{
	int	x;
	int	y;

	x = 120;
	y = 1800;
	c3d->claw_left = mlx_xpm_file_to_image(c3d->mlx, \
		"./sprites/claw_left.xpm", &x, &y);
	c3d->claw_right = mlx_xpm_file_to_image(c3d->mlx, \
		"./sprites/claw_right.xpm", &x, &y);
	if (c3d->claw_left == NULL || c3d->claw_right == NULL)
		parse_error("Bad texture");
}

void	get_tex_addr(t_data *c3d)
{
	c3d->s->addr = (int *)mlx_get_data_addr(c3d->s->img, &c3d->s->bpp, \
		&c3d->s->ll, &c3d->s->endian);
	c3d->w->addr = (int *)mlx_get_data_addr(c3d->w->img, &c3d->w->bpp, \
		&c3d->w->ll, &c3d->w->endian);
	c3d->n->addr = (int *)mlx_get_data_addr(c3d->n->img, &c3d->n->bpp, \
		&c3d->n->ll, &c3d->n->endian);
	c3d->e->addr = (int *)mlx_get_data_addr(c3d->e->img, &c3d->e->bpp, \
		&c3d->e->ll, &c3d->e->endian);
}

void	inittext(t_data *c3d)
{
	c3d->n = malloc(sizeof(t_img));
	c3d->n->img = mlx_xpm_file_to_image(c3d->mlx, c3d->txn, \
		&c3d->n->width, &c3d->n->height);
	c3d->w = malloc(sizeof(t_img));
	c3d->w->img = mlx_xpm_file_to_image(c3d->mlx, c3d->txw, \
		&c3d->w->width, &c3d->w->height);
	c3d->s = malloc(sizeof(t_img));
	c3d->s->img = mlx_xpm_file_to_image(c3d->mlx, c3d->txs, \
		&c3d->s->width, &c3d->s->height);
	c3d->e = malloc(sizeof(t_img));
	c3d->e->img = mlx_xpm_file_to_image(c3d->mlx, c3d->txe, \
		&c3d->e->width, &c3d->e->height);
	if (c3d->n->img == NULL || c3d->w->img == NULL || \
		c3d->s->img == NULL || c3d->e->img == NULL)
		parse_error("Bad texture");
	get_tex_addr(c3d);
	return ;
}

int	cubclose(void)
{
	printf("Thanks for playing\n");
	system("leaks cub3D");
	exit(0);
}

int	keyhandle(int keycode, t_data *c3d)
{
	if (keycode == 53)
		cubclose();
	if (keycode == 1 || keycode == 126 || keycode == 13 || keycode == 125)
	{
		if (c3d->stp == 16)
			c3d->stp = 0;
		else
			c3d->stp++;
	}
	if (keycode == 126 || keycode == 125 || keycode == 124 || keycode == 123 \
	|| keycode == 0 || keycode == 1 || keycode == 2 || keycode == 13)
		update_camera_position(keycode, c3d);
	return (0);
}

int	mouse_move(int x, int y, t_data *c3d)
{
	mlx_mouse_hide();
	mlx_mouse_get_pos(c3d->win, &x, &y);
	if (x > SCREENWIDTH / 2)
		update_camera_position(124, c3d);
	if (x < SCREENWIDTH / 2)
		update_camera_position(123, c3d);
	mlx_mouse_move(c3d->win, SCREENWIDTH / 2, y / 2);
	return (0);
}

void	initorient(t_data *c3d)
{
	if (c3d->map->spawn_orient == 'W')
	{
	c3d->dirx = 0;
	c3d->diry = -1;
	c3d->planex = -0.66;
	c3d->planey = 0;
	}
	else if (c3d->map->spawn_orient == 'E')
	{
	c3d->dirx = 0;
	c3d->diry = 1;
	c3d->planex = 0.66;
	c3d->planey = 0;
	}
	else if (c3d->map->spawn_orient == 'S')
	{
	c3d->dirx = 1;
	c3d->diry = 0;
	c3d->planex = 0;
	c3d->planey = -0.66;
	}
	else if (c3d->map->spawn_orient == 'N')
	{
	c3d->dirx = -1;
	c3d->diry = 0;
	c3d->planex = 0;
	c3d->planey = 0.66;
	}
}

void	claws_util(t_data *c3d)
{
	if (c3d->stp == 0 || c3d->stp == 1 || c3d->stp == 8 || c3d->stp == 9)
	{
		c3d->add_l = 0;
		c3d->add_r = 0;
	}
	else if (c3d->stp == 2 || c3d->stp == 3 || c3d->stp == 6 || c3d->stp == 7)
	{
		c3d->add_l = 10;
		c3d->add_r = -10;
	}
	else if (c3d->stp == 4 || c3d->stp == 5)
	{
		c3d->add_l = 20;
		c3d->add_r = -20;
	}
	else if (c3d->stp == 10 || c3d->stp == 11 || c3d->stp == 14 \
		|| c3d->stp == 15)
	{
		c3d->add_l = -10;
		c3d->add_r = 10;
	}
	else if (c3d->stp == 12 || c3d->stp == 13)
	{
		c3d->add_l = -20;
		c3d->add_r = 20;
	}
}

int	bear_claws(t_data *c3d)
{
	int	x;
	int	y;
	int	xr;
	int	yr;

	x = 190;
	y = 400;
	xr = 390;
	yr = 400;
	claws_util(c3d);
	mlx_put_image_to_window(c3d->mlx, c3d->win, \
		c3d->claw_left, x, y + c3d->add_l);
	mlx_put_image_to_window(c3d->mlx, c3d->win, \
	c3d->claw_right, xr, yr + c3d->add_r);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*c3d;

	c3d = malloc(sizeof(t_data));
	c3d->map = malloc(sizeof(t_map));
	parsing(c3d->map, argv, argc, c3d);
	c3d->stp = 0;
	c3d->movespeed = 0.15;
	c3d->rotspeed = 0.15;
	c3d->mlx = mlx_init();
	c3d->win = mlx_new_window(c3d->mlx, SCREENWIDTH, SCREENHEIGHT, "cub3D");
	c3d->txn = c3d->map->n_path;
	c3d->txw = c3d->map->w_path;
	c3d->txs = c3d->map->s_path;
	c3d->txe = c3d->map->e_path;
	initorient(c3d);
	inittext(c3d);
	initclaws(c3d);
	raycasting(c3d);
	mlx_hook(c3d->win, 2, 1L << 0, keyhandle, c3d);
	mlx_hook(c3d->win, 6, 1L << 6, mouse_move, c3d);
	mlx_hook(c3d->win, 17, 1L << 0, cubclose, c3d);
	mlx_loop(c3d->mlx);
	return (0);
}
