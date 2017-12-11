#include "fractol.h"

void		mandelbrot(struct s_map *map)
{
	t_complex		ft_curr;
	t_complex		ft_prev;
	t_complex		constant;

	constant.real = 1.5 * (map->x - WIDTH / 2) / (0.5 * map->zoom * WIDTH);
	constant.im = (map->y - HEIGHT / 2) / (0.5 * map->zoom * HEIGHT);
	ft_prev.real = 0.0;
	ft_prev.im = 0.0;
	while (map->iter < map->max_iter)
	{
		ft_curr.real = ft_prev.real;
		ft_curr.im = ft_prev.im;
		ft_prev.real = ft_curr.real * ft_curr.real - ft_curr.im * ft_curr.im + constant.real;
		ft_prev.im = 2.0 * ft_curr.real * ft_curr.im + constant.im;
		if ((ft_prev.real * ft_prev.real + ft_prev.im * ft_prev.im) > 4.0)
			break ;
		map->iter++;
	}
}

void		io(struct s_map *map)
{
	printf("YOU HAVE VISITED io\n");
}

void		ship(struct s_map *map)
{
	t_complex		ft_curr;
	t_complex		ft_prev;
	t_complex		constant;

	constant.real = 1.5 * (map->x - WIDTH / 2) / (0.5 * map->zoom * WIDTH);
	constant.im = (map->y - HEIGHT / 2) / (0.5 * map->zoom * HEIGHT);
	ft_prev.real = 0.0;
	ft_prev.im = 0.0;
	while (map->iter < map->max_iter)
	{
		ft_curr.real = ft_prev.real;
		ft_curr.im = ft_prev.im;
		ft_prev.real = ft_curr.real * ft_curr.real - ft_curr.im * ft_curr.im + constant.real;
		ft_prev.im = 2.0 * fabs(ft_curr.real) * fabs(ft_curr.im) + constant.im;
		if ((ft_prev.real * ft_prev.real + ft_prev.im * ft_prev.im) > 4.0)
			break ;
		map->iter++;
	}
}

void		julia(struct s_map *map)
{
	t_complex		ft_curr;
	t_complex		ft_prev;

	ft_prev.real = 1.5 * (map->x - WIDTH / 2) / (0.5 * map->zoom * WIDTH);
	ft_prev.im = (map->y - HEIGHT / 2) / (0.5 * map->zoom * HEIGHT);
	while (map->iter < map->max_iter)
	{
		ft_curr.real = ft_prev.real;
		ft_curr.im = ft_prev.im;
		ft_prev.real = ft_curr.real * ft_curr.real - ft_curr.im * ft_curr.im + map->julia_coef_x;
		ft_prev.im = 2.0 * ft_curr.real * ft_curr.im + map->julia_coef_y;
		if ((ft_prev.real * ft_prev.real + ft_prev.im * ft_prev.im) > 4.0)
			break ;
		map->iter++;
	}
}

void		newton(struct s_map *map)
{
	printf("YOU HAVE VISITED newton\n");
}