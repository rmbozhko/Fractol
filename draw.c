#include "fractol.h"

void				ft_get_color(unsigned iter, t_map *map)
{
	// printf("blue:%f\n", COLOR_GEN(map->pltt.b_coef));
	// printf("green:%f\n", COLOR_GEN(map->pltt.g_coef));
	// printf("red:%f\n", COLOR_GEN(map->pltt.r_coef));
	// blue
	map->str[map->x * 4 + map->y * map->sl] = 0;//COLOR_GEN(map->pltt.b_coef);
	// green
	map->str[map->x * 4 + map->y * map->sl + 1] = 55;//COLOR_GEN(map->pltt.g_coef);
	// red
	map->str[map->x * 4 + map->y * map->sl + 2] = 127;//COLOR_GEN(map->pltt.r_coef);
}

// void		ft_draw_fractol(t_map *map)
// {
// 	t_threads_info		*temp;

// 	temp = (t_threads_info*)map;
// 	while (temp->y_start < temp->y_end)
// 	{
// 		temp->x_start = 0;
// 		while (temp->x_start < WIDTH)
// 		{
// 			temp->iter = 0;
// 			temp->function[temp->f_num](temp);
// 			temp->x_start++;
// 		}
// 		temp->y_start++;
// 	}
// }

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
