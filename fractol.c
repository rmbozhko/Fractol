#include "fractol.h"

void				ft_handle_win_params(t_map *map, const char *value, bool flag)
{
	int			temp;

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