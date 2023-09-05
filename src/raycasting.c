/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 21:46:43 by apanikov          #+#    #+#             */
/*   Updated: 2023/09/05 22:59:03 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	floor_ceiling(t_data *c3d)
{
	int	y;
	int	x;

	y = 0;
	while (y < SCREENHEIGHT / 2)
	{
		x = 0;
		while (x < SCREENWIDTH)
			c3d->image->addr[y * SCREENWIDTH + x++] = c3d->ceilingColor;
		y++;
	}
	y = SCREENHEIGHT / 2;
	while (y < SCREENHEIGHT)
	{
		x = 0;
		while (x < SCREENWIDTH)
			c3d->image->addr[y * SCREENWIDTH + x++] = c3d->floorColor;
		y++;
	}
}

void	determine_ray_intersects_distances(t_data *c3d)
{
	if (c3d->rayDirX < 0)
	{
		c3d->stepX = -1;
		c3d->sideDistX = (c3d->posX - c3d->mapX) * c3d->deltaDistX;
	}
	else
	{
		c3d->stepX = 1;
		c3d->sideDistX = (c3d->mapX + 1.0 - c3d->posX) * c3d->deltaDistX;
	}
	if (c3d->rayDirY < 0)
	{
		c3d->stepY = -1;
		c3d->sideDistY = (c3d->posY - c3d->mapY) * c3d->deltaDistY;
	}
	else
	{
		c3d->stepY = 1;
		c3d->sideDistY = (c3d->mapY + 1.0 - c3d->posY) * c3d->deltaDistY;
	}
}

void	hit_wall(t_data *c3d)
{
	while (c3d->hit == 0)
	{
		if (c3d->sideDistX < c3d->sideDistY)
		{
			c3d->sideDistX += c3d->deltaDistX;
			c3d->mapX += c3d->stepX;
			c3d->side = 0;
		}
		else
		{
			c3d->sideDistY += c3d->deltaDistY;
			c3d->mapY += c3d->stepY;
			c3d->side = 1;
		}
		if (c3d->map->map_arr[c3d->mapX][c3d->mapY] == '1')
			c3d->hit = 1;
	}
}

void	calculating_parameters_rendering_wall(t_data *c3d)
{
	if (c3d->side == 0)
		c3d->perpWallDist = (c3d->sideDistX - c3d->deltaDistX);
	else
		c3d->perpWallDist = (c3d->sideDistY - c3d->deltaDistY);
	c3d->lineHeight = (int)(SCREENHEIGHT / c3d->perpWallDist);
	c3d->drawStart = -c3d->lineHeight / 2 + SCREENHEIGHT / 2;
	if (c3d->drawStart < 0)
		c3d->drawStart = 0;
	c3d->drawEnd = c3d->lineHeight / 2 + SCREENHEIGHT / 2;
	if (c3d->drawEnd >= SCREENHEIGHT)
		c3d->drawEnd = SCREENHEIGHT - 1;
	if (c3d->side == 1)
		c3d->color = c3d->color / 2;
	if (c3d->side == 0)
		c3d->wallX = c3d->posY + c3d->perpWallDist * c3d->rayDirY;
	else
		c3d->wallX = c3d->posX + c3d->perpWallDist * c3d->rayDirX;
	c3d->wallX -= floor(c3d->wallX);
}

void	side_of_the_wall(t_data *c3d)
{
	if (c3d->side == 0)
	{
		if (c3d->rayDirX > 0)
			c3d->wallT = c3d->east;
		else
			c3d->wallT = c3d->west;
	}
	else
	{
		if (c3d->rayDirY > 0)
			c3d->wallT = c3d->north;
		else
			c3d->wallT = c3d->south;
	}
}

void	calculating_textured_rendering_wall(t_data *c3d, int x)
{
	int	y;

	c3d->texX = (int)(c3d->wallX * (double)c3d->wallT->width);
	if ((c3d->side == 0 && c3d->rayDirX > 0) || (c3d->side == 1 && c3d->rayDirY < 0))
		c3d->texX = c3d->wallT->width - c3d->texX - 1;
	c3d->texHeight = (int)(SCREENHEIGHT / c3d->perpWallDist);
	c3d->drawStart = -c3d->texHeight / 2 + SCREENHEIGHT / 2;
	if (c3d->drawStart < 0)
		c3d->drawStart = 0;
	c3d->drawEnd = c3d->texHeight / 2 + SCREENHEIGHT / 2;
	if (c3d->drawEnd >= SCREENHEIGHT)
		c3d->drawEnd = SCREENHEIGHT - 1;
	y = c3d->drawStart;
	while (y < c3d->drawEnd)
	{
		c3d->texY = (int)(((y - SCREENHEIGHT / 2 + c3d->texHeight / 2) * c3d->wallT->height) / c3d->texHeight);
		c3d->color = c3d->wallT->addr[c3d->texY * c3d->wallT->width + c3d->texX];
		c3d->image->addr[y * SCREENWIDTH + x] = c3d->color;
		y++;
	}
}

void	initializing_parameters_raycasting(t_data *c3d, int x)
{
	c3d->cameraX = 2 * x / (double)SCREENWIDTH - 1;
	c3d->rayDirX = c3d->dirX + c3d->planeX * c3d->cameraX;
	c3d->rayDirY = c3d->dirY + c3d->planeY * c3d->cameraX;
	c3d->mapX = (int)c3d->posX;
	c3d->mapY = (int)c3d->posY;
	if (c3d->rayDirX == 0)
		c3d->deltaDistX = 1e30;
	else
		c3d->deltaDistX = fabs(1 / c3d->rayDirX);
	if (c3d->rayDirY == 0)
		c3d->deltaDistY = 1e30;
	else
		c3d->deltaDistY = fabs(1 / c3d->rayDirY);
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
	c3d->image->addr = (int *)mlx_get_data_addr(c3d->image->img, &c3d->image->bits_per_pixel, &c3d->image->line_length, &c3d->image->endian);
	floor_ceiling(c3d);
	raycasting_core(c3d);
	mlx_put_image_to_window(c3d->mlx, c3d->win, c3d->image->img, 0, 0);
	mlx_destroy_image(c3d->mlx, c3d->image->img);
	free(c3d->image);
	bear_claws(c3d);
}
