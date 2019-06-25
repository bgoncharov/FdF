/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogoncha <bogoncha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 20:05:01 by bogoncha          #+#    #+#             */
/*   Updated: 2019/06/24 17:02:21 by bogoncha         ###   ########.fr       */
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
	t_line	*tmp;
	int		x;
	int		nb_line;

	tmp = line;
	nb_line = 0;
	x = line->x_str;
	while (tmp->next)
	{
		if (x != tmp->x_str)
		{
			write(2, "Error: The file is invalid\n", 27);
			exit(1);
		}
		tmp = tmp->next;
		nb_line++;
	}
	return (nb_line);
}

int			free_list(t_line *line)
{
	int		i;

	printf("%p ", line->next);
	if (line->next->next != NULL)
		free_list(line->next);
	i = 0;
	printf("str:%p\n", line->str);
	printf("stri:%s\n", line->str[0]);
	while (line->str && line->str[i])
	{
		printf("%s:", line->str[i]);
		free(line->str[i]);
		i++;
	}
	return (0);
}

t_parse		get_tab(t_line *line)
{
	t_parse	map;
	t_line	*begin;
	int		i;
	int		j;

	begin = line;
	map.y_tab = check_map(line);
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
	free_list(begin);
	return (map);
}