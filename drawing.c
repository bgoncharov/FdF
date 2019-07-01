/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogoncha <bogoncha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 16:55:04 by bogoncha          #+#    #+#             */
/*   Updated: 2019/07/01 16:43:55 by bogoncha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	proj(t_mlx *mlx, int *xyz)
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
		mlx->p.x1 = mlx->p.offset_x + (c * xyz[0] - c * xyz[1])
			/ 10;
		mlx->p.x2 = mlx->p.offset_x + (c * xyz[3] - c * xyz[4])
			/ 10;
		mlx->p.y1 = mlx->p.offset_y - xyz[2] + ((c / 2) * xyz[0]
				+ (c / 2) * xyz[1]) / 10;
		mlx->p.y2 = mlx->p.offset_y - xyz[5] + ((c / 2) * xyz[3]
				+ (c / 2) * xyz[4]) / 10;
	}
	if (xyz[2] != 0 || xyz[5] != 0)
		line(mlx, 16761035);
	else
		line(mlx, 65535);
}

int			get_addr(t_mlx *mlx, int i)
{
	int addr;
	int x;
	int y;

	addr = 0;
	if ((mlx->p.x2 - mlx->p.x1) >= (mlx->p.y2 - mlx->p.y1))
	{
		x = i;
		y = (mlx->p.y1 + ((mlx->p.y2 - mlx->p.y1)
				* (x - mlx->p.x1)) / (mlx->p.x2 - mlx->p.x1));
		if ((mlx->p.x2 - mlx->p.x1) != 0)
			addr = WIN_WIDTH * y + x;
	}
	else if ((mlx->p.y2 - mlx->p.y1) > (mlx->p.x2 - mlx->p.x1))
	{
		y = i;
		x = (mlx->p.x1 + ((mlx->p.x2 - mlx->p.x1)
				* (y - mlx->p.y1)) / (mlx->p.y2 - mlx->p.y1));
		printf("y 2 : %d", y);
		printf("x 2 : %d\n", x);
		if ((mlx->p.y2 - mlx->p.y1) != 0)
			addr = WIN_WIDTH * y + x;
	}
	if (addr <= 0 || addr > (WIN_WIDTH * WIN_HEIGHT))
		return (0);
	return (addr);
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

void	line(t_mlx *mlx, int color)
{
	int		x;
	int		y;

	if (mlx->p.x1 > mlx->p.x2)
		swap_xy(&(mlx->p.x1), &(mlx->p.x2), &(mlx->p.y1), &(mlx->p.y2));
	if ((mlx->p.x2 - mlx->p.x1) >= (mlx->p.y2 - mlx->p.y1))
	{
		x = mlx->p.x1;
		y = mlx->p.y1;
		while (x <= mlx->p.x2)
		{
			if (((x > 0 && x < WIN_WIDTH) || (mlx->p.x2 > 0 && mlx->p.x2 < WIN_WIDTH)) && ((y > 0 && y < WIN_WIDTH) || (mlx->p.y2 > 0 && mlx->p.y2 < WIN_WIDTH)))
				mlx->img.data[get_addr(mlx, x)] = color;
			x++;
		}
	}
	else if ((mlx->p.y2 - mlx->p.y1) > (mlx->p.x2 - mlx->p.x1))
	{
		y = mlx->p.y1;
		x = mlx->p.x1;
		while (y <= mlx->p.y2)
		{
			if (((x > 0 && x < WIN_WIDTH) || (mlx->p.x2 > 0 && mlx->p.x2 < WIN_WIDTH)) && ((y > 0 && y < WIN_WIDTH) || (mlx->p.y2 > 0 && mlx->p.y2 < WIN_WIDTH)))
				mlx->img.data[get_addr(mlx, y)] = color;
			y++;
		}
	}
}

void		init_map(t_mlx *mlx)
{
	int		x;
	int		y;

	if (mlx->init == 0)
	{
		define_gap(mlx);
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