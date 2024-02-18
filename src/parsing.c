/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachtata <yachtata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 04:00:53 by yachtata          #+#    #+#             */
/*   Updated: 2024/02/04 03:31:47 by yachtata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	ft_creat_array(t_var *data, int x, int y, char *split)
{
	t_cpy	*creat;
	int		index;

	index = find_index(x, y, data->max_rows);
	creat = (t_cpy *)malloc(sizeof(t_cpy));
	if (!creat)
	{
		free_list(&(data->head));
		free_2d_array(data->twod_array, data->total);
		exit(1);
	}
	creat->x = x;
	creat->y = y;
	creat->z = ft_atoi(split);
	creat->color = ft_grepcolor(split);
	creat->down = NULL;
	creat->right = NULL;
	if (creat->z > data->max_z)
		data->max_z = creat->z;
	data->twod_array[index] = creat;
	return (0);
}

void	ft_addtoarray(t_var *data, char *str, int columns)
{
	char	**split;
	int		row;

	row = 0;
	split = ft_split(str, ' ');
	while (split[row])
	{
		ft_creat_array(data, row, columns, split[row]);
		row++;
	}
	while (row >= 0)
	{
		free(split[row]);
		row--;
	}
	free(split);
}

void	get_max_columns_rows(t_var *data)
{
	t_line	*current;
	int		i;
	int		row;

	i = 0;
	row = 0;
	data->max_rows = 0;
	data->total = 0;
	current = data->head;
	while (current)
	{
		row = 0;
		i = 0;
		while (current->content[i])
		{
			if (current->content[i] != ' '
				&& (i == 0 || current->content[i - 1] == ' '))
				row++;
			i++;
		}
		data->total += row;
		if (row > data->max_rows)
			data->max_rows = row;
		current = current->next;
	}
}

t_cpy	**ft_cpy_map(t_var *data, char *str)
{
	t_line	*temp;
	int		columns;

	columns = 0;
	creat_list(data, str);
	get_max_columns_rows(data);
	data->twod_array = malloc(sizeof(t_cpy *) * (data->total + 1));
	if (!data->twod_array)
	{
		free_list(&(data->head));
		ft_putstr_fd("Allocation Error\n", 2);
		exit(1);
	}
	temp = data->head;
	while (temp)
	{
		ft_addtoarray(data, temp->content, columns);
		temp = temp->next;
		columns++;
	}
	free_list(&(data->head));
	data->twod_array[data->total] = '\0';
	return (data->twod_array);
}

t_cpy	**check_maps(t_var *data, char *str)
{
	int	len;
	int	file_check;

	len = ft_strlen(str);
	if (len <= 4)
	{
		ft_putstr_fd("Invalid map format should be '.fdf'\n", 2);
		exit(MALLOC_ERROR);
	}
	if (ft_strcmp(".fdf", &str[len - 4]))
	{
		ft_putstr_fd("Invalid map format should be '.fdf'\n", 2);
		exit(MALLOC_ERROR);
	}
	file_check = is_file_empty(str);
	if (file_check)
	{
		ft_putstr_fd("The file is empty.\n", 2);
		exit(EXIT_FAILURE);
	}
	return (ft_cpy_map(data, str));
}
