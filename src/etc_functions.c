/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   etc_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachtata <yachtata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 06:44:17 by yachtata          #+#    #+#             */
/*   Updated: 2024/01/25 06:44:18 by yachtata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	interpolate_color_component(int c1, int c2, float t)
{
	return ((int)(c1 + (c2 - c1) * t));
}

void	print_list(t_line *test)
{
	t_line	*head;

	head = test;
	while (head)
	{
		ft_printf("node -> %s\n", head->content);
		head = head->next;
	}
}

int	ft_grepcolor(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ',' && str[i + 1] != '\0' && str[i + 1] == '0')
			return (ft_atoi_base(str + (i + 3), HEX_DECIMAL));
		i++;
	}
	return (0);
}

void	fill_screen(t_var *data)
{
	int	y;
	int	x;

	y = -1;
	while (y < HEIGHT)
	{
		x = -1;
		while (x < WIDTH)
		{
			my_pixel_put(&(data->img), x, y, 0x212221);
			x++;
		}
		y++;
	}
}

void	put_image(t_var *data, int keycode)
{
	fill_screen(data);
	connect_pixels(data, keycode);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
	put_info(data);
}
