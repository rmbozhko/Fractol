#ifndef FRACTOL_H
#define FRACTOL_H

#include <stdio.h>
#include <stdbool.h>
#include "libft/libft.h"
#include "minilibx/mlx.h"
#include <math.h>
#include <complex.h>


# define USAGE_STR "usage: ./fractol [fractol_name]\n\t\t (mandelbrot, io, ship, julia, newton)"
# define FRACTOL_NUM 5
# define HEIGHT 800
# define WIDTH 1200
# define OFFSET_NUM 5
# define ZOOM_COEF 0.3

# define ESC 53
# define ONE 18
# define ZERO 29
# define FOUR 21
# define KEYBOARD_DIGITS_BASE_NUM 17
# define INSIDE_WIN ((x >= 0 && x <= WIDTH) && (y >= 0 && y <= HEIGHT))
# define SPACE 49
# define ITER_START 10
# define ITER_STEP 10
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define PLUS 69
# define NEG 78

// typedef	void (*pft)(struct s_map *map);

typedef		struct 	s_map
{
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
	void 		(**function)(struct s_map *map);
	int 		f_num;
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*str;
	int 		bpp;
	int 		sl;
	int 		endian;
}					t_map;

typedef		struct 	s_complex
{
	double		real;
	double		im;		
}					t_complex;

typedef void 		(*pft)(t_map *map);

void		ft_get_color(unsigned iter_num, t_map *map);
void		mandelbrot(t_map *map);
void		io(t_map *map);
void		ship(t_map *map);
void		julia(t_map *map);
void		newton(t_map *map);
void		fractol_init(int fractol_num, char *fractol_name, t_map *map);
void		ft_draw_fractol(t_map *map);
pft 		*ft_handle_fractol(int fractol_num);

#endif