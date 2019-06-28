/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogoncha <bogoncha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 17:13:36 by bogoncha          #+#    #+#             */
/*   Updated: 2019/06/27 17:38:07 by bogoncha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_exit(t_mlx *mlx)
{
	mlx_destroy_image(mlx->ptr, mlx->img.img_ptr);
	mlx_destroy_window(mlx->ptr, mlx->wdw);
	exit(1);
}

void		ft_close(int fd)
{
	if (close(fd) == -1)
	{
		write(2, "Error: file can't be closed\n", 28);
		exit(1);
	}
}

int			ft_open(char *file)
{
	int		i;
	int		fd;

	i = ft_strlen(file) - 4;
	if (i <= 0 || ft_strcmp(file + i, ".fdf"))
	{
		write(2, "Error: Usage: ./fdf <file.fdf> -p/-i\n", 37);
		exit(1);
	}
	if ((fd = open(file, O_RDONLY)) == -1)
	{
		write(2, "Error: file doesn't exist\n", 26);
		exit(1);
	}
	return (fd);
}

void		ft_init_mlx(t_mlx *mlx)
{
	t_img	img;

	mlx->ptr = mlx_init();
	mlx->wdw = mlx_new_window(mlx->ptr, WIN_WIDTH, WIN_HEIGHT, "FdF");
	img.img_ptr = mlx_new_image(mlx->ptr, WIN_WIDTH, WIN_HEIGHT);
	img.data = (int *)mlx_get_data_addr(img.img_ptr, &(img.bpp), &(img.s_l),
			&(img.endian));
	mlx->img = img;
	mlx->init = 0;
}

int			main(int ac, char **av)
{
	int		fd;
	t_mlx	mlx;

	if (ac == 2 || (ac == 3 && (av[2][1] == 'i' || av[2][1] == 'p')))
	{
		fd = ft_open(av[1]);
		mlx.map = get_tab(get_map(fd));
		ft_close(fd);
		ft_init_mlx(&mlx);
		if (ac == 3)
			mlx.proj = av[2][1];
		else
			mlx.proj = 'i';
		init_map(&mlx);
		mlx_put_image_to_window(mlx.ptr, mlx.wdw, mlx.img.img_ptr, 0, 0);
		mlx_key_hook(mlx.wdw, keyboard, &mlx);
		mlx_hook(mlx.wdw, DESTROYNOTIFY, NOEVENTMASK, ft_exit, &mlx);
		mlx_loop(mlx.ptr);
	}
	else
		write(2, "Usage: ./fdf <file.fdf> -p/-i\n", 30);
	return (0);
}
