/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_ults.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachtata <yachtata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 04:14:49 by yachtata          #+#    #+#             */
/*   Updated: 2024/01/25 04:15:37 by yachtata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static int	ft_add_node(t_line **lst, const char *content)
{
	t_line	*crnt;
	t_line	*prev;
	t_line	*creat;

	if (!lst || !content)
		return (0);
	creat = (t_line *)malloc(sizeof(t_line));
	if (!creat)
		return (0);
	creat->content = (char *)content;
	creat->next = NULL;
	if (!*lst)
	{
		*lst = creat;
		return (1);
	}
	crnt = *lst;
	while (crnt)
	{
		prev = crnt;
		crnt = crnt->next;
	}
	prev->next = creat;
	return (1);
}

void	creat_list(t_var *data, char *str)
{
	int		fd;
	char	*temp;
	int		colomns;

	colomns = 0;
	fd = open(str, O_RDONLY);
	temp = get_next_line(fd);
	while (temp)
	{
		ft_add_node(&(data->head), temp);
		temp = get_next_line(fd);
		colomns++;
	}
	data->max_columns = colomns;
	close(fd);
}

t_cpy	*get_right_node(t_var *data, int x, int y)
{
	int	index;

	index = find_index(x + 1, y, data->max_rows);
	if (x >= data->max_rows - 1)
		return (NULL);
	if (index < data->total && data->twod_array[index])
		return (data->twod_array[index]);
	return (NULL);
}

t_cpy	*get_down_node(t_var *data, int x, int y)
{
	int	index;

	index = find_index(x, y + 1, data->max_rows);
	if (y >= data->max_columns - 1)
		return (NULL);
	if (index < data->total && data->twod_array[index])
		return (data->twod_array[index]);
	return (NULL);
}

void	link_nodes(t_var *data, t_cpy **two_array)
{
	int	i;

	i = 0;
	while (two_array[i] != NULL)
	{
		two_array[i]->down = get_down_node(data, two_array[i]->x,
				two_array[i]->y);
		two_array[i]->right = get_right_node(data, two_array[i]->x,
				two_array[i]->y);
		i++;
	}
}
