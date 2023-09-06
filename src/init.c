/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:43:36 by apanikov          #+#    #+#             */
/*   Updated: 2023/09/06 16:46:23 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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

void	initorient_2(t_data *c3d)
{
	if (c3d->map->spawn_orient == 'S')
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
	else
		initorient_2(c3d);
}
