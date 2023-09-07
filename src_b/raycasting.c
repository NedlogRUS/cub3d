/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 21:46:43 by apanikov          #+#    #+#             */
/*   Updated: 2023/09/06 14:39:12 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	side_of_the_wall(t_data *c3d)
{
	if (c3d->side == 0)
	{
		if (c3d->raydirx > 0)
			c3d->wallt = c3d->e;
		else
			c3d->wallt = c3d->w;
	}
	else
	{
		if (c3d->raydiry > 0)
			c3d->wallt = c3d->n;
		else
			c3d->wallt = c3d->s;
	}
}

void	calculating_textured_rendering_wall(t_data *c3d, int x)
{
	int	y;

	c3d->texx = (int)(c3d->wallx * (double)c3d->wallt->width);
	if ((c3d->side == 0 && c3d->raydirx > 0) \
		|| (c3d->side == 1 && c3d->raydiry < 0))
		c3d->texx = c3d->wallt->width - c3d->texx - 1;
	c3d->texheight = (int)(SCREENHEIGHT / c3d->perpwalldist);
	c3d->drawstart = -c3d->texheight / 2 + SCREENHEIGHT / 2;
	if (c3d->drawstart < 0)
		c3d->drawstart = 0;
	c3d->drawend = c3d->texheight / 2 + SCREENHEIGHT / 2;
	if (c3d->drawend >= SCREENHEIGHT)
		c3d->drawend = SCREENHEIGHT - 1;
	y = c3d->drawstart;
	while (y < c3d->drawend)
	{
		c3d->texy = (int)(((y - SCREENHEIGHT / 2 + c3d->texheight / 2) \
			* c3d->wallt->height) / c3d->texheight);
		c3d->color = c3d->wallt->addr[c3d->texy \
			* c3d->wallt->width + c3d->texx];
		c3d->image->addr[y * SCREENWIDTH + x] = c3d->color;
		y++;
	}
}

void	initializing_parameters_raycasting(t_data *c3d, int x)
{
	c3d->camerax = 2 * x / (double)SCREENWIDTH - 1;
	c3d->raydirx = c3d->dirx + c3d->planex * c3d->camerax;
	c3d->raydiry = c3d->diry + c3d->planey * c3d->camerax;
	c3d->mapx = (int)c3d->posx;
	c3d->mapy = (int)c3d->posy;
	if (c3d->raydirx == 0)
		c3d->deltadistx = 1e30;
	else
		c3d->deltadistx = fabs(1 / c3d->raydirx);
	if (c3d->raydiry == 0)
		c3d->deltadisty = 1e30;
	else
		c3d->deltadisty = fabs(1 / c3d->raydiry);
	c3d->hit = 0;
}

void	raycasting_core(t_data *c3d)
{
	int	x;

	x = 0;
	while (x < SCREENWIDTH)
	{
		initializing_parameters_raycasting(c3d, x);
		determine_ray_intersects_distances(c3d);
		hit_wall(c3d);
		calculating_parameters_rendering_wall(c3d);
		side_of_the_wall(c3d);
		calculating_textured_rendering_wall(c3d, x);
		x++;
	}
}

void	raycasting(t_data *c3d)
{
	c3d->image = malloc(sizeof(t_img));
	c3d->image->img = mlx_new_image(c3d->mlx, SCREENWIDTH, SCREENHEIGHT);
	c3d->image->addr = (int *)mlx_get_data_addr(c3d->image->img, \
		&c3d->image->bpp, &c3d->image->ll, \
		&c3d->image->endian);
	floor_ceiling(c3d);
	raycasting_core(c3d);
	mlx_put_image_to_window(c3d->mlx, c3d->win, c3d->image->img, 0, 0);
	mlx_destroy_image(c3d->mlx, c3d->image->img);
	free(c3d->image);
	bear_claws(c3d);
}
