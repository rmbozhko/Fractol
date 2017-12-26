#include "fractol.h"

// void		*ft_draw_fractol(void *map)
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
// 	return (NULL);
// 	// mlx_put_image_to_window(temp->mlx_ptr, temp->win_ptr, temp->img_ptr, 0, 0);
// }

t_threads_info		**ft_get_threads_info(t_map *map)
{
	t_threads_info		**temp;
	size_t				i;
	unsigned			range;
	size_t				start;
	pthread_t 			p_arr[THREADS_NUM];

	i = 0;
	temp = (t_threads_info**)malloc(sizeof(t_threads_info*) * THREADS_NUM);
	range = (unsigned)HEIGHT / THREADS_NUM;
	start = 0;
	while (i < THREADS_NUM)
	{
		temp[i] = (t_threads_info*)malloc(sizeof(t_threads_info));
		temp[i]->thread_id = i;
		// temp[i]->y_start = (i > 0) ? temp[i - 1]->y_end + 1 : start;
		// temp[i]->y_end = (i > 0) ? temp[i - 1]->y_end + range : range;
		// printf("THREAD_ID:%zu|start:%zu|end:%zu\n", i, temp[i]->y_start, temp[i]->y_end);
		pthread_create(&p_arr[i], NULL, (void*(*)(void*))ft_draw_fractol, (void*)map);
		i++;
	}
	i = 0;
	while (i < THREADS_NUM)
	{
		pthread_join(p_arr[i], NULL);
		i++;
	}
	// mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->img_ptr, 0, 0);
	return (temp);
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
