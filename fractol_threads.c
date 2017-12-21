#include "fractol.h"

void		ft_draw_fractol(void *map)
{
	t_map		*temp;

	temp = (t_map*)map;
	while (temp->threads_info[temp->threads->thread_id].y_start < temp->threads_info[temp->thread_id].y_end)
	{
		temp->threads_info[temp->threads->thread_id].x_start = 0;
		while (temp->threads_info[temp->threads->thread_id].x_start < WIDTH)
		{
			temp->threads_info[temp->threads->thread_id].iter = 0;
			temp->function[temp->f_num](temp);
			temp->threads_info[temp->threads->thread_id].x_start++;
		}
		temp->threads_info[temp->threads->thread_id].y_start++;
	}
	mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->img_ptr, 0, 0);
}

int			ft_get_thread_range(size_t *start, size_t *end, unsigned range)
{
	static size_t		temp = 0;

	*start = temp;
	temp += range;
	*end = temp++;
}

t_threads_info		*ft_get_threads_info(void)
{
	t_threads_info		*temp;
	size_t				i;

	i = 0;
	temp = (t_threads_info*)malloc(sizeof(t_threads_info) * THREADS_NUM);
	while (i < THREADS_NUM)
	{
		temp[i]->thread_id = i;
		ft_get_thread_range(&temp[i]->y_start, &temp[i]->y_end, (unsigned)HEIGHT / THREADS_NUM);
		i++;
	}
	return (temp);
}

void				ft_threading_drawing(void *map)
{
	int			i;
	pthread_t 	tid;

	i = 0;
	while (i < THREADS_NUM)
	{
		pthread_create(&tid, NULL, ft_draw_fractal, map);
		i++;
	}
}