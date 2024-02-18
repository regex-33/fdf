/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachtata <yachtata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 04:12:45 by yachtata          #+#    #+#             */
/*   Updated: 2024/02/08 08:11:43 by yachtata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	find_index(int x, int y, int width)
{
	return ((y) * (width) + (x));
}

int	is_file_empty(const char *filename)
{
	int		fd;
	char	buffer[1];
	ssize_t	bytes_read;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error opening file", 2);
		exit(MALLOC_ERROR);
	}
	bytes_read = read(fd, buffer, sizeof(buffer));
	if (bytes_read == -1)
	{
		ft_putstr_fd("Error reading file", 2);
		close(fd);
		exit(MALLOC_ERROR);
	}
	close(fd);
	return (bytes_read == 0);
}

void	free_list(t_line **lst)
{
	t_line	*temp;
	int		i;

	i = 0;
	if (!lst || !*lst)
		return ;
	while (*lst != NULL)
	{
		temp = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = temp;
		i++;
	}
	*lst = NULL;
}

void	free_2d_array(t_cpy **array, int total)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (i < total)
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
}

void	free_mem(t_var *vars)
{
	mlx_do_key_autorepeaton(vars->mlx);
	mlx_destroy_image(vars->mlx, vars->img.img_ptr);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free_2d_array(vars->twod_array, vars->total);
	free(vars->mlx);
	exit(1);
}
