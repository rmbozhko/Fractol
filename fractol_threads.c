#include "fractol.h"

// void		ft_draw_fractol(void *map)
// {
// 	t_map		*temp;

// 	temp = (t_map*)map;
// 	while (temp->threads_info[temp->threads->thread_id].y_start < temp->threads_info[temp->thread_id].y_end)
// 	{
// 		temp->threads_info[temp->threads->thread_id].x_start = 0;
// 		while (temp->threads_info[temp->threads->thread_id].x_start < WIDTH)
// 		{
// 			temp->threads_info[temp->threads->thread_id].iter = 0;
// 			temp->function[temp->f_num](temp);
// 			temp->threads_info[temp->threads->thread_id].x_start++;
// 		}
// 		temp->threads_info[temp->threads->thread_id].y_start++;
// 	}
// 	mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->img_ptr, 0, 0);
// }

t_threads_info		**ft_get_threads_info(void)
{
	t_threads_info		**temp;
	size_t				i;
	unsigned			range;
	size_t				start;

	i = 0;
	temp = (t_threads_info**)malloc(sizeof(t_threads_info*) * THREADS_NUM);
	range = (unsigned)HEIGHT / THREADS_NUM;
	start = 0;
	while (i < THREADS_NUM)
	{
		temp[i] = (t_threads_info*)malloc(sizeof(t_threads_info));
		temp[i]->thread_id = i;
		temp[i]->y_start = (i > 0) ? temp[i - 1]->y_end + 1 : start;
		temp[i]->y_end = (i > 0) ? temp[i - 1]->y_end + range : range;
		printf("THREAD_ID:%zu|start:%zu|end:%zu\n", i, temp[i]->y_start, temp[i]->y_end);
		i++;
	}
	return (temp);
}

void				ft_threading_drawing(void *map)
{
	size_t			i;
	pthread_t 		tid;

	i = 0;
	while (i < THREADS_NUM)
	{
		pthread_create(&tid, NULL, (void*(*)(void*))ft_draw_fractol, (void*)map);
		i++;
	}
}
