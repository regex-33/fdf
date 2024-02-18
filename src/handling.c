/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachtata <yachtata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 04:06:19 by yachtata          #+#    #+#             */
/*   Updated: 2024/01/28 11:10:23 by yachtata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	change_a_y_z(t_var *data, int *x, int *y, int *z)
{
	*x += data->new_x;
	*y += data->new_y;
	*z += data->new_z;
}

int	close_button_press(void *param)
{
	t_var	*vars;

	vars = (t_var *)param;
	free_mem(vars);
	exit(0);
	return (0);
}

void	connect_to_down(t_cpy **head, int row, int clm)
{
	t_cpy	*current;
	t_cpy	*down_node;

	current = *head;
	while (current)
	{
		if (current->x == row && current->y == clm)
		{
			down_node = current->next;
			while (down_node && down_node->x != row)
				down_node = down_node->next;
			if (down_node && down_node->y == clm + 1)
			{
				current->down = down_node;
				return ;
			}
		}
		current = current->next;
	}
}

void	connect_to_right(t_cpy **head, int row, int clm)
{
	t_cpy	*current;
	t_cpy	*right_node;

	current = *head;
	while (current)
	{
		if (current->y == clm && current->x == row)
		{
			right_node = current->next;
			while (right_node && right_node->y != clm)
				right_node = right_node->next;
			if (right_node && right_node->x == row + 1)
			{
				current->right = right_node;
				return ;
			}
		}
		current = current->next;
	}
}

void	link_points(t_cpy *head)
{
	t_cpy	*temp;

	temp = head;
	while (temp)
	{
		connect_to_down(&head, temp->x, temp->y);
		connect_to_right(&head, temp->x, temp->y);
		temp = temp->next;
	}
}
