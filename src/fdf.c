/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachtata <yachtata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 06:18:26 by yachtata          #+#    #+#             */
/*   Updated: 2024/02/08 07:40:10 by yachtata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	my_pixel_put(t_img *img, int x, int y, int color)
{
	int	offset;

	if (x < 0 || x > WIDTH || y < 0 || y > HEIGHT)
		return ;
	offset = (img->line_len * y) + (x * (img->bits_per_pixel / 8));
	*((unsigned int *)(offset + img->img_pixels_ptr)) = color;
}

void	display_windows(t_var *data)
{
	data->size_line = (HEIGHT / fmax(data->max_columns, data->max_rows)) * 0.35;
	fill_screen(data);
	connect_pixels(data, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
	data->moves = 1;
	put_info(data);
}

void	initialize_vars(t_var *vars, char *map_file)
{
	vars->z_len = 1;
	check_maps(vars, map_file);
	link_nodes(vars, vars->twod_array);
	vars->mlx = mlx_init();
	if (!vars->mlx)
	{
		free_2d_array(vars->twod_array, vars->total);
		exit(1);
	}
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "My window");
	if (!vars->win)
	{
		free_2d_array(vars->twod_array, vars->total);
		mlx_destroy_display(vars->mlx);
		exit(1);
	}
	vars->img.img_ptr = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	vars->img.img_pixels_ptr = mlx_get_data_addr(vars->img.img_ptr,
			&vars->img.bits_per_pixel, &vars->img.line_len, &vars->img.endian);
}

void	run_graphics(t_var *vars)
{
	display_windows(vars);
	mlx_hook(vars->win, 33, 1L << 17, close_button_press, vars);
	mlx_key_hook(vars->win, key_press, vars);
	put_info(vars);
	mlx_loop(vars->mlx);
	free_mem(vars);
}

int	main(int argc, char **argv)
{
	t_var	vars;

	if (argc != 2)
	{
		ft_printf("Invalid number of argc: ./fdf </tests_maps/your_map.fdf>\n");
		exit(0);
	}
	initialize_vars(&vars, argv[1]);
	run_graphics(&vars);
	return (0);
}
