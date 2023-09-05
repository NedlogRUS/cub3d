#include "cube3d.h"

int cubclose(void)
{
    printf("Thanks for playing\n");
    system("leaks cub3D");
    exit(0);
}

void draw_vertical_line(t_data *c3d, int x)
{
    int y;

    y = c3d->drawStart;
    while (y < c3d->drawEnd)
    {
        mlx_pixel_put(c3d->mlx, c3d->win, x, y, c3d->color);
        y++;
    }
}

void raycasting(t_data *c3d)
{
    mlx_clear_window(c3d->mlx, c3d->win);

    // Draw the ceiling (upper half of the screen)
    for (int y = 0; y < SCREENHEIGHT / 2; y++)
    {
        for (int x = 0; x < SCREENWIDTH; x++)
        {
            mlx_pixel_put(c3d->mlx, c3d->win, x, y, c3d->ceilingColor);
        }
    }
    // Draw the floor (lower half of the screen)
    for (int y = SCREENHEIGHT / 2; y < SCREENHEIGHT; y++)
    {
        for (int x = 0; x < SCREENWIDTH; x++)
        {
            mlx_pixel_put(c3d->mlx, c3d->win, x, y, c3d->floorColor);
        }
    }
    for (int x = 0; x < SCREENWIDTH; x++)
    {
        c3d->cameraX = 2 * x / (double)SCREENWIDTH - 1;
        c3d->rayDirX = c3d->dirX + c3d->planeX * c3d->cameraX;
        c3d->rayDirY = c3d->dirY + c3d->planeY * c3d->cameraX;
        c3d->mapX = (int)c3d->posX;
        c3d->mapY = (int)c3d->posY;
        c3d->deltaDistX = (c3d->rayDirX == 0) ? 1e30 : fabs(1 / c3d->rayDirX);
        c3d->deltaDistY = (c3d->rayDirY == 0) ? 1e30 : fabs(1 / c3d->rayDirY);
        c3d->hit = 0;

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
            if (c3d->map->int_arr[c3d->mapX][c3d->mapY] > 0)
                c3d->hit = 1;
        }
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

        switch (c3d->map->int_arr[c3d->mapX][c3d->mapY])
        {
            case 1: c3d->color = 0xFF0000; break; // Red
            case 2: c3d->color = 0x00FF00; break; // Green
            case 3: c3d->color = 0x0000FF; break; // Blue
            case 4: c3d->color = 0xFFFFFF; break; // White
            default: c3d->color = 0xFFFF00; break; // Yellow
        }
        if (c3d->side == 1)
        {
            c3d->color = c3d->color / 2;
        }

        draw_vertical_line(c3d, x);
    }
}


int updateCameraPosition(int keycode, t_data *c3d)
{
    if (keycode == 126) // Up arrow key
    {
        if (c3d->map->int_arr[(int)(c3d->posX + c3d->dirX * c3d->moveSpeed)][(int)c3d->posY] == 0)
            c3d->posX += c3d->dirX * c3d->moveSpeed;
        if (c3d->map->int_arr[(int)c3d->posX][(int)(c3d->posY + c3d->dirY * c3d->moveSpeed)] == 0)
            c3d->posY += c3d->dirY * c3d->moveSpeed;
        raycasting(c3d);
    }
    if (keycode == 125) // Down arrow key
    {
        if (c3d->map->int_arr[(int)(c3d->posX - c3d->dirX * c3d->moveSpeed)][(int)c3d->posY] == 0)
            c3d->posX -= c3d->dirX * c3d->moveSpeed;
        if (c3d->map->int_arr[(int)c3d->posX][(int)(c3d->posY - c3d->dirY * c3d->moveSpeed)] == 0)
            c3d->posY -= c3d->dirY * c3d->moveSpeed;
        raycasting(c3d);
    }
    if (keycode == 124) // Right arrow key (rotate right)
    {
        c3d->oldDirX = c3d->dirX;
        c3d->dirX = c3d->dirX * cos(-c3d->rotSpeed) - c3d->dirY * sin(-c3d->rotSpeed);
        c3d->dirY = c3d->oldDirX * sin(-c3d->rotSpeed) + c3d->dirY * cos(-c3d->rotSpeed);
        c3d->oldPlaneX = c3d->planeX;
        c3d->planeX = c3d->planeX * cos(-c3d->rotSpeed) - c3d->planeY * sin(-c3d->rotSpeed);
        c3d->planeY = c3d->oldPlaneX * sin(-c3d->rotSpeed) + c3d->planeY * cos(-c3d->rotSpeed);
        raycasting(c3d);
    }
    if (keycode == 123) // Left arrow key (rotate left)
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

int keyhandle(int keycode, t_data *c3d)
{
    if (keycode == 53)
        cubclose();
    if (keycode == 126 || keycode == 125 || keycode == 124 || keycode == 123)
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

int main(int argc, char **argv)
{
    t_data  *c3d;
    t_map   *map;

    c3d = malloc(sizeof(t_data));
    map = malloc(sizeof(t_map));
    c3d->map = map;
    parsing(map, argv, argc, c3d);
    c3d->dirX = 0;
    c3d->dirY = 1;
    c3d->planeX = 0.66;
    c3d->planeY = 0;
    c3d->moveSpeed = 0.3;
    c3d->rotSpeed = 0.1;
    c3d->mlx = mlx_init();
    c3d->win = mlx_new_window(c3d->mlx, SCREENWIDTH, SCREENHEIGHT, "Raycaster");
    raycasting(c3d);
    mlx_hook(c3d->win, 2, 1L << 0, keyhandle, c3d);
    mlx_hook(c3d->win, 17, 1L << 0, cubclose, c3d);
    mlx_hook(c3d->win, 6, 1L << 6, mouse_move, c3d);
    mlx_loop(c3d->mlx);
    return 0;
}
