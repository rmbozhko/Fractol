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

int			ft_is_fractol(const char *str)
{
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
	ft_draw_fractol(map);
}

static	void		ft_move_fractol(int keycode, t_map *map)
{
	if (keycode == KEY_LEFT)
		map->x_offset -= OFFSET_NUM * map->speed;
	else if (keycode == KEY_RIGHT)
		map->x_offset += OFFSET_NUM * map->speed;
	else if (keycode == KEY_DOWN)
		map->y_offset += OFFSET_NUM * map->speed;
	else
		map->y_offset -= OFFSET_NUM * map->speed;
	ft_draw_fractol(map);
}

static	void		ft_change_speed(int keycode, t_map *map)
{
	if (keycode == 83)
		map->speed = 1;
	else if (keycode == 84)
		map->speed = 2;
	else if (keycode == 85)
		map->speed = 3;
	else if (keycode == 86)
		map->speed = 4;
	else if (keycode == 87)
		map->speed = 5;
	else if (keycode == 88)
		map->speed = 6;
	else if (keycode == 89)
		map->speed = 7;
	else if (keycode == 91)
		map->speed = 8;
	else if (keycode == 92)
		map->speed = 9;
}

static	void		ft_change_zoom(int keycode, t_map *map)
{
	if (ZOOM_BOUNDARY)
	{
		map->zoom += (keycode == PLUS) ? ZOOM_COEF : -ZOOM_COEF;
		ft_draw_fractol(map);
	}
}

static	int 		ft_key_hook(int keycode, t_map *map)
{
	if (keycode == ESC)
		exit(0);
	else if ((keycode >= ONE && keycode <= FOUR) || keycode == ZERO)
		ft_get_new_fractol(keycode, map);
	else if (keycode == SPACE)
	{
		map->max_iter += ITER_STEP;
		ft_draw_fractol(map);
	}
	else if (keycode >= KEY_LEFT && keycode <= KEY_UP)
		ft_move_fractol(keycode, map);
	else if (keycode >= 83 && keycode <= 92 && keycode != 90)
		ft_change_speed(keycode, map);
	else if (keycode == PLUS || keycode == NEG)
		ft_change_zoom(keycode, map);
	else if (keycode == C_LTTR)
		ft_change_default_color(map);
	else if (keycode == P_LTTR)
		map->pause = !map->pause;
	else if (keycode == S_LTTR)
		ft_make_printscreen(map);
	return (0);
}

static	int 		ft_mouse_hook(int mouse_code, int pos_x, int pos_y, t_map *map)
{
	if (mouse_code == 1 || mouse_code == 2)
	{
		map->x_offset += pos_x - (map->win_width / 2);
		map->y_offset += pos_y - (map->win_height  / 2);
		if (ZOOM_BOUNDARY)
			map->zoom += (mouse_code == 1) ? ZOOM_COEF : -ZOOM_COEF;
		ft_draw_fractol(map);
		return (0);
	}
	return (1);
}

static	int 		ft_julia_coef(int x, int y, t_map *map)
{
	if (INSIDE_WIN && (map->f_num == 3 || map->f_num == 1) && !map->pause)
	{
		map->julia_coef_x = ((double)x / (map->win_width / 4)) - 2;
		map->julia_coef_y = ((double)y / (map->win_height / 4)) - 2;
		ft_draw_fractol(map);
	}
	return (0);
}

void				ft_get_color(unsigned iter, t_map *map)
{
	map->str[map->x * 4 + map->y * map->sl] = COLOR_GEN(map->pltt.b_coef);
	map->str[map->x * 4 + map->y * map->sl + 1] = COLOR_GEN(map->pltt.g_coef);
	map->str[map->x * 4 + map->y * map->sl + 2] = COLOR_GEN(map->pltt.r_coef);
}

void				ft_putnstr(const char *str, size_t len)
{
	size_t		i;

	i = 0;
	while (i < len)
		ft_putnbr(str[i++]);
}

void				ft_draw_fractol(t_map *map)
{
	ft_bzero(map->str, map->win_height * map->sl);
	map->y = 0;
	while (map->y < map->win_height)
	{
		map->x = 0;
		while (map->x < map->win_width)
		{
			map->iter = 0;
			(*map->function[map->f_num])(map);
			map->x++;
		}
		map->y++;
	}
	mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->img_ptr, 0, 0);
}

void				ft_handle_win_params(t_map *map, const char *value, bool flag)
{
	unsigned		temp;

	if (ft_is_numeric((char*)value) && (ft_strlen(value) <= 4))
	{
		temp = ft_atoi((char*)value);
		if (temp >= ft_atoi(MIN_WIN_SIZE))
		{
			if (flag)
				map->win_height = (temp <= 1395) ? temp : HEIGHT;
			else
				map->win_width = (temp <= 2560) ? temp : WIDTH;
			return ;
		}
	}
	ft_throw_exception(USAGE_STR);
}

int 				ft_validate_cmd_args(const char **args, t_map *map, int *fractol_pos)
{
	size_t		i;
	char 		*temp;
	int 		fractol_num;

	i = 0;
	temp = NULL;
	fractol_num = -1;
	while (args[i])
	{
		if (ft_is_fractol(args[i]) != -1)
		{
			*fractol_pos = i + 1;
			fractol_num = ft_is_fractol(args[i]);
		}
		else
		{
			temp = ft_strsub(args[i], 0, ft_strlen("width:"));
			if (!ft_strcmp(temp, "width:"))
				ft_handle_win_params(map, args[i] + ft_strlen("width:"), false);
			ft_strdel(&temp);
			temp = ft_strsub(args[i], 0, ft_strlen("height:"));
			if (!ft_strcmp(temp, "height:"))
				ft_handle_win_params(map, args[i] + ft_strlen("height:"), true);
			ft_strdel(&temp);
		}
		i++;
	}
	return (fractol_num);
}

int		main(int argc, char const *argv[])
{
	int			fractol_num;
	t_map		map;
	int			fractol_pos;

	if (argc >= 2)
	{
		map.win_width = WIDTH;
		map.win_height = HEIGHT;
		fractol_pos = 1;
		if (argc > 2)
			fractol_num = ft_validate_cmd_args((argv) + 1, &map, &fractol_pos);
		else
			fractol_num = ft_is_fractol(argv[1]);
		if (fractol_num > -1)
		{
			fractol_init(fractol_num, (char*)argv[fractol_pos], &map);
			ft_draw_fractol(&map);
		 	mlx_hook(map.win_ptr, 2, 0, ft_key_hook, &map);
			mlx_hook(map.win_ptr, 6, 0, ft_julia_coef, &map);
			mlx_mouse_hook(map.win_ptr, ft_mouse_hook, &map);
			mlx_loop(map.mlx_ptr);
			return 0;
		}
	}
	ft_throw_exception(CONCAT);
}