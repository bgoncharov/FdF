/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proj.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogoncha <bogoncha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 17:26:29 by bogoncha          #+#    #+#             */
/*   Updated: 2019/07/01 20:49:31 by bogoncha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			get_addr(t_mlx *mlx, int i)
{
	int addr;
	int x;
	int y;

	addr = 0;
	if (abs(mlx->p.x2 - mlx->p.x1) >= abs(mlx->p.y2 - mlx->p.y1))
	{
		x = i;
		if ((mlx->p.x2 - mlx->p.x1) != 0)
			addr = WIN_WIDTH * (mlx->p.y1 + ((mlx->p.y2 - mlx->p.y1) * (x - mlx->p.x1)) / (mlx->p.x2 - mlx->p.x1)) + x;
	}
	else
	{
		y = i;
		if ((mlx->p.y2 - mlx->p.y1) != 0)
			addr = WIN_WIDTH * y + (mlx->p.x1 + ((mlx->p.x2 - mlx->p.x1) * (y - mlx->p.y1)) / (mlx->p.y2 - mlx->p.y1));
	}
	if (addr <= 0 || addr > (WIN_WIDTH * WIN_HEIGHT))
		return (0);
	return (addr);
}

void		line_x(t_mlx *mlx, int color)
{
	int		x;

	if (mlx->p.x2 < mlx->p.x1)
		swap_xy(&(mlx->p.x1), &(mlx->p.y1), &(mlx->p.x2), &(mlx->p.y2));
	x = mlx->p.x1;
	while (x <= mlx->p.x2)
	{
		mlx->img.data[get_addr(mlx, x)] = color;
		//mlx_pixel_put(mlx->ptr, mlx->wdw, x, mlx->p.y1 + ((mlx->p.y2 - mlx->p.y1) * (x - mlx->p.x1 )) / (mlx->p.x2 - mlx->p.x1), color);
		x++;
	}
}

void		line_y(t_mlx *mlx, int color)
{
	int		y;

	if (mlx->p.y2 < mlx->p.y1)
		swap_xy(&(mlx->p.x1), &(mlx->p.y1), &(mlx->p.x2), &(mlx->p.y2));
	y = mlx->p.y1;
	while (y <= mlx->p.y2)
	{
		//mlx_pixel_put(mlx->ptr, mlx->wdw, mlx->p.x1 + ((mlx->p.x2 - mlx->p.x1) * (y - mlx->p.y1)) / (mlx->p.y2 - mlx->p.y1), y, color);
		mlx->img.data[get_addr(mlx, y)] = color;
		y++;
	}
}

void		proj(t_mlx *mlx, int *xyz)
{
	int		c;

	c = 5;
	if (mlx->proj == 'p')
	{
		mlx->p.x1 = mlx->p.offset_x + xyz[0] + (c * xyz[2]) / 10;
		mlx->p.x2 = mlx->p.offset_x + xyz[3] + (c * xyz[5]) / 10;
		mlx->p.y1 = mlx->p.offset_y + xyz[1] + (c * xyz[2]) / 20;
		mlx->p.y2 = mlx->p.offset_y + xyz[4] + (c * xyz[5]) / 20;
	}
	if (mlx->proj == 'i')
	{
		mlx->p.x1 = mlx->p.offset_x + (c * xyz[0] - c * xyz[1]) / 10;
		mlx->p.x2 = mlx->p.offset_x + (c * xyz[3] - c * xyz[4]) / 10;
		mlx->p.y1 = mlx->p.offset_y - xyz[2] + ((c / 2) * xyz[0]
			+ (c / 2) * xyz[1]) / 10;
		mlx->p.y2 = mlx->p.offset_y - xyz[5] + ((c / 2) * xyz[3]
			+ (c / 2) * xyz[4]) / 10;
	}
	if (abs(mlx->p.x2 - mlx->p.x1) >= abs(mlx->p.y2 - mlx->p.y1))
		line_x(mlx, color(mlx, xyz[2], xyz[5]));
	else
		line_y(mlx, color(mlx, xyz[2], xyz[5]));
}