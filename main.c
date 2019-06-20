/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogoncha <bogoncha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 17:13:36 by bogoncha          #+#    #+#             */
/*   Updated: 2019/06/18 18:10:33 by bogoncha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		ft_exit(void)
{
}

int		keyboard(int key, t_mlx *mlx)
{
	printf("Key:%d\n", key);
	if (key == 53)
	{
		mlx_destroy_window(mlx->ptr, mlx->wdw);
		exit(1);
	}
	if (key == 2)
	{
		mlx_clear_window(mlx->ptr, mlx->wdw);
	}
	if (key == 38 || key == 69 || key == 24)
	{
		mlx->check++;
		mlx->p.gap_x *= 1.1;
		mlx->p.gap_y *= 1.1;
		ft_bzero(mlx->img.data, WIN_WIDTH * WIN_HEIGHT * sizeof(int));
		mlx_clear_window(mlx->ptr, mlx->wdw);
		draw_map(mlx);
		mlx_put_image_to_window(mlx->ptr, mlx->wdw, mlx->img.img_ptr, 0, 0);
	}
	if (key == 40 || key == 27 || key == 78)
	{
		mlx->check++;
		mlx->p.gap_x *= 0.9;
		mlx->p.gap_y *= 0.9;
		mlx_clear_window(mlx->ptr, mlx->wdw);
		ft_bzero(mlx->img.data, WIN_WIDTH * WIN_HEIGHT * sizeof(int));
		draw_map(mlx);
		mlx_put_image_to_window(mlx->ptr, mlx->wdw, mlx->img.img_ptr, 0, 0);
	}
	return (0);
}

int			ft_verif(char *file)
{
	int		i;
	int		fd;

	i = ft_strlen(file) - 4;
	if (i <= 0 || ft_strcmp(file + i, ".fdf"))
	{
		write(2, "Error: Usage: ./fdf <file.fdf> -p/-i\n", 36);
		exit(1);
	}
	if ((fd = open(file, O_RDONLY)) == -1)
	{
		write(2, "Error: file doesn't exist\n", 26);
		exit(1);
	}
	return (fd);
}

int			main(int ac, char **av)
{
	int		fd;
	t_mlx	mlx;
	t_img	img;

	if (ac == 3)
	{
		fd = ft_verif(av[1]);
		mlx.map = get_tab(get_map(fd));
		if (close(fd) == -1)
		{
			write(2, "Error: file can't be closed\n", 28);
			exit(1);
		}
		mlx.proj = av[2][1];
		mlx.ptr = mlx_init();
		mlx.wdw = mlx_new_window(mlx.ptr, WIN_WIDTH, WIN_HEIGHT, "FdF");
		img.img_ptr = mlx_new_image(mlx.ptr, WIN_WIDTH, WIN_HEIGHT);
		img.data = (int *)mlx_get_data_addr(img.img_ptr, &(img.bpp), &(img.s_l), &(img.endian));
		mlx.img = img;
		mlx.check = 0;
		draw_map(&mlx);
		mlx_put_image_to_window(mlx.ptr, mlx.wdw, img.img_ptr, 0, 0);
		mlx_key_hook(mlx.wdw, keyboard, &mlx);
		mlx_loop(mlx.ptr);
	}
	else
		write(2, "Usage: ./fdf <file.fdf> -p/-i\n", 30);
	return (0);
}