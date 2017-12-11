#include "fractol.h"

pft 		*ft_handle_fractol(int fractol_num)
{
	// Bonus part, for changing fractal image during runtime
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

int			ft_is_fractol(const char *str)
{
	printf("|%s|\n", str);
	if (!ft_strcmp(str, "mandelbrot"))
		return (0);
	else if (!ft_strcmp(str, "io"))
		return (1);
	else if (!ft_strcmp(str, "ship"))
		return (2);
	else if (!ft_strcmp(str, "julia"))
		return (3);
	else if (!ft_strcmp(str, "newton"))
		return (4);
	return (-1);
}

static	void		ft_get_new_fractol(int keycode, t_map *map)
{
	if (keycode == ZERO)
		map->f_num = 0;
	else
		map->f_num = keycode - KEYBOARD_DIGITS_BASE_NUM;
	// ft_bzero(map->str, ft_strlen(map->str));
	mlx_clear_window(map->mlx_ptr, map->win_ptr);
	ft_draw_fractol(map);
}

static	int 		ft_key_hook(int keycode, t_map *map)
{
	if (keycode == ESC)
		exit(0);
	else if ((keycode >= ONE && keycode <= FOUR) || keycode == ZERO)
		ft_get_new_fractol(keycode, map);
	return (0);
}

static	int 		ft_mouse_hook(int mouse_code, int pos_x, int pos_y, t_map *map)
{
	printf("MOUSE_CODE:%d|X:%d|Y:%d\n", mouse_code, pos_x, pos_y);
	printf("SCALING....\n");
	return (0);
}

static	int 		ft_julia_coef(int x, int y, t_map *map)
{
	if (INSIDE_WIN && (map->f_num == 3))
	{
		printf("X:%d and Y:%d\n", x, y);
		map->julia_coef_x = x / (WIDTH / 4) - 2;
		map->julia_coef_y = y / (WIDTH / 4) - 2;
		mlx_clear_window(map->mlx_ptr, map->win_ptr);
		// ft_bzero(map->str, ft_strlen(map->str));
		ft_draw_fractol(map);
	}
	return (0);
}

int			rainbow_color(t_map *map)
{
	int		color;
	int		r;
	int		g;
	int		b;

map->frequency = 0.4;
	map->center = 164;
	map->width = 91;
	map->r = 3;
	map->g = 5;
	map->b = 6;

	r = sin(map->frequency * map->iter
			+ map->r) * map->width
		+ map->center;
	g = sin(map->frequency * map->iter +
			map->g) * map->width
		+ map->center;
	b = sin(map->frequency * map->iter +
			map->b) * map->width
		+ map->center;
	color = ((b >> 16) & 0xFF);
	color = ((g >> 8) & 0xFF);
	color = ((r) & 0xFF);
	return (color);
}


void		ft_draw_fractol(t_map *map)
{
	map->y = 0;
	while (map->y < HEIGHT)
	{
		map->x = 0;
		while (map->x < WIDTH)
		{
			map->iter = 0;
			map->function[map->f_num](map);
			mlx_pixel_put(map->mlx_ptr, map->win_ptr, map->x, map->y, rainbow_color(map));
			// if (map->iter < map->max_iter)
			// {
			// 	map->str[map->x * 4 + map->y * map->sl] = 124;
			// 	map->str[map->x * 4 + map->y * map->sl + 1] = 12;
			// 	map->str[map->x * 4 + map->y * map->sl + 2] = 79;
			// }
			// else
			// {
			// 	map->str[map->x * 4 + map->y * map->sl] = 25;
			// 	map->str[map->x * 4 + map->y * map->sl + 1] = 52;
			// 	map->str[map->x * 4 + map->y * map->sl + 2] = 125;
			// }
			map->x++;
		}
		map->y++;
	}
	// mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->img_ptr, 0, 0);
}

int		main(int argc, char const *argv[])
{
	int			fractol_num;
	t_map		map;

	if (argc == 2)
	{
		fractol_num = ft_is_fractol(argv[1]);
		if (fractol_num > -1)
		{
			fractol_init(fractol_num, (char*)argv[1], &map);
			ft_draw_fractol(&map);
			mlx_hook(map.win_ptr, 2, 0, ft_key_hook, &map);
			mlx_hook(map.win_ptr, 6, 0, ft_julia_coef, &map);
			mlx_mouse_hook(map.win_ptr, ft_mouse_hook, &map);
			mlx_loop(map.mlx_ptr);
			return 0;
		}
	}
	ft_throw_exception(USAGE_STR);
}