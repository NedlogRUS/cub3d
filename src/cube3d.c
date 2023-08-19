#include "cube3d.h"

// #define screenWidth 640
// #define screenHeight 480
// #define mapWidth 24
// #define mapHeight 24

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
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
// };

// void	key_hook(int keycode, void *n)
// {
// 		if (keycode == 126) // 'W' key for moving forward
//         {
//             if (worldMap[(int)(posX + dirX * moveSpeed)][(int)posY] == 0)
//                 posX += dirX * moveSpeed;
//             if (worldMap[(int)posX][(int)(posY + dirY * moveSpeed)] == 0)
//                 posY += dirY * moveSpeed;
//         }
//         if (keycode == 125) // 'S' key for moving backward
//         {
//             if (worldMap[(int)(posX - dirX * moveSpeed)][(int)posY] == 0)
//                 posX -= dirX * moveSpeed;
//             if (worldMap[(int)posX][(int)(posY - dirY * moveSpeed)] == 0)
//                 posY -= dirY * moveSpeed;
//         }
//         if (keycode == 124) // 'D' key for strafing right
//         {
//             double oldDirX = dirX;
//             dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
//             dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
//             double oldPlaneX = planeX;
//             planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
//             planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
//         }
//         if (keycode == 123) // 'A' key for strafing left
//         {
//             double oldDirX = dirX;
//             dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
//             dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
//             double oldPlaneX = planeX;
//             planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
//             planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
//         }
// }

// void draw_vertical_line(void *mlx, void *win, int x, int drawStart, int drawEnd, int color)
// {
//     int y;

//     y = drawStart;
//     while (y < drawEnd)
//     {
//         mlx_pixel_put(mlx, win, x, y, color);
//         y++;
//     }
// }

// int main()
// {
//     void *mlx;
//     void *win;
//     double posX = 22, posY = 12;
//     double dirX = -1, dirY = 0;
//     double planeX = 0, planeY = 0.66;

//     // double time = 0;
//     // double oldTime = 0;
// 	double moveSpeed = 5.0;
//     double rotSpeed = 3.0;

//     mlx = mlx_init();
//     win = mlx_new_window(mlx, screenWidth, screenHeight, "Raycaster");

//     while (1)
//     {
//         for (int x = 0; x < screenWidth; x++)
//         {
//             double cameraX = 2 * x / (double)screenWidth - 1;
//             double rayDirX = dirX + planeX * cameraX;
//             double rayDirY = dirY + planeY * cameraX;
//             int mapX = (int)posX;
//             int mapY = (int)posY;
//             double sideDistX;
//             double sideDistY;
//             double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
//             double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
//             double perpWallDist;
//             int stepX;
//             int stepY;
//             int hit = 0;
//             int side;

//             if (rayDirX < 0)
//             {
//                 stepX = -1;
//                 sideDistX = (posX - mapX) * deltaDistX;
//             }
//             else
//             {
//                 stepX = 1;
//                 sideDistX = (mapX + 1.0 - posX) * deltaDistX;
//             }
//             if (rayDirY < 0)
//             {
//                 stepY = -1;
//                 sideDistY = (posY - mapY) * deltaDistY;
//             }
//             else
//             {
//                 stepY = 1;
//                 sideDistY = (mapY + 1.0 - posY) * deltaDistY;
//             }
//             while (hit == 0)
//             {
//                 if (sideDistX < sideDistY)
//                 {
//                     sideDistX += deltaDistX;
//                     mapX += stepX;
//                     side = 0;
//                 }
//                 else
//                 {
//                     sideDistY += deltaDistY;
//                     mapY += stepY;
//                     side = 1;
//                 }
//                 if (worldMap[mapX][mapY] > 0)
//                     hit = 1;
//             }
//             if (side == 0)
//                 perpWallDist = (sideDistX - deltaDistX);
//             else
//                 perpWallDist = (sideDistY - deltaDistY);
//             int lineHeight = (int)(screenHeight / perpWallDist);
//             int drawStart = -lineHeight / 2 + screenHeight / 2;
//             if (drawStart < 0)
//                 drawStart = 0;
//             int drawEnd = lineHeight / 2 + screenHeight / 2;
//             if (drawEnd >= screenHeight)
//                 drawEnd = screenHeight - 1;
//             int color;
//             switch (worldMap[mapX][mapY])
//             {
//                 case 1: color = 0xFF0000; break; // Red
//                 case 2: color = 0x00FF00; break; // Green
//                 case 3: color = 0x0000FF; break; // Blue
//                 case 4: color = 0xFFFFFF; break; // White
//                 default: color = 0xFFFF00; break; // Yellow
//             }
//             if (side == 1)
//             {
//                 color = color / 2;
//             }
//             draw_vertical_line(mlx, win, x, drawStart, drawEnd, color);
//         }


//         mlx_clear_window(mlx, win);
//         mlx_hook(sl.mlx->win, 2, 1L << 0, key_hook, NULL);
//         mlx_loop(mlx);
//     }

//     return 0;
// }

///////////////////////////////////////////////////
//////////////////////////////////////////////////



// #define screenWidth 640
// #define screenHeight 480
// #define mapWidth 24
// #define mapHeight 24

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
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
// };

// double posX = 22, posY = 12;
// double dirX = -1, dirY = 0;
// double planeX = 0, planeY = 0.66;

// double moveSpeed = 5.0;
// double rotSpeed = 3.0;

// int key_hook(int keycode, void *n)
// {
// 	(void) n;
//     if (keycode == 13) // 'W' key for moving forward (you can adjust this keycode)
//     {
//         if (worldMap[(int)(posX + dirX * moveSpeed)][(int)posY] == 0)
//             posX += dirX * moveSpeed;
//         if (worldMap[(int)posX][(int)(posY + dirY * moveSpeed)] == 0)
//             posY += dirY * moveSpeed;
//     }
//     if (keycode == 1) // 'S' key for moving backward (you can adjust this keycode)
//     {
//         if (worldMap[(int)(posX - dirX * moveSpeed)][(int)posY] == 0)
//             posX -= dirX * moveSpeed;
//         if (worldMap[(int)posX][(int)(posY - dirY * moveSpeed)] == 0)
//             posY -= dirY * moveSpeed;
//     }
//     if (keycode == 2) // 'D' key for strafing right (you can adjust this keycode)
//     {
//         double oldDirX = dirX;
//         dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
//         dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
//         double oldPlaneX = planeX;
//         planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
//         planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
//     }
//     if (keycode == 0) // 'A' key for strafing left (you can adjust this keycode)
//     {
//         double oldDirX = dirX;
//         dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
//         dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
//         double oldPlaneX = planeX;
//         planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
//         planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
//     }
// 	return (0);
// }

// void draw_vertical_line(void *mlx, void *win, int x, int drawStart, int drawEnd, int color)
// {
//     int y;

//     y = drawStart;
//     while (y < drawEnd)
//     {
//         mlx_pixel_put(mlx, win, x, y, color);
//         y++;
//     }
// }

// int main()
// {
//     void *mlx;
//     void *win;

//     mlx = mlx_init();
//     win = mlx_new_window(mlx, screenWidth, screenHeight, "Raycaster");

//     mlx_hook(win, 2, 1L << 0, key_hook, NULL);

//     while (1)
//     {
//         for (int x = 0; x < screenWidth; x++)
//         {
//             double cameraX = 2 * x / (double)screenWidth - 1;
//             double rayDirX = dirX + planeX * cameraX;
//             double rayDirY = dirY + planeY * cameraX;
//             int mapX = (int)posX;
//             int mapY = (int)posY;
//             double sideDistX;
//             double sideDistY;
//             double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
//             double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
//             double perpWallDist;
//             int stepX;
//             int stepY;
//             int hit = 0;
//             int side;

//             if (rayDirX < 0)
//             {
//                 stepX = -1;
//                 sideDistX = (posX - mapX) * deltaDistX;
//             }
//             else
//             {
//                 stepX = 1;
//                 sideDistX = (mapX + 1.0 - posX) * deltaDistX;
//             }
//             if (rayDirY < 0)
//             {
//                 stepY = -1;
//                 sideDistY = (posY - mapY) * deltaDistY;
//             }
//             else
//             {
//                 stepY = 1;
//                 sideDistY = (mapY + 1.0 - posY) * deltaDistY;
//             }
//             while (hit == 0)
//             {
//                 if (sideDistX < sideDistY)
//                 {
//                     sideDistX += deltaDistX;
//                     mapX += stepX;
//                     side = 0;
//                 }
//                 else
//                 {
//                     sideDistY += deltaDistY;
//                     mapY += stepY;
//                     side = 1;
//                 }
//                 if (worldMap[mapX][mapY] > 0)
//                     hit = 1;
//             }
//             if (side == 0)
//                 perpWallDist = (sideDistX - deltaDistX);
//             else
//                 perpWallDist = (sideDistY - deltaDistY);
//             int lineHeight = (int)(screenHeight / perpWallDist);
//             int drawStart = -lineHeight / 2 + screenHeight / 2;
//             if (drawStart < 0)
//                 drawStart = 0;
//             int drawEnd = lineHeight / 2 + screenHeight / 2;
//             if (drawEnd >= screenHeight)
//                 drawEnd = screenHeight - 1;
//             int color;
//             switch (worldMap[mapX][mapY])
//             {
//                 case 1: color = 0xFF0000; break; // Red
//                 case 2: color = 0x00FF00; break; // Green
//                 case 3: color = 0x0000FF; break; // Blue
//                 case 4: color = 0xFFFFFF; break; // White
//                 default: color = 0xFFFF00; break; // Yellow
//             }
//             if (side == 1)
//             {
//                 color = color / 2;
//             }
//             draw_vertical_line(mlx, win, x, drawStart, drawEnd, color);
//     }

//         mlx_clear_window(mlx, win);
//         mlx_loop(mlx);
//     }

//     return 0;
// }







///////////

#define screenWidth 640
#define screenHeight 480
#define mapWidth 24
#define mapHeight 24

typedef struct s_data
{
	void	*mlx;
	void	*win;
}				t_data;

int worldMap[mapWidth][mapHeight] =
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

double posX = 12, posY = 12;
double dirX = -1, dirY = 0;
double planeX = 0, planeY = 0.66;

double moveSpeed = 0.1;
double rotSpeed = 0.05;


void draw_vertical_line(void *mlx, void *win, int x, int drawStart, int drawEnd, int color)
{
    int y;

    y = drawStart;
    while (y < drawEnd)
    {
        mlx_pixel_put(mlx, win, x, y, color);
        y++;
    }
}


void raycasting(void *mlx, void *win)
{
        for (int x = 0; x < screenWidth; x++)
        {
            double cameraX = 2 * x / (double)screenWidth - 1;
            double rayDirX = dirX + planeX * cameraX;
            double rayDirY = dirY + planeY * cameraX;
            int mapX = (int)posX;
            int mapY = (int)posY;
            double sideDistX;
            double sideDistY;
            double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
            double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
            double perpWallDist;
            int stepX;
            int stepY;
            int hit = 0;
            int side;

            if (rayDirX < 0)
            {
                stepX = -1;
                sideDistX = (posX - mapX) * deltaDistX;
            }
            else
            {
                stepX = 1;
                sideDistX = (mapX + 1.0 - posX) * deltaDistX;
            }
            if (rayDirY < 0)
            {
                stepY = -1;
                sideDistY = (posY - mapY) * deltaDistY;
            }
            else
            {
                stepY = 1;
                sideDistY = (mapY + 1.0 - posY) * deltaDistY;
            }
            while (hit == 0)
            {
                if (sideDistX < sideDistY)
                {
                    sideDistX += deltaDistX;
                    mapX += stepX;
                    side = 0;
                }
                else
                {
                    sideDistY += deltaDistY;
                    mapY += stepY;
                    side = 1;
                }
                if (worldMap[mapX][mapY] > 0)
                    hit = 1;
            }
            if (side == 0)
                perpWallDist = (sideDistX - deltaDistX);
            else
                perpWallDist = (sideDistY - deltaDistY);
            int lineHeight = (int)(screenHeight / perpWallDist);
            int drawStart = -lineHeight / 2 + screenHeight / 2;
            if (drawStart < 0)
                drawStart = 0;
            int drawEnd = lineHeight / 2 + screenHeight / 2;
            if (drawEnd >= screenHeight)
                drawEnd = screenHeight - 1;
            int color;
            switch (worldMap[mapX][mapY])
            {
                case 1: color = 0xFF0000; break; // Red
                case 2: color = 0x00FF00; break; // Green
                case 3: color = 0x0000FF; break; // Blue
                case 4: color = 0xFFFFFF; break; // White
                default: color = 0xFFFF00; break; // Yellow
            }
            if (side == 1)
            {
                color = color / 2;
            }
			// mlx_clear_window(mlx, win);
            draw_vertical_line(mlx, win, x, drawStart, drawEnd, color);
		}
}

int updateCameraPosition(int keycode, t_data *c3d)
{
    if (keycode == 126)
    {
        if (worldMap[(int)(posX + dirX * moveSpeed)][(int)posY] == 0)
            posX += dirX * moveSpeed;
        if (worldMap[(int)posX][(int)(posY + dirY * moveSpeed)] == 0)
            posY += dirY * moveSpeed;
		printf("Keycode : %d\n", keycode);
		// raycasting(c3d->mlx, c3d->win);
    }
    if (keycode == 125)
    {
        if (worldMap[(int)(posX - dirX * moveSpeed)][(int)posY] == 0)
            posX -= dirX * moveSpeed;
        if (worldMap[(int)posX][(int)(posY - dirY * moveSpeed)] == 0)
            posY -= dirY * moveSpeed;
		printf("Keycode : %d\n", keycode);
		// raycasting(c3d->mlx, c3d->win);
    }
    if (keycode == 124)
    {
        double oldDirX = dirX;
        dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
        dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
        double oldPlaneX = planeX;
        planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
        planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
		printf("Keycode : %d\n", keycode);
		// raycasting(c3d->mlx, c3d->win);
    }
    if (keycode == 123)
    {
        double oldDirX = dirX;
        dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
        dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
        double oldPlaneX = planeX;
        planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
        planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
		printf("Keycode : %d\n", keycode);
		// raycasting(c3d->mlx, c3d->win);
    }
	raycasting(c3d->mlx, c3d->win);
	return (0);
}

int main()
{
	t_data *c3d;
    // void *mlx;
    // void *win;
	c3d = malloc(sizeof(t_data));

    c3d->mlx = mlx_init();
    c3d->win = mlx_new_window(c3d->mlx, screenWidth, screenHeight, "Raycaster");
    raycasting(c3d->mlx, c3d->win);  
	mlx_hook(c3d->win, 2, 1L << 0, updateCameraPosition, &c3d);
    mlx_loop(c3d->mlx);
    return 0;
}