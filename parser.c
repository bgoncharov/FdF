/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogoncha <bogoncha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 20:05:01 by bogoncha          #+#    #+#             */
/*   Updated: 2019/06/24 18:31:54 by bogoncha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_line		*get_map(int fd)
{
	int		i;
	char	*line;
	t_line	*lst;
	t_line	*begin;

	if (!(lst = malloc(sizeof(t_line))))
		return (0);
	begin = lst;
	while (get_next_line(fd, &line) == 1)
	{
		if (!(lst->str = ft_strsplit(line, ' ')))
			return (0);
		i = 0;
		while (lst->str[i])
			i++;
		lst->x_str = i;
		if (!(lst->next = malloc(sizeof(t_line))))
			return (0);
		lst = lst->next;
		lst->str = NULL;
		free(line);
	}
	lst->next = NULL;
	return (begin);
}

void		error_map(int index)
{
	if (index == 0)
		write(2, "Error: The map is invalid\n", 26);
	if (index == 1)
		write(2, "Error: Wrong memory allocation\n", 31);
	exit(1);
}

int			check_map(t_line *line)
{
	t_line	*tmp;
	int		nb_line;

	tmp = line;
	nb_line = 0;
	while (tmp->next)
	{
		if (line->x_str != tmp->x_str)
			error_map(0);
		tmp = tmp->next;
		nb_line++;
	}
	return (nb_line);
}

int			free_list(t_line *line)
{
	int		i;

	if (line->next != NULL)
		free_list(line->next);
	i = 0;
	while (line->str && line->str[i])
	{
		free(line->str[i]);
		i++;
	}
	if (line->str)
		free(line->str);
	if (line)
		free(line);
	return (0);
}

t_parse		get_tab(t_line *line)
{
	t_parse	map;
	t_line	*begin;
	int		i;
	int		j;
	int		k;

	if (!line)
		error_map(1);
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
			k = 0;
			while (line->str[i][k])
			{
				if (!ft_isdigit(line->str[i][k]))
					error_map(0);
				k++;
			}
			map.tab[j][i] = atoi(line->str[i]);
			i++;
		}
		j++;
		line = line->next;
	}
	free_list(begin);
	return (map);
}