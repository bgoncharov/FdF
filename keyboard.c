/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogoncha <bogoncha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 16:58:14 by bogoncha          #+#    #+#             */
/*   Updated: 2019/06/27 17:34:13 by bogoncha         ###   ########.fr       */
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
	if (key == 53)
		ft_exit(mlx);
	if (key == 69 || key == 24)
	{
		mlx->p.gap_x += 2;
		mlx->p.gap_y += 2;
	}
	if ((key == 78 || key == 27) && mlx->p.gap_x > 1 && mlx->p.gap_y > 1)
	{
		mlx->p.gap_x -= 2;
		mlx->p.gap_y -= 2;
	}
	if (key == 4 || key == 126)
		mlx->p.gap_z++;
	if (key == 37 || key == 125)
		mlx->p.gap_z--;
	new_img(mlx);
	return (0);
}
