#include "fractol.h"

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
		map->x_offset += OFFSET_NUM * map->speed;
	else if (keycode == KEY_RIGHT)
		map->x_offset -= OFFSET_NUM * map->speed;
	else if (keycode == KEY_DOWN)
		map->y_offset -= OFFSET_NUM * map->speed;
	else
		map->y_offset += OFFSET_NUM * map->speed;
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

int 		ft_key_hook(int keycode, t_map *map)
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
