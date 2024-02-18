/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_pixels.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachtata <yachtata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 06:59:39 by yachtata          #+#    #+#             */
/*   Updated: 2024/02/11 05:00:51 by yachtata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	copy_and_transform_coordinates(t_var *data, t_cpy *src, t_cpy *dest,
		int rotate_buttom)
{
	(void)rotate_buttom;
	ft_memcpy(dest, src, sizeof(t_cpy));
	dest->x *= data->size_line;
	dest->y *= data->size_line;
	dest->z *= data->z_len;
	change_a_y_z(data, &(dest->x), &(dest->y), &(dest->z));
	if (data->last_botton != 97)
		to_isometric(data, &(dest->x), &(dest->y), &(dest->z));
	find_rotation(data, &(dest->x), &(dest->y), &(dest->z));
	if (data->last_botton == 97)
	{
		dest->x -= (data->size_line * data->max_rows) / 2;
		dest->y -= (data->size_line * data->max_columns) / 2;
	}
	dest->y += HEIGHT / 2;
	dest->x += WIDTH / 2;
}

void	connect_right_node(t_var *data, t_cpy *current, t_cpy *right,
		int rotate_buttom)
{
	t_cpy	*right_node;

	right_node = malloc(sizeof(t_cpy));
	if (right_node == NULL)
		free_mem(data);
	right_node->x = 0;
	right_node->y = 0;
	right_node->z = 0;
	right_node->color = 0;
	right_node->down = NULL;
	right_node->right = NULL;
	copy_and_transform_coordinates(data, right, right_node, rotate_buttom);
	bresenham_line(data, current, right_node);
	free(right_node);
}

void	connect_down_node(t_var *data, t_cpy *current, t_cpy *down,
		int rotate_buttom)
{
	t_cpy	*down_node;

	down_node = malloc(sizeof(t_cpy));
	if (down_node == NULL)
		free_mem(data);
	down_node->x = 0;
	down_node->y = 0;
	down_node->z = 0;
	down_node->color = 0;
	down_node->down = NULL;
	down_node->right = NULL;
	copy_and_transform_coordinates(data, down, down_node, rotate_buttom);
	bresenham_line(data, current, down_node);
	if (data->total < 40000 && !data->moves)
		mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
	free(down_node);
}

void	connect_pixels(t_var *data, int rotate_buttom)
{
	int		i;
	t_cpy	*current_cpy;
	t_cpy	**current;

	i = 0;
	current_cpy = malloc(sizeof(t_cpy));
	current = data->twod_array;
	while (i <= data->total)
	{
		copy_and_transform_coordinates(data, current[i], current_cpy,
			rotate_buttom);
		if (current[i]->right != NULL)
			connect_right_node(data, current_cpy, current[i]->right,
				rotate_buttom);
		if (current[i]->down != NULL)
			connect_down_node(data, current_cpy, current[i]->down,
				rotate_buttom);
		while (i < data->total && current[i + 1] == NULL)
			i++;
		i++;
	}
	free(current_cpy);
}
