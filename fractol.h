/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 16:31:35 by rbozhko           #+#    #+#             */
/*   Updated: 2018/07/21 19:04:03 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h>
# include <stdbool.h>
# include "libft/libft.h"
# include "minilibx/mlx.h"
# include "jpeglib/jpeglib.h"
# include <math.h>
# include <complex.h>
# include <pthread.h>
# include <time.h>

# define W_H map->win_height
# define W_W map->win_width
# define WARNING "(max:9999)"
# define MIN_WIN_SIZE "400"
# define USAGE_BONUS "(mandelbrot, io, ship, julia, newton)\n\t\t"
# define RESTRICTION "\t\t(unit should be greater than "
# define USAGE_STR "usage: ./fractol [fractol_name[width:uint height:uint]]\n"
# define CONCAT USAGE_STR USAGE_BONUS RESTRICTION MIN_WIN_SIZE WARNING ")"
# define FRACTOL_NUM 5
# define HEIGHT 800
# define WIDTH 1200
# define OFFSET_NUM 5
# define ZOOM_COEF 0.3
# define ZOOM_BOUNDARY map->zoom >= -50
# define INSIDE_WIN ((x >= 0 && x <= W_W) && (y >= 0 && y <= W_H))
# define COLOR_OPTIONS_NUM 6
# define THREADS_NUM 4
# define PART 0.5 * map->zoom
# define CALC_REAL 1.5 * (map->x + map->x_offset - W_W / 2) / (PART * W_W)
# define CALC_IMG (map->y + map->y_offset - W_H / 2) / (PART * W_H)
# define ESC 53
# define ONE 18
# define ZERO 29
# define FOUR 21
# define KEYBOARD_DIGITS_BASE_NUM 17
# define SPACE 49
# define ITER_START 10
# define ITER_STEP 10
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define PLUS 69
# define NEG 78
# define C_LTTR 8
# define P_LTTR 35
# define S_LTTR 1

# define RANGE map->pltt.width + map->pltt.center
# define COLOR_GEN(gamma) (sin(map->pltt.freq * iter + gamma) * RANGE)
# define ALLOWED_WIN_AREA_FOR_THREADS_COEF (1000 * 1000)
# define THREADS_ALLOC sizeof(unsigned char) * W_H * W_W * bpp + 1

typedef	struct			s_jpeg
{
	size_t				id;
	size_t				len;
	size_t				y_start;
	size_t				y_end;
	unsigned char		*dest_str;
	unsigned char		*src_str;
}						t_jpeg;

typedef	struct			s_node
{
	int				fd;
	char			*str;
	struct s_node	*next;
}						t_node;

typedef	struct			s_complex
{
	double		real;
	double		im;
}						t_complex;

typedef	struct			s_color
{
	const float			freq;
	unsigned short		center;
	unsigned short		width;
	unsigned short		b_coef;
	unsigned short		g_coef;
	unsigned short		r_coef;
}						t_color;

typedef	struct s_map	t_map;
typedef void		(*t_pft)(t_map *map);

struct					s_map
{
	int					win_width;
	int					win_height;
	bool				pause;
	int					speed;
	int					x_offset;
	int					y_offset;
	double				julia_coef_x;
	double				julia_coef_y;
	int					mouse_x;
	int					mouse_y;
	double				zoom;
	int					iter;
	int					max_iter;
	int					x;
	int					y;
	t_pft				(*function);
	int					f_num;
	void				*mlx_ptr;
	void				*win_ptr;
	void				*img_ptr;
	unsigned char		*str;
	int					bpp;
	int					sl;
	int					endian;
	t_color				pltt;
};

typedef	struct			s_threads_info
{
	size_t				thread_id;
	int					iter;
	size_t				x_start;
	size_t				y_start;
	size_t				y_end;
	t_complex			ft_curr;
	t_complex			ft_prev;
	t_complex			constant;
	double				newton_cnst;
	t_map				*map;
}						t_threads_info;

void					ft_get_color(unsigned iter_num, t_map *map);
void					mandelbrot(t_map *map);
void					io(t_map *map);
void					ship(t_map *map);
void					julia(t_map *map);
void					newton(t_map *map);
void					fractol_init(int f_num, char *f_name, t_map *m);
void					ft_draw_fractol(t_map *map);
t_pft					*ft_handle_fractol(int fractol_num);
void					ft_change_default_color(t_map *map);
void					ft_get_threads_info(t_map *map);
int						ft_make_printscreen(t_map *map);
int						ft_mouse_hook(int m, int x, int y, t_map *map);
int						ft_key_hook(int keycode, t_map *map);
int						ft_julia_coef(int x, int y, t_map *map);
unsigned char			*ft_get_threads(t_map *m, int b, size_t i, size_t r);
unsigned char			*ft_get_proper(t_map *map);
char					**ft_get_months(void);
char					*ft_find_month(const char *str);
char					*ft_get_time_part(const char *curr_time);
char					*ft_get_fractol_name(const t_map *map);

#endif
