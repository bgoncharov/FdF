/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogoncha <bogoncha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 21:08:18 by bogoncha          #+#    #+#             */
/*   Updated: 2019/06/11 21:12:42 by bogoncha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <stdlib.h>
# include "minilibx/mlx.h"
# include "libft/libft.h"
# include "libft/get_next_line.h"
# include <fcntl.h>

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

typedef struct		s_line
{
	char			**str;
	int				x_str;
	int				y_str;
	struct s_line	*next;
}					t_line;

typedef struct		s_parse
{
	int				**tab;
	int				x_tab;
	int				y_tab;
}					t_parse;

#endif