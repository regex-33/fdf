/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_bresenham.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachtata <yachtata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 06:44:02 by yachtata          #+#    #+#             */
/*   Updated: 2024/02/10 12:26:35 by yachtata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	calculate_color_based_on_z(int z, int max_z)
{
	float	factor;
	int		blue_intensity;

	factor = (float)z / max_z;
	blue_intensity = (int)(255 * factor);
	return (create_trgb(0, 0, blue_intensity, 255 - blue_intensity));
}

int	calculate_and_set_color(t_var *data, t_cpy *point)
{
	if (!point->color)
	{
		if (!point->z)
			point->color = calculate_color_based_on_z(0, 1);
	}
	if (point->color)
		return (point->color);
	else
		return (calculate_color_based_on_z(point->z, data->max_z));
}

int	lerp_trgb(t_var *data, t_cpy *current, t_cpy *right_down, float t)
{
	int	color1;
	int	color2;

	color1 = calculate_and_set_color(data, current);
	color2 = calculate_and_set_color(data, right_down);
	data->trgb.t1 = get_t(color1);
	data->trgb.r1 = get_r(color1);
	data->trgb.g1 = get_g(color1);
	data->trgb.b1 = get_b(color1);
	data->trgb.t2 = get_t(color2);
	data->trgb.r2 = get_r(color2);
	data->trgb.g2 = get_g(color2);
	data->trgb.b2 = get_b(color2);
	data->trgb.lerped_t = interpolate_color_component(data->trgb.t1,
			data->trgb.t2, t);
	data->trgb.lerped_r = interpolate_color_component(data->trgb.r1,
			data->trgb.r2, t);
	data->trgb.lerped_g = interpolate_color_component(data->trgb.g1,
			data->trgb.g2, t);
	data->trgb.lerped_b = interpolate_color_component(data->trgb.b1,
			data->trgb.b2, t);
	return (create_trgb(data->trgb.lerped_t, data->trgb.lerped_r,
			data->trgb.lerped_g, data->trgb.lerped_b));
}

void	bresenham_line_2(t_var *data, t_cpy *current, t_cpy *right_down,
		float persantej)
{
	while (1)
	{
		if (!data->size_line)
			data->size_line = 1;
		persantej = (persantej / data->size_line) * 100;
		data->bresenham.color = lerp_trgb(data, current, right_down, persantej
				/ 100.0);
		my_pixel_put(&(data->img), data->bresenham.x1, data->bresenham.y1,
			data->bresenham.color);
		if (data->bresenham.x1 == data->bresenham.x2
			&& data->bresenham.y1 == data->bresenham.y2)
			break ;
		data->bresenham.e2 = 2 * data->bresenham.err;
		if (data->bresenham.e2 >= data->bresenham.dy)
		{
			data->bresenham.err += data->bresenham.dy;
			data->bresenham.x1 += data->bresenham.sx;
		}
		if (data->bresenham.e2 <= data->bresenham.dx)
		{
			data->bresenham.err += data->bresenham.dx;
			data->bresenham.y1 += data->bresenham.sy;
		}
		persantej += (data->size_line) / 100;
	}
}

void	bresenham_line(t_var *data, t_cpy *current, t_cpy *right_down)
{
	float	persantej;

	persantej = 0;
	data->bresenham.x1 = current->x;
	data->bresenham.y1 = current->y;
	data->bresenham.x2 = right_down->x;
	data->bresenham.y2 = right_down->y;
	data->bresenham.dx = abs(data->bresenham.x2 - data->bresenham.x1);
	if (data->bresenham.x1 < data->bresenham.x2)
		data->bresenham.sx = 1;
	else
		data->bresenham.sx = -1;
	data->bresenham.dy = -abs(data->bresenham.y2 - data->bresenham.y1);
	if (data->bresenham.y1 < data->bresenham.y2)
		data->bresenham.sy = 1;
	else
		data->bresenham.sy = -1;
	data->bresenham.err = data->bresenham.dx + data->bresenham.dy;
	bresenham_line_2(data, current, right_down, persantej);
}
