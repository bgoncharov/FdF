/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogoncha <bogoncha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 16:55:04 by bogoncha          #+#    #+#             */
/*   Updated: 2019/06/25 18:03:56 by bogoncha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	proj(t_mlx *mlx, int *xyz)
{
	int		c;

	c = 5;
	if (mlx->proj == 'p')
	{
		mlx->p.x1 = mlx->p.gap_x + xyz[0] + (c * xyz[2]) / 10;
		mlx->p.x2 = mlx->p.gap_x + xyz[3] + (c * xyz[5]) / 10;
		mlx->p.y1 = mlx->p.gap_y + xyz[1] + (c * xyz[2]) / 20;
		mlx->p.y2 = mlx->p.gap_y + xyz[4] + (c * xyz[5]) / 20;
	}
	if (mlx->proj == 'i')
	{
		mlx->p.x1 = (WIN_WIDTH * 2) / 5 + (c * xyz[0] - c * xyz[1])
		/ 10;
		mlx->p.x2 = (WIN_WIDTH * 2) / 5 + (c * xyz[3] - c * xyz[4])
		/ 10;
		mlx->p.y1 = WIN_HEIGHT / 5 - xyz[2] + ((c / 2) * xyz[0]
		+ (c / 2) * xyz[1]) / 10;
		mlx->p.y2 = WIN_HEIGHT / 5 - xyz[5] + ((c / 2) * xyz[3]
		+ (c / 2) * xyz[4]) / 10;
	}
	if (xyz[2] > 0 || xyz[5] > 0)
		line(mlx, 16761035);
	else
		line(mlx, 65535);
}

void		draw_map(t_mlx *mlx)
{
	int		x;
	int		y;
	int		xyz[6];

	if (mlx->check == 0)
	{
		mlx->p.gap_x = WIN_WIDTH / (mlx->map.x_tab + 1);
		mlx->p.gap_y = WIN_HEIGHT / (mlx->map.y_tab + 1);
		mlx->p.gap_z = (mlx->p.gap_x + mlx->p.gap_y) / 10;
	}
	y = 0;
	while (y < mlx->map.y_tab)
	{
		x = 0;
		while (x < mlx->map.x_tab)
		{
			xyz[0] = x * mlx->p.gap_x;
			xyz[1] = y * mlx->p.gap_y;
			xyz[2] = mlx->map.tab[y][x] * mlx->p.gap_z;
			if (x < (mlx->map.x_tab - 1))
			{
				xyz[3] = (x + 1) * mlx->p.gap_x;
				xyz[4] = y * mlx->p.gap_y;
				xyz[5] = mlx->map.tab[y][x + 1] * mlx->p.gap_z;
				proj(mlx, xyz);
			}
			if (y < (mlx->map.y_tab - 1))
			{
				xyz[3] = x * mlx->p.gap_x;
				xyz[4] = (y + 1) * mlx->p.gap_y;
				xyz[5] = mlx->map.tab[y + 1][x] * mlx->p.gap_z;
				proj(mlx, xyz);
			}
			x++;
		}
		y++;
	}
}

void	swap_xy(int *x1, int *x2, int *y1, int *y2)
{
	int		tmp;

	tmp = *x2;
	*x2 = *x1;
	*x1 = tmp;
	tmp = *y2;
	*y2 = *y1;
	*y1 = tmp;
}

void	line(t_mlx *mlx, int color)
{
	int		x;
	int		y;

	if (mlx->p.x1 > mlx->p.x2)
		swap_xy(&(mlx->p.x1), &(mlx->p.x2), &(mlx->p.y1), &(mlx->p.y2));
	if ((mlx->p.x2 - mlx->p.x1) > (mlx->p.y2 - mlx->p.y1))
	{
		x = mlx->p.x1;
		while (x <= mlx->p.x2)
		{
			mlx->img.data[WIN_WIDTH * (mlx->p.y1 + ((mlx->p.y2 - mlx->p.y1) *
			(x - mlx->p.x1)) / (mlx->p.x2 - mlx->p.x1)) + x] = color;
			x++;
		}
	}
	else if ((mlx->p.y2 - mlx->p.y1) > (mlx->p.x2 - mlx->p.x1))
	{
		y = mlx->p.y1;
		while (y <= mlx->p.y2)
		{
			mlx->img.data[WIN_WIDTH * y + (mlx->p.x1 + ((mlx->p.x2 - mlx->p.x1)
			* (y - mlx->p.y1)) / (mlx->p.y2 - mlx->p.y1))] = color;
			y++;
		}
	}
}

void		xyz(t_mlx *mlx, int x, int y)
{
	int xyz[6];

	xyz[0] = x * mlx->p.gap_x;
	xyz[1] = y * mlx->p.gap_y;
	xyz[2] = mlx->map.tab[y][x] * mlx->p.gap_z;
	if (x < (mlx->map.x_tab - 1))
	{
		xyz[3] = (x + 1) * mlx->p.gap_x;
		xyz[4] = y * mlx->p.gap_y;
		xyz[5] = mlx->map.tab[y][x + 1] * mlx->p.gap_z;
		proj(mlx, xyz);
	}
	if (y < (mlx->map.y_tab - 1))
	{
		xyz[3] = x * mlx->p.gap_x;
		xyz[4] = (y + 1) * mlx->p.gap_y;
		xyz[5] = mlx->map.tab[y + 1][x] * mlx->p.gap_z;
		proj(mlx, xyz);
	}
}

void		init_map(t_mlx *mlx)
{
	int		x;
	int		y;

	if (mlx->init == 0)
	{
		mlx->p.gap_x = WIN_WIDTH / (mlx->map.x_tab + 1);
		mlx->p.gap_y = WIN_HEIGHT / (mlx->map.y_tab + 1);
		mlx->p.gap_z = (mlx->p.gap_x + mlx->p.gap_y) / 12;
		mlx->init = 1;
	}
	if (mlx->p.gap_x == 0)
	       	mlx->p.gap_x = 1;
	if (mlx->p.gap_y == 0)
	       	mlx->p.gap_y = 1;
	y = 0;
	while (y < mlx->map.y_tab)
	{
		x = 0;
		while (x < mlx->map.x_tab)
		{
			xyz(mlx, x, y);
			x++;
		}
		y++;
	}
}