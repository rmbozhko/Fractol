#include "fractol.h"

// void		newton_mod(struct s_map *map)
// {	
// 	imgx = 512
// 	imgy = 512
// 	image = Image.new("RGB", (imgx, imgy))

// 	# drawing area
// 	xa = -1.0
// 	xb = 1.0
// 	ya = -1.0
// 	yb = 1.0

// 	maxIt = 20 # max iterations allowed
// 	h = 1e-6 # step size for numerical derivative
// 	eps = 1e-3 # max error allowed

// 	# put any complex function here to generate a fractal for it!
// 	def f(z):
//     	return z * z * z - 1.0

// 	# draw the fractal
// 	for y in range(imgy):
//     	zy = y * (yb - ya) / (imgy - 1) + ya
//     	for x in range(imgx):
//         	zx = x * (xb - xa) / (imgx - 1) + xa
//         	z = complex(zx, zy)
//         	for i in range(maxIt):
//             	# complex numerical derivative
//             	dz = (f(z + complex(h, h)) - f(z)) / complex(h, h)
//             	z0 = z - f(z) / dz # Newton iteration
//             	if abs(z0 - z) < eps: # stop when close enough to any root
//                 	break
//             	z = z0
//         	image.putpixel((x, y), (i % 4 * 64, i % 8 * 32, i % 16 * 16))

// 	image.save("newtonFr.png", "PNG")
// }

void		mandelbrot(struct s_map *map)
{
	t_complex		ft_curr;
	t_complex		ft_prev;
	t_complex		constant;

	constant.real = 1.5 * (map->x + map->x_offset - map->win_width / 2) / (0.5 * map->zoom * map->win_width);
	constant.im = (map->y + map->y_offset - map->win_height / 2) / (0.5 * map->zoom * map->win_height);
	ft_prev.real = 0.0;
	ft_prev.im = 0.0;
	while (map->iter < map->max_iter)
	{
		ft_curr.real = ft_prev.real;
		ft_curr.im = ft_prev.im;
		ft_prev.real = ft_curr.real * ft_curr.real - ft_curr.im * ft_curr.im + constant.real;
		ft_prev.im = 2.0 * ft_curr.real * ft_curr.im + constant.im;
		if ((ft_prev.real * ft_prev.real + ft_prev.im * ft_prev.im) > 4.0)
		{
			ft_get_color(map->iter, map);
			break ;
		}
		map->iter++;
	}
}

void		ship(struct s_map *map)
{
	t_complex		ft_curr;
	t_complex		ft_prev;
	t_complex		constant;

	constant.real = 1.5 * (map->x + map->x_offset - map->win_width / 2) / (0.5 * map->zoom * map->win_width);
	constant.im = (map->y + map->y_offset - map->win_height / 2) / (0.5 * map->zoom * map->win_height);
	ft_prev.real = 0.0;
	ft_prev.im = 0.0;
	while (map->iter < map->max_iter)
	{
		ft_curr.real = ft_prev.real;
		ft_curr.im = ft_prev.im;
		ft_prev.real = ft_curr.real * ft_curr.real - ft_curr.im * ft_curr.im + constant.real;
		ft_prev.im = 2.0 * fabs(ft_curr.real) * fabs(ft_curr.im) + constant.im;
		if ((ft_prev.real * ft_prev.real + ft_prev.im * ft_prev.im) > 4.0)
		{
			ft_get_color(map->iter, map);
			break ;
		}
		map->iter++;
	}
}

void		julia(struct s_map *map)
{
	t_complex		ft_curr;
	t_complex		ft_prev;

	ft_prev.real = 1.5 * (map->x + map->x_offset - map->win_width / 2) / (0.5 * map->zoom * map->win_width);
	ft_prev.im = (map->y + map->y_offset - map->win_height / 2) / (0.5 * map->zoom * map->win_height);
	while (map->iter < map->max_iter)
	{
		ft_curr.real = ft_prev.real;
		ft_curr.im = ft_prev.im;
		ft_prev.real = ft_curr.real * ft_curr.real - ft_curr.im * ft_curr.im + map->julia_coef_x;
		ft_prev.im = 2.0 * ft_curr.real * ft_curr.im + map->julia_coef_y;
		if ((ft_prev.real * ft_prev.real + ft_prev.im * ft_prev.im) > 4.0)
		{
			ft_get_color(map->iter, map);
			break ;
		}
		map->iter++;
	}
}

void			newton(struct s_map *map)
{
	t_complex		ft_curr;
	t_complex		ft_prev;
	double			constant;

	ft_curr.real = 1.5 * (map->x + map->x_offset - map->win_width / 2) / (0.5 * map->zoom * map->win_width);
	ft_curr.im = (map->y + map->y_offset - map->win_height / 2) / (0.5 * map->zoom * map->win_height);
	constant = 1.0;
	while (constant > 0.000001 && map->iter < map->max_iter)
	{
		ft_prev.real = ft_curr.real;
		ft_prev.im = ft_curr.im;
		constant = (ft_curr.real * ft_curr.real + ft_curr.im * ft_curr.im) *
			(ft_curr.real * ft_curr.real + ft_curr.im * ft_curr.im);
		ft_curr.real = (2 * ft_curr.real * constant + ft_curr.real * ft_curr.real -
				ft_curr.im * ft_curr.im) / (3.0 * constant);
		ft_curr.im = (2 * ft_curr.im * (constant - ft_prev.real)) / (3.0 * constant);
		constant = (ft_curr.real - ft_prev.real) * (ft_curr.real - ft_prev.real) +
			(ft_curr.im - ft_prev.im) * (ft_curr.im - ft_prev.im);
		map->iter++;
	}
	if (map->iter != map->max_iter)
		ft_get_color(map->iter, map);
}

void			io(struct s_map *map)
{
	t_complex		ft_curr;
	t_complex		ft_prev;

	ft_curr.real = 1.5 * (map->x + map->x_offset - map->win_width / 2) / (0.5 * map->zoom * map->win_width);
	ft_curr.im = (map->y + map->y_offset - map->win_height / 2) / (0.5 * map->zoom * map->win_height);
	while (map->iter < map->max_iter)
	{
		ft_prev.real = ft_curr.real;
		ft_prev.im = ft_curr.im;
		ft_curr.real = ft_prev.real * ft_prev.real * ft_prev.real * ft_prev.real
			+ ft_prev.im * ft_prev.im * ft_prev.im * ft_prev.im -
			6 * ft_prev.real * ft_prev.real * ft_prev.im * ft_prev.im + map->julia_coef_x;
		ft_curr.im = 4 * ft_prev.real * ft_prev.real * ft_prev.real * ft_prev.im -
			4 * ft_prev.real * ft_prev.im * ft_prev.im * ft_prev.im + map->julia_coef_y;
		if (ft_prev.real * ft_prev.im > 4 || ft_prev.im * ft_prev.im > 4)
		{
			if ((fabs(ft_curr.real)) > 10 || (fabs(ft_curr.im) > 1000))
				ft_get_color(map->iter, map);
			break ;
		}
		map->iter++;
	}
}

