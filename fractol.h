/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 16:31:35 by rbozhko           #+#    #+#             */
/*   Updated: 2018/07/21 16:31:37 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
#define FRACTOL_H

#include <stdio.h>
#include <stdbool.h>
#include "libft/libft.h"
#include "minilibx/mlx.h"
#include "jpeglib/jpeglib.h"
#include <math.h>
#include <complex.h>
#include <pthread.h>
#include <time.h>

# define WARNING "(max:9999)"
# define MIN_WIN_SIZE "400"
# define USAGE_BONUS "(mandelbrot, io, ship, julia, newton)\n\t\t (unit should be greater than "
# define USAGE_STR "usage: ./fractol [fractol_name[width:uint height:uint]]\n\t\t "
# define CONCAT USAGE_STR USAGE_BONUS MIN_WIN_SIZE WARNING ")"
# define FRACTOL_NUM 5
# define HEIGHT 800
# define WIDTH 1200
# define OFFSET_NUM 5
# define ZOOM_COEF 0.3
# define ZOOM_BOUNDARY map->zoom >= -50 
//&& map->zoom <= 500
# define INSIDE_WIN ((x >= 0 && x <= map->win_width) && (y >= 0 && y <= map->win_height))
# define COLOR_OPTIONS_NUM 6
# define THREADS_NUM 4
//4


#define CALC_REAL 1.5 * (map->x + map->x_offset - map->win_width / 2) / (0.5 * map->zoom * map->win_width)
#define CALC_IMG (map->y + map->y_offset - map->win_height / 2) / (0.5 * map->zoom * map->win_height)

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
# define C_LTTR 8 // c
# define P_LTTR 35 // p
# define S_LTTR 1 // s

//# define BUFF_SIZE 1
//# define NL_CODE ft_strchr(temp, '\n')
//# define S_C_SUB (NL_CODE - temp)
//# define IF_FP ((fd < 0 || fd > 4096) || ((read(fd, buff, 0)) == -1 && !(head)))
//# define IF_SP (!(line) || !(ft_memset(buff, 0, BUFF_SIZE + 1)))

# define RANGE map->pltt.width + map->pltt.center
# define COLOR_GEN(gamma) (sin(map->pltt.freq * iter + gamma) * RANGE)

# define ALLOWED_WIN_AREA_FOR_THREADS_COEF (1000 * 1000) // to be found, may not be correct
# define THREADS_ALLOC sizeof(unsigned char) * map->win_height * map->win_width * bpp + 1

typedef struct s_jpeg
{
	size_t				id;
	size_t				len;
	size_t				y_start;
	size_t				y_end;
	unsigned char		*dest_str;
	unsigned char		*src_str;
} t_jpeg;

typedef	struct	s_node
{
	int				fd;
	char			*str;
	struct s_node	*next;
}				t_node;

typedef		struct 	s_complex
{
	double		real;
	double		im;		
}					t_complex;

typedef		struct  s_color
{
	const float			freq;
	unsigned short		center;
	unsigned short		width;
	unsigned short		b_coef;
	unsigned short		g_coef;
	unsigned short		r_coef;
}					t_color;

typedef		struct s_map t_map;
typedef void 		(*pft)(t_map *map);

struct 	s_map
{
	int			win_width;
	int			win_height;
	bool		pause;
	int 		speed;
	int 		x_offset;
	int 		y_offset;
	double 		julia_coef_x;
	double 		julia_coef_y;
	int 		mouse_x;
	int 		mouse_y;
	double		zoom;
	int 		iter;
	int 		max_iter;
	int 		x;
	int 		y;
	pft 		(*function);
	int 		f_num;
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	// char		*str;
	unsigned char		*str;
	int 		bpp;
	int 		sl;
	int 		endian;
	t_color		pltt;
	// t_threads_info		**threads;
};

typedef		struct  s_threads_info
{
	size_t				thread_id;
	int					iter;
	size_t				x_start;
	// size_t				x_end;
	size_t				y_start;
	size_t				y_end;
	t_complex			ft_curr;
	t_complex			ft_prev;
	t_complex			constant;
	double				newton_cnst;
	t_map				*map;
}					t_threads_info;

void		ft_get_color(unsigned iter_num, t_map *map);
void		mandelbrot(t_map *map);
void		io(t_map *map);
void		ship(t_map *map);
void		julia(t_map *map);
void		newton(t_map *map);
void		fractol_init(int fractol_num, char *fractol_name, t_map *map);
void		ft_draw_fractol(t_map *map);
pft 		*ft_handle_fractol(int fractol_num);
void		ft_change_default_color(t_map *map);
int			get_next_line(const int fd, char **line, char *str);
void		ft_get_threads_info(t_map *map);
int 		ft_make_printscreen(t_map *map);
int 		ft_mouse_hook(int mouse_code, int pos_x, int pos_y, t_map *map);
int 		ft_key_hook(int keycode, t_map *map);
int 		ft_julia_coef(int x, int y, t_map *map);
unsigned char        *ft_get_threads(t_map *map, int bpp, size_t i, size_t range);
unsigned char   *ft_get_proper(t_map *map);
char				**ft_get_months(void);
char				*ft_find_month(const char *str);
char				*ft_get_time_part(const char *curr_time);
char				*ft_get_fractol_name(const t_map *map);

#endif
