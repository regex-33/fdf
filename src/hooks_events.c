/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachtata <yachtata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 06:56:22 by yachtata          #+#    #+#             */
/*   Updated: 2024/02/08 07:38:43 by yachtata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	ft_zome_in_out(t_var *data, int key)
{
	if (key == ZOME_IN)
	{
		if (data->size_line / 2 >= 1)
		{
			if (data->zome > 0)
				data->zome--;
			data->size_line /= 2;
		}
		else
			ft_printf("Is min zome\n");
	}
	else if (key == ZOME_OUT)
	{
		if (data->zome <= 4)
		{
			data->size_line *= 2;
			data->zome++;
		}
		else
			ft_printf("Is max zome\n");
	}
	put_image(data, key);
}

void	ft_resize_z(t_var *data, int key)

{
	if (key == Z_IN)
	{
		if (data->zome_z >= 1)
		{
			data->z_len /= 2;
			data->zome_z--;
		}
		else
			ft_printf("Is min zome\n");
	}
	else if (key == Z_OUT)
	{
		if (data->zome_z <= 4)
		{
			data->z_len *= 2;
			data->zome_z++;
		}
		else
			ft_printf("Is max zome\n");
	}
	put_image(data, key);
}

void	edite_aixs(t_var *data, int keycode)
{
	if (keycode == H_KEY)
	{
		data->new_x -= 5;
		if (data->total <= 10000)
			data->new_y -= 5;
	}
	else if (keycode == J_KEY)
	{
		data->new_y -= 5;
		if (data->total <= 10000)
			data->new_x += 5;
	}
	else if (keycode == K_KEY)
	{
		data->new_y += 5;
		if (data->total <= 10000)
			data->new_x -= 5;
	}
	else
	{
		data->new_x += 5;
		if (data->total <= 10000)
			data->new_y += 5;
	}
	put_image(data, keycode);
}

void	key_press_2(int keycode, t_var *data)
{
	if (keycode == ROTATE_Y)
	{
		if (data->rotation_angley < 6.28)
			data->rotation_angley += 0.1746;
		else
			data->rotation_angley = 0.1746;
		put_image(data, keycode);
	}
	else if (keycode == ROTATE_X)
	{
		if (data->rotation_anglex < 6.28)
			data->rotation_anglex += 0.1746;
		else
			data->rotation_anglex = 0.1746;
		put_image(data, keycode);
	}
	else if (keycode == ROTATE_Z)
	{
		if (data->rotation_anglez < 6.28)
			data->rotation_anglez += 0.1746;
		else
			data->rotation_anglez = 0.1746;
		put_image(data, keycode);
	}
}

int	key_press(int keycode, t_var *data)
{
	ft_printf("key : %d\n", keycode);
	if (keycode == XK_Escape)
		free_mem(data);
	else if (keycode == ZOME_OUT || keycode == ZOME_IN)
		ft_zome_in_out(data, keycode);
	else if (keycode == Z_OUT || keycode == Z_IN)
		ft_resize_z(data, keycode);
	else if (keycode == H_KEY || (keycode >= J_KEY && keycode <= L_KEY))
		edite_aixs(data, keycode);
	else if (keycode == 97)
	{
		data->last_botton = 97;
		put_image(data, keycode);
	}
	else if (keycode == 113)
	{
		data->last_botton = 113;
		data->rotation_anglex = 0.0;
		data->rotation_angley = 0.0;
		data->rotation_anglez = 0.0;
		put_image(data, keycode);
	}
	else
		key_press_2(keycode, data);
	return (0);
}
