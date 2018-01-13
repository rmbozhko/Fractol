#include "fractol.h"

void		ft_get_threads_info(t_map *map)
{
	t_threads_info		temp[THREADS_NUM];
	size_t				i;
	unsigned			range;
	pthread_t 			p_arr[THREADS_NUM];

	i = 0;
	range = (unsigned)HEIGHT / THREADS_NUM;
	while (i < THREADS_NUM)
	{
		temp[i].map = map;
		temp[i].y_start = (i > 0) ? temp[i - 1].y_end + 1 : 0;
		temp[i].y_end = (i > 0) ? temp[i - 1].y_end + range : range;
		pthread_create(&(p_arr[i]), NULL, (void*(*)(void*))ft_draw_fractol, &(temp[i]));
		i++;
	}
	i = 0;
	while (i < THREADS_NUM)
	{
		pthread_join(p_arr[i], NULL);
		i++;
	}
	// mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->img_ptr, 0, 0);
}

// void				ft_threading_drawing(void *map)
// {
// 	size_t			i;
// 	pthread_t 		tid;

// 	i = 0;
// 	while (i < THREADS_NUM)
// 	{
// 		pthread_create(&tid, NULL, (void*(*)(void*))ft_draw_fractol, (void*)map);
// 		i++;
// 	}
// }
