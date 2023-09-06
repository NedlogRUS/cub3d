/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 21:39:39 by apanikov          #+#    #+#             */
/*   Updated: 2023/09/05 21:48:39 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int updateCameraPosition(int keycode, t_data *c3d)
{
    if (keycode == 126 || keycode == 13)
    {
        if (c3d->map->map_arr[(int)(c3d->posX + c3d->dirX * c3d->moveSpeed)][(int)c3d->posY] != '1')
            c3d->posX += c3d->dirX * c3d->moveSpeed;
        if (c3d->map->map_arr[(int)c3d->posX][(int)(c3d->posY + c3d->dirY * c3d->moveSpeed)] != '1')
            c3d->posY += c3d->dirY * c3d->moveSpeed;
        raycasting(c3d);
    }
    if (keycode == 125 || keycode == 1) 
    {
        if (c3d->map->map_arr[(int)(c3d->posX - c3d->dirX * c3d->moveSpeed)][(int)c3d->posY] != '1')
            c3d->posX -= c3d->dirX * c3d->moveSpeed;
        if (c3d->map->map_arr[(int)c3d->posX][(int)(c3d->posY - c3d->dirY * c3d->moveSpeed)] != '1')
            c3d->posY -= c3d->dirY * c3d->moveSpeed;
        raycasting(c3d);
    }
	if (keycode == 2)
    {
        if (c3d->map->map_arr[(int)(c3d->posX + c3d->dirY * c3d->moveSpeed)][(int)c3d->posY] != '1')
            c3d->posX += c3d->dirY * c3d->moveSpeed;
        if (c3d->map->map_arr[(int)c3d->posX][(int)(c3d->posY - c3d->dirX * c3d->moveSpeed)] != '1')
            c3d->posY -= c3d->dirX * c3d->moveSpeed;
        raycasting(c3d);
    }
    if (keycode == 0) 
    {
        if (c3d->map->map_arr[(int)(c3d->posX - c3d->dirY * c3d->moveSpeed)][(int)c3d->posY] != '1')
            c3d->posX -= c3d->dirY * c3d->moveSpeed;
        if (c3d->map->map_arr[(int)c3d->posX][(int)(c3d->posY + c3d->dirX * c3d->moveSpeed)] != '1')
            c3d->posY += c3d->dirX * c3d->moveSpeed;
        raycasting(c3d);
    }
    if (keycode == 124) 
    {
        c3d->oldDirX = c3d->dirX;
        c3d->dirX = c3d->dirX * cos(-c3d->rotSpeed) - c3d->dirY * sin(-c3d->rotSpeed);
        c3d->dirY = c3d->oldDirX * sin(-c3d->rotSpeed) + c3d->dirY * cos(-c3d->rotSpeed);
        c3d->oldPlaneX = c3d->planeX;
        c3d->planeX = c3d->planeX * cos(-c3d->rotSpeed) - c3d->planeY * sin(-c3d->rotSpeed);
        c3d->planeY = c3d->oldPlaneX * sin(-c3d->rotSpeed) + c3d->planeY * cos(-c3d->rotSpeed);
        raycasting(c3d);
    }
    if (keycode == 123) 
    {
        c3d->oldDirX = c3d->dirX;
        c3d->dirX = c3d->dirX * cos(c3d->rotSpeed) - c3d->dirY * sin(c3d->rotSpeed);
        c3d->dirY = c3d->oldDirX * sin(c3d->rotSpeed) + c3d->dirY * cos(c3d->rotSpeed);
        c3d->oldPlaneX = c3d->planeX;
        c3d->planeX = c3d->planeX * cos(c3d->rotSpeed) - c3d->planeY * sin(c3d->rotSpeed);
        c3d->planeY = c3d->oldPlaneX * sin(c3d->rotSpeed) + c3d->planeY * cos(c3d->rotSpeed);
        raycasting(c3d);
    }
    return (0);
}

void		inittext(t_data *c3d)
{
	int x = 120;
    int y = 1800;

	c3d->north = malloc(sizeof(t_img));
	c3d->north->img = mlx_xpm_file_to_image(c3d->mlx, c3d->textnorth, &c3d->north->width, &c3d->north->height);
	c3d->west = malloc(sizeof(t_img));
	c3d->west->img = mlx_xpm_file_to_image(c3d->mlx, c3d->textwest, &c3d->west->width, &c3d->west->height);
	c3d->south = malloc(sizeof(t_img));
	c3d->south->img = mlx_xpm_file_to_image(c3d->mlx, c3d->textsouth, &c3d->south->width, &c3d->south->height);
	c3d->east = malloc(sizeof(t_img));
	c3d->east->img = mlx_xpm_file_to_image(c3d->mlx, c3d->texteast, &c3d->east->width, &c3d->east->height);
	c3d->claw_left = mlx_xpm_file_to_image(c3d->mlx, "./sprites/claw_left.xpm", &x, &y);
    c3d->claw_right = mlx_xpm_file_to_image(c3d->mlx, "./sprites/claw_right.xpm", &x, &y);
	if (c3d->north->img == NULL || c3d->west->img == NULL || c3d->south->img == NULL \
	|| c3d->east->img == NULL || c3d->claw_left == NULL || c3d->claw_right == NULL)
		parse_error("Bad texture");
	c3d->south->addr = (int *)mlx_get_data_addr(c3d->south->img, &c3d->south->bits_per_pixel, &c3d->south->line_length, &c3d->south->endian);
	c3d->west->addr = (int *)mlx_get_data_addr(c3d->west->img, &c3d->west->bits_per_pixel, &c3d->west->line_length, &c3d->west->endian);
	c3d->north->addr = (int *)mlx_get_data_addr(c3d->north->img, &c3d->north->bits_per_pixel, &c3d->north->line_length, &c3d->north->endian);
	c3d->east->addr = (int *)mlx_get_data_addr(c3d->east->img, &c3d->east->bits_per_pixel, &c3d->east->line_length, &c3d->east->endian);
	return ;
}

int cubclose(void)
{
    printf("Thanks for playing\n");
    system("leaks cub3D");
    exit(0);
}

int keyhandle(int keycode, t_data *c3d)
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
	|| keycode == 0 || keycode == 1 || keycode == 2 || keycode == 13 )
        updateCameraPosition(keycode, c3d);
    return (0);
}

int	mouse_move(int x, int y, t_data *c3d)
{
	mlx_mouse_hide();
	mlx_mouse_get_pos(c3d->win, &x, &y);
	if (x > SCREENWIDTH / 2)
		updateCameraPosition(124, c3d);
	if (x < SCREENWIDTH / 2)
		updateCameraPosition(123, c3d);
	mlx_mouse_move(c3d->win, SCREENWIDTH / 2, y / 2);
	return (0);
}

void	initorient(t_data *c3d)
{
	if (c3d->map->spawn_orient == 'W')
	{
    c3d->dirX = 0; 
    c3d->dirY = -1;
    c3d->planeX = -0.66; 
    c3d->planeY = 0;
	}
	else if (c3d->map->spawn_orient == 'E')
	{
    c3d->dirX = 0; 
    c3d->dirY = 1;
    c3d->planeX = 0.66; 
    c3d->planeY = 0;
	}
	else if (c3d->map->spawn_orient == 'S')
	{
    c3d->dirX = 1; 
    c3d->dirY = 0;
    c3d->planeX = 0; 
    c3d->planeY = -0.66;
	}
	else if (c3d->map->spawn_orient == 'N')
	{  
	c3d->dirX = -1; 
    c3d->dirY = 0;
    c3d->planeX = 0; 
    c3d->planeY = 0.66;
	}
}

void    claws_util(t_data *c3d)
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
    else if (c3d->stp == 10 || c3d->stp == 11 || c3d->stp == 14 || c3d->stp == 15)
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

int bear_claws(t_data *c3d)
{
    int x;
    int y;
    int xr;
    int yr;

    x = 190;
    y = 400;
    xr = 390;
    yr = 400;
    claws_util(c3d);
    mlx_put_image_to_window(c3d->mlx, c3d->win,\
     c3d->claw_left, x, y + c3d->add_l);
    mlx_put_image_to_window(c3d->mlx, c3d->win, \
    c3d->claw_right, xr, yr +c3d->add_r);
    return (0);
}

int main(int argc, char **argv)
{
    t_data *c3d;
    
    c3d = malloc(sizeof(t_data));
	c3d->map = malloc(sizeof(t_map));
	parsing(c3d->map, argv, argc, c3d);
    c3d->stp = 0;
    c3d->moveSpeed = 0.1;
    c3d->rotSpeed = 0.1;
    c3d->mlx = mlx_init();
    c3d->win = mlx_new_window(c3d->mlx, SCREENWIDTH, SCREENHEIGHT, "cub3D");
	c3d->textnorth = c3d->map->north_path;
	c3d->textwest = c3d->map->west_path;
	c3d->textsouth = c3d->map->south_path; 
	c3d->texteast = c3d->map->east_path;
	initorient(c3d);
	inittext(c3d);
    raycasting(c3d);
	mlx_hook(c3d->win, 2, 1L << 0, keyhandle, c3d);
	mlx_hook(c3d->win, 6, 1L << 6, mouse_move, c3d);
	mlx_hook(c3d->win, 17, 1L << 0, cubclose, c3d);
    mlx_loop(c3d->mlx);
    return 0;
}
