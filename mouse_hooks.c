/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 14:54:55 by rbozhko           #+#    #+#             */
/*   Updated: 2018/07/21 14:54:59 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int 		ft_mouse_hook(int mouse_code, int pos_x, int pos_y, t_map *map)
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

int 		ft_julia_coef(int x, int y, t_map *map)
{
	if (INSIDE_WIN && (map->f_num == 3 || map->f_num == 1) && !map->pause)
	{
		map->julia_coef_x = ((double)x / (map->win_width / 4)) - 2;
		map->julia_coef_y = ((double)y / (map->win_height / 4)) - 2;
		ft_draw_fractol(map);
	}
	return (0);
}
