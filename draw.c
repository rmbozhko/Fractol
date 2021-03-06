/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 17:37:01 by rbozhko           #+#    #+#             */
/*   Updated: 2018/07/21 17:37:02 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void				ft_get_color(unsigned iter, t_map *map)
{
	map->str[map->x * 4 + map->y * map->sl] =
		(unsigned char)COLOR_GEN(map->pltt.b_coef);
	map->str[map->x * 4 + map->y * map->sl + 1] =
		(unsigned char)COLOR_GEN(map->pltt.g_coef);
	map->str[map->x * 4 + map->y * map->sl + 2] =
		(unsigned char)COLOR_GEN(map->pltt.r_coef);
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
	mlx_put_image_to_window(map->mlx_ptr, map->win_ptr,
			map->img_ptr, 0, 0);
}
