#include "cube3d.h"

char worldMap[mapWidth][mapHeight] =
{
  {'1','1','1','1','1'},
  {'1','0','0','0','1'},
  {'1','0','0','0','1'},
  {'1','0','1','0','1'},
  {'1','0','0','0','1'},
  {'1','0','0','0','1'},
  {'1','1','1','1','1'}
};

void raycasting(t_data *c3d)
{
    mlx_clear_window(c3d->mlx, c3d->win);

    // Draw the ceiling (upper half of the screen)
    for (int y = 0; y < screenHeight / 2; y++)
    {
        for (int x = 0; x < screenWidth; x++)
        {
            mlx_pixel_put(c3d->mlx, c3d->win, x, y, c3d->ceilingColor);
        }
    }
    // Draw the floor (lower half of the screen)
    for (int y = screenHeight / 2; y < screenHeight; y++)
    {
        for (int x = 0; x < screenWidth; x++)
        {
            mlx_pixel_put(c3d->mlx, c3d->win, x, y, c3d->floorColor);
        }
    }
    for (int x = 0; x < screenWidth; x++)
    {
        c3d->cameraX = 2 * x / (double)screenWidth - 1;
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
			if (worldMap[c3d->mapX][c3d->mapY] != '0') 
				c3d->hit = 1;
		}
        if (c3d->side == 0)
            c3d->perpWallDist = (c3d->sideDistX - c3d->deltaDistX);
        else
            c3d->perpWallDist = (c3d->sideDistY - c3d->deltaDistY);
        c3d->lineHeight = (int)(screenHeight / c3d->perpWallDist);
        c3d->drawStart = -c3d->lineHeight / 2 + screenHeight / 2;
        if (c3d->drawStart < 0)
            c3d->drawStart = 0;
        c3d->drawEnd = c3d->lineHeight / 2 + screenHeight / 2;
        if (c3d->drawEnd >= screenHeight)
            c3d->drawEnd = screenHeight - 1;
        if (c3d->side == 1)
        {
            c3d->color = c3d->color / 2;
        }
		
		// Calculate texture coordinates
        if (c3d->side == 0)
            c3d->wallX = c3d->posY + c3d->perpWallDist * c3d->rayDirY;
        else
            c3d->wallX = c3d->posX + c3d->perpWallDist * c3d->rayDirX;
        c3d->wallX -= floor(c3d->wallX);

        // Determine which wall texture to use based on the side
        // t_img *wallT;
        if (c3d->side == 0) // East or West wall
        {
            if (c3d->rayDirX > 0)
                c3d->wallT = c3d->east;
            else
                c3d->wallT = c3d->west;
        }
        else // North or South wall
        {
            if (c3d->rayDirY > 0)
                c3d->wallT = c3d->north;
            else
                c3d->wallT = c3d->south;
        }

        // Calculate texture coordinates based on the wallX
        int texX = (int)(c3d->wallX * (double)c3d->wallT->width);
        if ((c3d->side == 0 && c3d->rayDirX > 0) || (c3d->side == 1 && c3d->rayDirY < 0))
            texX = c3d->wallT->width - texX - 1;

        // Calculate the height of the texture column to draw
        int texHeight = (int)(screenHeight / c3d->perpWallDist);

        // Calculate the starting and ending positions to draw the texture column
        int drawStart = -texHeight / 2 + screenHeight / 2;
        if (drawStart < 0)
            drawStart = 0;
        int drawEnd = texHeight / 2 + screenHeight / 2;
        if (drawEnd >= screenHeight)
            drawEnd = screenHeight - 1;

        // Draw the textured wall column
        for (int y = drawStart; y < drawEnd; y++)
        {
            int texY = (int)(((y - screenHeight / 2 + texHeight / 2) * c3d->wallT->height) / texHeight);
            int color = c3d->wallT->addr[texY * c3d->wallT->width + texX];
            mlx_pixel_put(c3d->mlx, c3d->win, x, y, color);
        }
    }
}

int updateCameraPosition(int keycode, t_data *c3d)
{
    if (keycode == 126)
    {
        if (worldMap[(int)(c3d->posX + c3d->dirX * c3d->moveSpeed)][(int)c3d->posY] == '0')
            c3d->posX += c3d->dirX * c3d->moveSpeed;
        if (worldMap[(int)c3d->posX][(int)(c3d->posY + c3d->dirY * c3d->moveSpeed)] == '0')
            c3d->posY += c3d->dirY * c3d->moveSpeed;
        raycasting(c3d);
    }
    if (keycode == 125) 
    {
        if (worldMap[(int)(c3d->posX - c3d->dirX * c3d->moveSpeed)][(int)c3d->posY] == '0')
            c3d->posX -= c3d->dirX * c3d->moveSpeed;
        if (worldMap[(int)c3d->posX][(int)(c3d->posY - c3d->dirY * c3d->moveSpeed)] == '0')
            c3d->posY -= c3d->dirY * c3d->moveSpeed;
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
	c3d->north = malloc(sizeof(t_img));
	c3d->north->img = mlx_xpm_file_to_image(c3d->mlx, c3d->textnorth, &c3d->north->width, &c3d->north->height);
	c3d->north->addr = (int *)mlx_get_data_addr(c3d->north->img, &c3d->north->bits_per_pixel, &c3d->north->line_length, &c3d->north->endian);
	c3d->west = malloc(sizeof(t_img));
	c3d->west->img = mlx_xpm_file_to_image(c3d->mlx, c3d->textwest, &c3d->west->width, &c3d->west->height);
	c3d->west->addr = (int *)mlx_get_data_addr(c3d->west->img, &c3d->west->bits_per_pixel, &c3d->west->line_length, &c3d->west->endian);
	c3d->south = malloc(sizeof(t_img));
	c3d->south->img = mlx_xpm_file_to_image(c3d->mlx, c3d->textsouth, &c3d->south->width, &c3d->south->height);
	c3d->south->addr = (int *)mlx_get_data_addr(c3d->south->img, &c3d->south->bits_per_pixel, &c3d->south->line_length, &c3d->south->endian);
	c3d->east = malloc(sizeof(t_img));
	c3d->east->img = mlx_xpm_file_to_image(c3d->mlx, c3d->texteast, &c3d->east->width, &c3d->east->height);
	c3d->east->addr = (int *)mlx_get_data_addr(c3d->east->img, &c3d->east->bits_per_pixel, &c3d->east->line_length, &c3d->east->endian);
	return ;
}

int main()
{
    t_data *c3d;
    c3d = malloc(sizeof(t_data));
    c3d->posX = 2;
    c3d->posY = 2;
    c3d->dirX = -1; 
    c3d->dirY = 0;
    c3d->planeX = 0; 
    c3d->planeY = 0.66;
    c3d->moveSpeed = 0.5;
    c3d->rotSpeed = 0.2;
	c3d->floorColor = 0x35960B;
	c3d->ceilingColor = 0x6FA8DC;
    c3d->mlx = mlx_init();
    c3d->win = mlx_new_window(c3d->mlx, screenWidth, screenHeight, "Raycaster");
	c3d->textnorth = ft_strdup("./sprites/NORTH.xpm");
	c3d->textwest = ft_strdup("./sprites/WEST.xpm");
	c3d->textsouth = ft_strdup("./sprites/SOUTH.xpm");
	c3d->texteast = ft_strdup("./sprites/EAST.xpm");
	inittext(c3d);
    raycasting(c3d);  
    mlx_hook(c3d->win, 2, 1L << 0, updateCameraPosition, c3d);
    mlx_loop(c3d->mlx);
    return 0;
}

// char worldMap[mapWidth][mapHeight] =
// {
//   {'1','1','1','1','1'},
//   {'1','0','0','0','1'},
//   {'1','0','0','0','1'},
//   {'1','0','1','0','1'},
//   {'1','0','0','0','1'},
//   {'1','0','0','0','1'},
//   {'1','1','1','1','1'}
// };

// void raycasting(t_data *c3d)
// {
//     mlx_clear_window(c3d->mlx, c3d->win);

//     // Draw the ceiling (upper half of the screen)
//     for (int y = 0; y < screenHeight / 2; y++)
//     {
//         for (int x = 0; x < screenWidth; x++)
//         {
//             mlx_pixel_put(c3d->mlx, c3d->win, x, y, c3d->ceilingColor);
//         }
//     }
//     // Draw the floor (lower half of the screen)
//     for (int y = screenHeight / 2; y < screenHeight; y++)
//     {
//         for (int x = 0; x < screenWidth; x++)
//         {
//             mlx_pixel_put(c3d->mlx, c3d->win, x, y, c3d->floorColor);
//         }
//     }
//     for (int x = 0; x < screenWidth; x++)
//     {
//         c3d->cameraX = 2 * x / (double)screenWidth - 1;
//         c3d->rayDirX = c3d->dirX + c3d->planeX * c3d->cameraX;
//         c3d->rayDirY = c3d->dirY + c3d->planeY * c3d->cameraX;
//         c3d->mapX = (int)c3d->posX;
//         c3d->mapY = (int)c3d->posY;
//         c3d->deltaDistX = (c3d->rayDirX == 0) ? 1e30 : fabs(1 / c3d->rayDirX);
//         c3d->deltaDistY = (c3d->rayDirY == 0) ? 1e30 : fabs(1 / c3d->rayDirY);
//         c3d->hit = 0;

//         if (c3d->rayDirX < 0)
//         {
//             c3d->stepX = -1;
//             c3d->sideDistX = (c3d->posX - c3d->mapX) * c3d->deltaDistX;
//         }
//         else
//         {
//             c3d->stepX = 1;
//             c3d->sideDistX = (c3d->mapX + 1.0 - c3d->posX) * c3d->deltaDistX;
//         }
//         if (c3d->rayDirY < 0)
//         {
//             c3d->stepY = -1;
//             c3d->sideDistY = (c3d->posY - c3d->mapY) * c3d->deltaDistY;
//         }
//         else
//         {
//             c3d->stepY = 1;
//             c3d->sideDistY = (c3d->mapY + 1.0 - c3d->posY) * c3d->deltaDistY;
//         }

// 		while (c3d->hit == 0)
// 		{
// 			if (c3d->sideDistX < c3d->sideDistY)
// 			{
// 				c3d->sideDistX += c3d->deltaDistX;
// 				c3d->mapX += c3d->stepX;
// 				c3d->side = 0;
// 			}
// 			else
// 			{
// 				c3d->sideDistY += c3d->deltaDistY;
// 				c3d->mapY += c3d->stepY;
// 				c3d->side = 1;
// 			}
// 			if (worldMap[c3d->mapX][c3d->mapY] != '0') 
// 				c3d->hit = 1;
// 		}
//         if (c3d->side == 0)
//             c3d->perpWallDist = (c3d->sideDistX - c3d->deltaDistX);
//         else
//             c3d->perpWallDist = (c3d->sideDistY - c3d->deltaDistY);
//         c3d->lineHeight = (int)(screenHeight / c3d->perpWallDist);
//         c3d->drawStart = -c3d->lineHeight / 2 + screenHeight / 2;
//         if (c3d->drawStart < 0)
//             c3d->drawStart = 0;
//         c3d->drawEnd = c3d->lineHeight / 2 + screenHeight / 2;
//         if (c3d->drawEnd >= screenHeight)
//             c3d->drawEnd = screenHeight - 1;
//         if (c3d->side == 1)
//         {
//             c3d->color = c3d->color / 2;
//         }
// 		// Calculate texture coordinates
//         double wallX; // Where exactly the wall was hit
//         if (c3d->side == 0)
//             wallX = c3d->posY + c3d->perpWallDist * c3d->rayDirY;
//         else
//             wallX = c3d->posX + c3d->perpWallDist * c3d->rayDirX;
//         wallX -= floor(wallX);

//         // Calculate texture coordinates based on the wallX
//         int texX = (int)(wallX * (double)c3d->north->width);
//         if ((c3d->side == 0 && c3d->rayDirX > 0) || (c3d->side == 1 && c3d->rayDirY < 0))
//             texX = c3d->north->width - texX - 1;

//         // Calculate the height of the texture column to draw
//         int texHeight = (int)(screenHeight / c3d->perpWallDist);

//         // Calculate the starting and ending positions to draw the texture column
//         int drawStart = -texHeight / 2 + screenHeight / 2;
//         if (drawStart < 0)
//             drawStart = 0;
//         int drawEnd = texHeight / 2 + screenHeight / 2;
//         if (drawEnd >= screenHeight)
//             drawEnd = screenHeight - 1;

//         // Draw the textured wall column
//         for (int y = drawStart; y < drawEnd; y++)
//         {
//             int texY = (int)(((y - screenHeight / 2 + texHeight / 2) * c3d->north->height) / texHeight);
//             int color = c3d->north->addr[texY * c3d->north->width + texX];
//             mlx_pixel_put(c3d->mlx, c3d->win, x, y, color);
//         }
//     }
// }

// int updateCameraPosition(int keycode, t_data *c3d)
// {
//     if (keycode == 126)
//     {
//         if (worldMap[(int)(c3d->posX + c3d->dirX * c3d->moveSpeed)][(int)c3d->posY] == '0')
//             c3d->posX += c3d->dirX * c3d->moveSpeed;
//         if (worldMap[(int)c3d->posX][(int)(c3d->posY + c3d->dirY * c3d->moveSpeed)] == '0')
//             c3d->posY += c3d->dirY * c3d->moveSpeed;
//         raycasting(c3d);
//     }
//     if (keycode == 125) 
//     {
//         if (worldMap[(int)(c3d->posX - c3d->dirX * c3d->moveSpeed)][(int)c3d->posY] == '0')
//             c3d->posX -= c3d->dirX * c3d->moveSpeed;
//         if (worldMap[(int)c3d->posX][(int)(c3d->posY - c3d->dirY * c3d->moveSpeed)] == '0')
//             c3d->posY -= c3d->dirY * c3d->moveSpeed;
//         raycasting(c3d);
//     }
//     if (keycode == 124) 
//     {
//         c3d->oldDirX = c3d->dirX;
//         c3d->dirX = c3d->dirX * cos(-c3d->rotSpeed) - c3d->dirY * sin(-c3d->rotSpeed);
//         c3d->dirY = c3d->oldDirX * sin(-c3d->rotSpeed) + c3d->dirY * cos(-c3d->rotSpeed);
//         c3d->oldPlaneX = c3d->planeX;
//         c3d->planeX = c3d->planeX * cos(-c3d->rotSpeed) - c3d->planeY * sin(-c3d->rotSpeed);
//         c3d->planeY = c3d->oldPlaneX * sin(-c3d->rotSpeed) + c3d->planeY * cos(-c3d->rotSpeed);
//         raycasting(c3d);
//     }
//     if (keycode == 123) 
//     {
//         c3d->oldDirX = c3d->dirX;
//         c3d->dirX = c3d->dirX * cos(c3d->rotSpeed) - c3d->dirY * sin(c3d->rotSpeed);
//         c3d->dirY = c3d->oldDirX * sin(c3d->rotSpeed) + c3d->dirY * cos(c3d->rotSpeed);
//         c3d->oldPlaneX = c3d->planeX;
//         c3d->planeX = c3d->planeX * cos(c3d->rotSpeed) - c3d->planeY * sin(c3d->rotSpeed);
//         c3d->planeY = c3d->oldPlaneX * sin(c3d->rotSpeed) + c3d->planeY * cos(c3d->rotSpeed);
//         raycasting(c3d);
//     }
//     return (0);
// }

// void		inittext(t_data *c3d)
// {
// 	c3d->north = malloc(sizeof(t_img));
// 	c3d->north->img = mlx_xpm_file_to_image(c3d->mlx, c3d->textnorth, &c3d->north->width, &c3d->north->height);
// 	c3d->north->addr = (int *)mlx_get_data_addr(c3d->north->img, &c3d->north->bits_per_pixel, &c3d->north->line_length, &c3d->north->endian);
// 	c3d->west = malloc(sizeof(t_img));
// 	c3d->west->img = mlx_xpm_file_to_image(c3d->mlx, c3d->textwest, &c3d->west->width, &c3d->west->height);
// 	c3d->west->addr = (int *)mlx_get_data_addr(c3d->west->img, &c3d->west->bits_per_pixel, &c3d->west->line_length, &c3d->west->endian);
// 	c3d->south = malloc(sizeof(t_img));
// 	c3d->south->img = mlx_xpm_file_to_image(c3d->mlx, c3d->textsouth, &c3d->south->width, &c3d->south->height);
// 	c3d->south->addr = (int *)mlx_get_data_addr(c3d->south->img, &c3d->south->bits_per_pixel, &c3d->south->line_length, &c3d->south->endian);
// 	c3d->east = malloc(sizeof(t_img));
// 	c3d->east->img = mlx_xpm_file_to_image(c3d->mlx, c3d->texteast, &c3d->east->width, &c3d->east->height);
// 	c3d->east->addr = (int *)mlx_get_data_addr(c3d->east->img, &c3d->east->bits_per_pixel, &c3d->east->line_length, &c3d->east->endian);
// 	return ;
// }

// int main()
// {
//     t_data *c3d;
//     c3d = malloc(sizeof(t_data));
//     c3d->posX = 2;
//     c3d->posY = 2;
//     c3d->dirX = -1; 
//     c3d->dirY = 0;
//     c3d->planeX = 0; 
//     c3d->planeY = 0.66;
//     c3d->moveSpeed = 0.5;
//     c3d->rotSpeed = 0.2;
// 	c3d->floorColor = 0x35960B;
// 	c3d->ceilingColor = 0x6FA8DC;
//     c3d->mlx = mlx_init();
//     c3d->win = mlx_new_window(c3d->mlx, screenWidth, screenHeight, "Raycaster");
// 	c3d->textnorth = ft_strdup("./sprites/NORTH.xpm");
// 	c3d->textwest = ft_strdup("./sprites/WEST.xpm");
// 	c3d->textsouth = ft_strdup("./sprites/SOUTH.xpm");
// 	c3d->texteast = ft_strdup("./sprites/EAST.xpm");
// 	inittext(c3d);
//     raycasting(c3d);  
//     mlx_hook(c3d->win, 2, 1L << 0, updateCameraPosition, c3d);
//     mlx_loop(c3d->mlx);
//     return 0;
// }

// int worldMap[mapWidth][mapHeight] =
// {
//   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
//   {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
//   {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,1},
//   {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,5,0,0,0,0,0,0,1},
//   {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,1},
//   {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {9,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
// };

// // void draw_vertical_line(t_data *c3d, int x)
// // {
// //     int y;

// //     y = c3d->drawStart;
// //     while (y < c3d->drawEnd)
// //     {
// //         mlx_pixel_put(c3d->mlx, c3d->win, x, y, c3d->color);
// //         y++;
// //     }
// // }

// void raycasting(t_data *c3d)
// {
//     mlx_clear_window(c3d->mlx, c3d->win);

//     // Draw the ceiling (upper half of the screen)
//     for (int y = 0; y < screenHeight / 2; y++)
//     {
//         for (int x = 0; x < screenWidth; x++)
//         {
//             mlx_pixel_put(c3d->mlx, c3d->win, x, y, c3d->ceilingColor);
//         }
//     }
//     // Draw the floor (lower half of the screen)
//     for (int y = screenHeight / 2; y < screenHeight; y++)
//     {
//         for (int x = 0; x < screenWidth; x++)
//         {
//             mlx_pixel_put(c3d->mlx, c3d->win, x, y, c3d->floorColor);
//         }
//     }
//     for (int x = 0; x < screenWidth; x++)
//     {
//         c3d->cameraX = 2 * x / (double)screenWidth - 1;
//         c3d->rayDirX = c3d->dirX + c3d->planeX * c3d->cameraX;
//         c3d->rayDirY = c3d->dirY + c3d->planeY * c3d->cameraX;
//         c3d->mapX = (int)c3d->posX;
//         c3d->mapY = (int)c3d->posY;
//         c3d->deltaDistX = (c3d->rayDirX == 0) ? 1e30 : fabs(1 / c3d->rayDirX);
//         c3d->deltaDistY = (c3d->rayDirY == 0) ? 1e30 : fabs(1 / c3d->rayDirY);
//         c3d->hit = 0;

//         if (c3d->rayDirX < 0)
//         {
//             c3d->stepX = -1;
//             c3d->sideDistX = (c3d->posX - c3d->mapX) * c3d->deltaDistX;
//         }
//         else
//         {
//             c3d->stepX = 1;
//             c3d->sideDistX = (c3d->mapX + 1.0 - c3d->posX) * c3d->deltaDistX;
//         }
//         if (c3d->rayDirY < 0)
//         {
//             c3d->stepY = -1;
//             c3d->sideDistY = (c3d->posY - c3d->mapY) * c3d->deltaDistY;
//         }
//         else
//         {
//             c3d->stepY = 1;
//             c3d->sideDistY = (c3d->mapY + 1.0 - c3d->posY) * c3d->deltaDistY;
//         }
//         while (c3d->hit == 0)
//         {
//             if (c3d->sideDistX < c3d->sideDistY)
//             {
//                 c3d->sideDistX += c3d->deltaDistX;
//                 c3d->mapX += c3d->stepX;
//                 c3d->side = 0;
//             }
//             else
//             {
//                 c3d->sideDistY += c3d->deltaDistY;
//                 c3d->mapY += c3d->stepY;
//                 c3d->side = 1;
//             }
//             if (worldMap[c3d->mapX][c3d->mapY] > 0)
//                 c3d->hit = 1;
//         }
//         if (c3d->side == 0)
//             c3d->perpWallDist = (c3d->sideDistX - c3d->deltaDistX);
//         else
//             c3d->perpWallDist = (c3d->sideDistY - c3d->deltaDistY);
//         c3d->lineHeight = (int)(screenHeight / c3d->perpWallDist);
//         c3d->drawStart = -c3d->lineHeight / 2 + screenHeight / 2;
//         if (c3d->drawStart < 0)
//             c3d->drawStart = 0;
//         c3d->drawEnd = c3d->lineHeight / 2 + screenHeight / 2;
//         if (c3d->drawEnd >= screenHeight)
//             c3d->drawEnd = screenHeight - 1;

//         switch (worldMap[c3d->mapX][c3d->mapY])
//         {
//             case 1: c3d->color = 0xFF0000; break; // Red
//             case 2: c3d->color = 0x00FF00; break; // Green
//             case 3: c3d->color = 0x0000FF; break; // Blue
//             case 4: c3d->color = 0xFFFFFF; break; // White
//             default: c3d->color = 0xFFFF00; break; // Yellow
//         }
//         if (c3d->side == 1)
//         {
//             c3d->color = c3d->color / 2;
//         }
// 		// Calculate texture coordinates
//         double wallX; // Where exactly the wall was hit
//         if (c3d->side == 0)
//             wallX = c3d->posY + c3d->perpWallDist * c3d->rayDirY;
//         else
//             wallX = c3d->posX + c3d->perpWallDist * c3d->rayDirX;
//         wallX -= floor(wallX);

//         // Calculate texture coordinates based on the wallX
//         int texX = (int)(wallX * (double)c3d->img->width);
//         if ((c3d->side == 0 && c3d->rayDirX > 0) || (c3d->side == 1 && c3d->rayDirY < 0))
//             texX = c3d->img->width - texX - 1;

//         // Calculate the height of the texture column to draw
//         int texHeight = (int)(screenHeight / c3d->perpWallDist);

//         // Calculate the starting and ending positions to draw the texture column
//         int drawStart = -texHeight / 2 + screenHeight / 2;
//         if (drawStart < 0)
//             drawStart = 0;
//         int drawEnd = texHeight / 2 + screenHeight / 2;
//         if (drawEnd >= screenHeight)
//             drawEnd = screenHeight - 1;

//         // Draw the textured wall column
//         for (int y = drawStart; y < drawEnd; y++)
//         {
//             int texY = (int)(((y - screenHeight / 2 + texHeight / 2) * c3d->img->height) / texHeight);
//             int color = c3d->img->addr[texY * c3d->img->width + texX];
//             mlx_pixel_put(c3d->mlx, c3d->win, x, y, color);
//         }
//         // draw_vertical_line(c3d, x);
//     }
// }

// int updateCameraPosition(int keycode, t_data *c3d)
// {
//     if (keycode == 126) // Up arrow key
//     {
//         if (worldMap[(int)(c3d->posX + c3d->dirX * c3d->moveSpeed)][(int)c3d->posY] == 0)
//             c3d->posX += c3d->dirX * c3d->moveSpeed;
//         if (worldMap[(int)c3d->posX][(int)(c3d->posY + c3d->dirY * c3d->moveSpeed)] == 0)
//             c3d->posY += c3d->dirY * c3d->moveSpeed;
//         raycasting(c3d);
//     }
//     if (keycode == 125) // Down arrow key
//     {
//         if (worldMap[(int)(c3d->posX - c3d->dirX * c3d->moveSpeed)][(int)c3d->posY] == 0)
//             c3d->posX -= c3d->dirX * c3d->moveSpeed;
//         if (worldMap[(int)c3d->posX][(int)(c3d->posY - c3d->dirY * c3d->moveSpeed)] == 0)
//             c3d->posY -= c3d->dirY * c3d->moveSpeed;
//         raycasting(c3d);
//     }
//     if (keycode == 124) // Right arrow key (rotate right)
//     {
//         c3d->oldDirX = c3d->dirX;
//         c3d->dirX = c3d->dirX * cos(-c3d->rotSpeed) - c3d->dirY * sin(-c3d->rotSpeed);
//         c3d->dirY = c3d->oldDirX * sin(-c3d->rotSpeed) + c3d->dirY * cos(-c3d->rotSpeed);
//         c3d->oldPlaneX = c3d->planeX;
//         c3d->planeX = c3d->planeX * cos(-c3d->rotSpeed) - c3d->planeY * sin(-c3d->rotSpeed);
//         c3d->planeY = c3d->oldPlaneX * sin(-c3d->rotSpeed) + c3d->planeY * cos(-c3d->rotSpeed);
//         raycasting(c3d);
//     }
//     if (keycode == 123) // Left arrow key (rotate left)
//     {
//         c3d->oldDirX = c3d->dirX;
//         c3d->dirX = c3d->dirX * cos(c3d->rotSpeed) - c3d->dirY * sin(c3d->rotSpeed);
//         c3d->dirY = c3d->oldDirX * sin(c3d->rotSpeed) + c3d->dirY * cos(c3d->rotSpeed);
//         c3d->oldPlaneX = c3d->planeX;
//         c3d->planeX = c3d->planeX * cos(c3d->rotSpeed) - c3d->planeY * sin(c3d->rotSpeed);
//         c3d->planeY = c3d->oldPlaneX * sin(c3d->rotSpeed) + c3d->planeY * cos(c3d->rotSpeed);
//         raycasting(c3d);
//     }
//     return (0);
// }

// void		inittext(t_data *c3d)
// {
// 	c3d->img = malloc(sizeof(t_img));
// 	c3d->img->img = mlx_xpm_file_to_image(c3d->mlx, c3d->textpath, &c3d->img->width, &c3d->img->height);
// 	c3d->img->addr = (int *)mlx_get_data_addr(c3d->img->img, &c3d->img->bits_per_pixel, &c3d->img->line_length, &c3d->img->endian);
// 	return ;
// }

// int main()
// {
//     t_data *c3d;
//     c3d = malloc(sizeof(t_data));
//     c3d->posX = 15;
//     c3d->posY = 15;
//     c3d->dirX = -1; 
//     c3d->dirY = 0;
//     c3d->planeX = 0; 
//     c3d->planeY = 0.66;
//     c3d->moveSpeed = 0.5;
//     c3d->rotSpeed = 0.2;
// 	c3d->floorColor = 0x35960B;
// 	c3d->ceilingColor = 0x6FA8DC;
//     c3d->mlx = mlx_init();
//     c3d->win = mlx_new_window(c3d->mlx, screenWidth, screenHeight, "Raycaster");
// 	c3d->textpath = ft_strdup("./sprites/wall.xpm");
// 	inittext(c3d);
//     raycasting(c3d);  
//     mlx_hook(c3d->win, 2, 1L << 0, updateCameraPosition, c3d);
//     mlx_loop(c3d->mlx);
//     return 0;
// }
