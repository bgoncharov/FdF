/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogoncha <bogoncha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 16:58:14 by bogoncha          #+#    #+#             */
/*   Updated: 2019/06/24 18:32:24 by bogoncha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	new_img(t_mlx *mlx)
{
	ft_bzero(mlx->img.data, WIN_WIDTH * WIN_HEIGHT * sizeof(int));
	mlx_clear_window(mlx->ptr, mlx->wdw);
	init_map(mlx);
	mlx_put_image_to_window(mlx->ptr, mlx->wdw, mlx->img.img_ptr, 0, 0);
}

int			keyboard(int key, t_mlx *mlx)
{
	printf("Key:%d\n", key);
	if (key == 53)
		ft_exit(mlx);
	if (key == 69 || key == 24)
	{
		mlx->p.gap_x *= 1.1;
		mlx->p.gap_y *= 1.1;
	}
	if (key == 78 || key == 27)
	{
		mlx->p.gap_x *= 0.9;
		mlx->p.gap_y *= 0.9;
	}
	if (key == 4 || key == 126)
		mlx->p.gap_z += 1;
	if (key == 37 || key == 125)
		mlx->p.gap_z -= 1;
	new_img(mlx);
	return (0);
}
