/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogoncha <bogoncha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 20:05:01 by bogoncha          #+#    #+#             */
/*   Updated: 2019/06/18 17:21:28 by bogoncha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_line		*get_map(int fd)
{
	int		i;
	char	*line;
	t_line	*list;
	t_line	*begin;

	if (!(list = malloc(sizeof(t_line))))
		return (0);
	begin = list;
	while (get_next_line(fd, &line) == 1)
	{
		if (!(list->str = ft_strsplit(line, ' ')))
			return (0);
		i = 0;
		while (list->str[i])
			i++;
		list->x_str = i;
		list->next = malloc(sizeof(t_line));
		list = list->next;
		list->y_str++;
		free(line);
	}
	list->next = NULL;
	return (begin);
}

int			check_map(t_line *line)
{
	t_line	*temp;
	int		x;
	int		num_line;

	temp = line;
	num_line = 0;
	x = line->x_str;
	while (temp->next)
	{
		if (x != line->x_str)
		{
			write(2, "Error:\nThe file is invalid", 26);
			exit(1);
		}
		temp = temp->next;
		num_line++;
	}
	return (num_line);
}

t_parse		get_tab(t_line *line)
{
	t_parse	map;
	int		i;
	int		j;

	map.y_tab = ft_check_map(line);
	map.x_tab = line->x_str;
	map.tab = malloc(sizeof(int **) * map.y_tab);
	j = 0;
	while (line->next)
	{
		map.tab[j] = malloc(sizeof(int *) * line->x_str);
		i = 0;
		while (i < line->x_str)
		{
			map.tab[j][i] = ft_atoi(line->str[i]);
			i++;
		}
		j++;
		line = line->next;
	}
	map.tab[j] = 0;
	return (map);
}