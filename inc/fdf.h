/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 13:17:17 by dpoveda-          #+#    #+#             */
/*   Updated: 2024/02/15 02:49:32 by yachtata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../lib/libft/includes/libft.h"
# include "../lib/mlx_linux/mlx.h"
# include <X11/keysym.h>
# include <math.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>

# define WHITE 0xFFFFFF
# define HEIGHT 900
# define WIDTH 1400
# define Z_IN 105
# define Z_OUT 111
# define H_KEY 104
# define J_KEY 106
# define K_KEY 107
# define L_KEY 108
# define ROTATE_X 120
# define ROTATE_Y 121
# define ROTATE_Z 122
# define INFO_X 20
# define INFO_Y 40
# define ZOME_OUT 61
# define ZOME_IN 45

# define MALLOC_ERROR 1
# define HEX_DECIMAL "0123456789abcdef"

typedef struct s_cpy
{
	int				x;
	int				y;
	int				z;
	int				color;
	void			*down;
	void			*right;

	struct s_cpy	*next;
}					t_cpy;

typedef struct s_bresenham
{
	int				x1;
	int				y1;
	int				x2;
	int				y2;
	int				dx;
	int				sx;
	int				dy;
	int				sy;
	int				err;
	int				e2;
	int				color;
}					t_bresenham;

typedef struct s_trgb
{
	int				t1;
	int				r1;
	int				g1;
	int				b1;

	int				t2;
	int				r2;
	int				g2;
	int				b2;

	int				lerped_t;
	int				lerped_r;
	int				lerped_g;
	int				lerped_b;
}					t_trgb;

typedef struct s_img
{
	void			*img_ptr;
	char			*img_pixels_ptr;
	int				bits_per_pixel;
	int				endian;
	int				line_len;
}					t_img;

typedef struct s_line
{
	char			*content;
	struct s_line	*next;
}					t_line;

typedef struct s_var
{
	t_cpy			**twod_array;
	t_img			img;
	t_bresenham		bresenham;
	t_trgb			trgb;
	t_line			*head;
	void			*mlx;
	void			*win;
	int				max_rows;
	int				max_columns;
	int				size_line;
	int				total;
	int				last_botton;
	int				max_z;
	int				z_len;
	int				new_x;
	int				new_y;
	int				new_z;
	int				moves;
	int				zome;
	int				zome_z;
	int				first_z;
	int				check_map;
	float			rotation_anglex;
	float			rotation_angley;
	float			rotation_anglez;
}					t_var;

void				connect_pixels(t_var *data, int rotate_bottom);
void				link_points(t_cpy *head);
t_cpy				**check_maps(t_var *data, char *str);
void				free_mem(t_var *vars);
void				free_list(t_line **lst);
void				my_pixel_put(t_img *img, int x, int y, int color);
int					close_button_press(void *param);
void				rotate_z(int *x, int *y, int *z, float theta);
void				rotate_x(int *x, int *y, int *z, float theta);
void				rotate_y(int *x, int *y, int *z, float angle_degrees);
void				to_isometric(t_var *data, int *x, int *y, int *z);
int					ft_grepcolor(char *str);
int					lerp_trgb(t_var *data, t_cpy *current, t_cpy *right_down,
						float t);
int					create_trgb(int t, int r, int g, int b);
int					get_b(int trgb);
int					get_g(int trgb);
int					get_r(int trgb);
int					get_t(int trgb);
int					key_press(int keycode, t_var *data);
void				color_screen(t_var *data, int color);
void				find_rotation(t_var *data, int *x, int *y, int *z);
t_cpy				*get_rightNode(t_var *data, int x, int y);
t_cpy				*get_downNode(t_var *data, int x, int y);
void				print_2d_array(t_var *data, t_cpy **twod_array);
void				link_nodes(t_var *data, t_cpy **two_array);
void				fill_screen(t_var *data);
void				creat_list(t_var *data, char *str);
void				print_list(t_line *test);
void				free_2d_array(t_cpy **array, int total);
void				bresenham_line(t_var *data, t_cpy *current,
						t_cpy *right_down);
void				change_a_y_z(t_var *data, int *x, int *y, int *z);
void				put_info(t_var *data);
void				put_image(t_var *data, int keycode);
int					interpolate_color_component(int c1, int c2, float t);
void				zome(int button, int x, int y, void *param);
int					find_index(int x, int y, int weight);
int					is_file_empty(const char *filename);

#endif
