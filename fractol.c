/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 15:03:51 by rbozhko           #+#    #+#             */
/*   Updated: 2018/07/21 17:27:40 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		ft_handle_win(t_map *map, const char *value, bool f)
{
	int			temp;

	if (ft_is_numeric((char*)value) && (ft_strlen(value) <= 4))
	{
		temp = ft_atoi((char*)value);
		if (temp >= ft_atoi(MIN_WIN_SIZE))
		{
			if (f)
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

int			ft_valargs(const char **a, t_map *map, int *pos, int f_num)
{
	int			i;
	char		*temp;

	i = -1;
	temp = NULL;
	while (a[++i])
	{
		if (ft_is_fractol(a[i]) != -1)
		{
			*pos = i + 1;
			f_num = ft_is_fractol(a[i]);
		}
		else
		{
			temp = ft_strsub(a[i], 0, ft_strlen("width:"));
			if (!ft_strcmp(temp, "width:"))
				ft_handle_win(map, a[i] + ft_strlen("width:"), false);
			ft_strdel(&temp);
			temp = ft_strsub(a[i], 0, ft_strlen("height:"));
			if (!ft_strcmp(temp, "height:"))
				ft_handle_win(map, a[i] + ft_strlen("height:"), true);
			ft_strdel(&temp);
		}
	}
	return (f_num);
}

int			main(int argc, char const *argv[])
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
			fractol_num = ft_valargs((argv) + 1, &map, &fractol_pos, -1);
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
			return (0);
		}
	}
	ft_throw_exception(CONCAT);
}
