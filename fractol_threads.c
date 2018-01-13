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

typedef struct s_jpeg
{
	size_t				id;
	size_t				len;
	size_t				y_start;
	size_t				y_end;
	unsigned char		*dest_str;
	unsigned char		*src_str;
} t_jpeg;

static void       *ft_three_bytes_img(void *thread)
{
    t_jpeg   *t;

    t = (t_jpeg*)thread;
    while (t->y_start < t->len && t->y_end < t->len)
    {
    	if (((t->y_end + 1) % 4) == 0)
            t->y_end++;
        // t->dest_str[t->y_start++] = (unsigned char)t->src_str[t->y_end++];
        t->dest_str[t->y_start++] = (unsigned char)t->src_str[t->y_end + 2];
        t->dest_str[t->y_start++] = (unsigned char)t->src_str[t->y_end + 1];
        t->dest_str[t->y_start++] = (unsigned char)t->src_str[t->y_end];
        t->y_end += 3;
        // if (((t->y_end + 1) % 4) == 0)
            // t->y_end++;
    }
    printf("start:%zu|end:%zu\n", t->y_start, t->y_end);
    return (t->dest_str);
}

unsigned char        *ft_get_threads_proper(t_map *map, int bpp)
{
    t_jpeg           	temp[THREADS_NUM];
    size_t              i;
    pthread_t           p_arr[THREADS_NUM];
    unsigned char       *str;
    size_t				range;

    i = 0;
    str = (unsigned char*)malloc(sizeof(unsigned char) * map->win_height * map->win_width * bpp + 1);
    ft_bzero(str, sizeof(unsigned char) * map->win_height * map->win_width * bpp + 1);
    range = 0;
    while (i < THREADS_NUM)
    {
    	temp[i].id = i;
        temp[i].len = (i > 0) ? temp[i - 1].len + ((map->win_height * map->sl) / THREADS_NUM) : ((map->win_height * map->sl) / THREADS_NUM);
        temp[i].y_start = (i > 0) ? range : 0;
        temp[i].y_end = (i > 0) ? temp[i - 1].len : 0;
        temp[i].dest_str = str;
        temp[i].src_str = map->str;
        pthread_create(&p_arr[i], NULL, ft_three_bytes_img, &(temp[i]));
        i++;
        range += (map->win_height * map->win_width * bpp / THREADS_NUM);
    }
    i = 0;
    while (i < THREADS_NUM)
        pthread_join(p_arr[i++], NULL);
    printf("Bonus with threads!\n");
    return (str);
}