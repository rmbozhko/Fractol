#include "fractol.h"

pft 		*ft_handle_fractol(int fractol_num)
{
	pft 		*fractol_ptr;

	fractol_ptr = (pft*)malloc(sizeof(pft) * FRACTOL_NUM);
	fractol_ptr[0] = mandelbrot;
	fractol_ptr[1] = io;
	fractol_ptr[2] = ship;
	fractol_ptr[3] = julia;
	fractol_ptr[4] = newton;
	fractol_ptr[5] = NULL;
	return (fractol_ptr);
}

void		fractol_init(int fractol_num, char *fractol_name, t_map *map)
{
	map->pause = false;
	map->speed = 1;
	map->x_offset = 0;
	map->y_offset = 0;
	map->julia_coef_x = 0;
	map->julia_coef_y = 0;
	map->mouse_x = 0;
	map->mouse_y = 0;
	map->zoom = 1;
	map->iter = 0;
	map->max_iter = ITER_START;
	map->f_num = fractol_num;
	map->mlx_ptr = mlx_init();
	map->win_ptr = mlx_new_window(map->mlx_ptr, map->win_width, map->win_height, fractol_name);
	map->img_ptr = mlx_new_image(map->mlx_ptr, map->win_width, map->win_height);
	map->str = mlx_get_data_addr(map->img_ptr, &map->bpp, &map->sl, &map->endian);
	map->function = ft_handle_fractol(fractol_num);
	map->pltt = (t_color){0.3F, 128, 127, 2, 0, 4};
	// map->threads = ft_get_threads_info();
}