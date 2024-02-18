/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachtata <yachtata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 04:08:57 by yachtata          #+#    #+#             */
/*   Updated: 2024/01/25 04:11:43 by yachtata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	radians_to_degrees(double radians)
{
	int	degrees;

	degrees = radians * (180.0 / M_PI);
	return (degrees);
}

void	display_map_info(t_var *data, void *mlx_ptr, void *win_ptr)
{
	char	rows_info[50];
	char	columns_info[50];
	char	rows_str[20];
	char	columns_str[20];

	mlx_string_put(mlx_ptr, win_ptr, INFO_X, INFO_Y, WHITE, "/// MAP INFO ///");
	ft_strcpy(rows_info, "Max Rows: ");
	int_to_str(data->max_rows, rows_str);
	ft_strcat(rows_info, rows_str);
	mlx_string_put(mlx_ptr, win_ptr, INFO_X + 5, INFO_Y + 40, WHITE, rows_info);
	ft_strcpy(columns_info, "Max Columns: ");
	int_to_str(data->max_columns, columns_str);
	ft_strcat(columns_info, columns_str);
	mlx_string_put(mlx_ptr, win_ptr, INFO_X + 5, INFO_Y + 60, WHITE,
		columns_info);
	ft_strcpy(columns_info, "Max Z: ");
	int_to_str(data->max_z, columns_str);
	ft_strcat(columns_info, columns_str);
	mlx_string_put(mlx_ptr, win_ptr, INFO_X + 5, INFO_Y + 80, WHITE,
		columns_info);
	ft_strcpy(columns_info, "Size: ");
	int_to_str(data->total, columns_str);
	ft_strcat(columns_info, columns_str);
	mlx_string_put(mlx_ptr, win_ptr, INFO_X + 5, INFO_Y + 100, WHITE,
		columns_info);
}

void	display_controls_info(void *mlx_ptr, void *win_ptr)
{
	mlx_string_put(mlx_ptr, win_ptr, INFO_X, INFO_Y + 130, WHITE,
		"/// CONTROLS INFO ///");
	mlx_string_put(mlx_ptr, win_ptr, INFO_X + 5, INFO_Y + 160, WHITE,
		"MOVE LEFT: H");
	mlx_string_put(mlx_ptr, win_ptr, INFO_X + 5, INFO_Y + 180, WHITE,
		"MOVE RIGHT: L");
	mlx_string_put(mlx_ptr, win_ptr, INFO_X + 5, INFO_Y + 200, WHITE,
		"MOVE UP: J");
	mlx_string_put(mlx_ptr, win_ptr, INFO_X + 5, INFO_Y + 220, WHITE,
		"MOVE DOWN: K");
	mlx_string_put(mlx_ptr, win_ptr, INFO_X + 5, INFO_Y + 250, WHITE,
		"ZOME IN /10: -");
	mlx_string_put(mlx_ptr, win_ptr, INFO_X + 5, INFO_Y + 270, WHITE,
		"ZOME OUT x10: +");
	mlx_string_put(mlx_ptr, win_ptr, INFO_X + 5, INFO_Y + 290, WHITE,
		"INCREASE Z: O");
	mlx_string_put(mlx_ptr, win_ptr, INFO_X + 5, INFO_Y + 310, WHITE,
		"REDUCTION Z: I");
	mlx_string_put(mlx_ptr, win_ptr, INFO_X + 5, INFO_Y + 350, WHITE,
		"RENDER MAP: A");
	mlx_string_put(mlx_ptr, win_ptr, INFO_X + 5, INFO_Y + 370, WHITE,
		"BACK TO NORAML MODE: Q");
	mlx_string_put(mlx_ptr, win_ptr, INFO_X + 5, INFO_Y + 390, WHITE,
		"ROTATION : X, Y, Z");
}

void	display_angles_info(t_var *data, void *mlx_ptr, void *win_ptr)
{
	char	rows_str[20];

	mlx_string_put(mlx_ptr, win_ptr, INFO_X + 5, INFO_Y + 20, WHITE,
		"X, Y, Z: [   ] [   ] [   ]");
	int_to_str(radians_to_degrees(data->rotation_anglex), rows_str);
	if (data->rotation_anglex == 0.0)
		mlx_string_put(mlx_ptr, win_ptr, INFO_X + 65, INFO_Y + 20, 0xffb533,
			"0");
	else
		mlx_string_put(mlx_ptr, win_ptr, INFO_X + 65, INFO_Y + 20, 0xffb533,
			rows_str);
	int_to_str(radians_to_degrees(data->rotation_angley), rows_str);
	if (data->rotation_angley == 0.0)
		mlx_string_put(mlx_ptr, win_ptr, INFO_X + 102, INFO_Y + 20, 0xffb533,
			"0");
	else
		mlx_string_put(mlx_ptr, win_ptr, INFO_X + 102, INFO_Y + 20, 0xffb533,
			rows_str);
	int_to_str(radians_to_degrees(data->rotation_anglez), rows_str);
	if (data->rotation_anglez == 0.0)
		mlx_string_put(mlx_ptr, win_ptr, INFO_X + 137, INFO_Y + 20, 0xffb533,
			"0");
	else
		mlx_string_put(mlx_ptr, win_ptr, INFO_X + 137, INFO_Y + 20, 0xffb533,
			rows_str);
}

void	put_info(t_var *data)
{
	display_map_info(data, data->mlx, data->win);
	display_controls_info(data->mlx, data->win);
	display_angles_info(data, data->mlx, data->win);
}
