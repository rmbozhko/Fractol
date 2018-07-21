/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pscreen_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 18:33:52 by rbozhko           #+#    #+#             */
/*   Updated: 2018/07/21 18:34:18 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

unsigned char		*ft_get_proper(t_map *map)
{
	unsigned char		*temp;
	size_t				i;
	size_t				j;
	unsigned long		len;

	i = 0;
	j = 0;
	len = map->win_height * map->sl;
	temp = (unsigned char*)malloc(sizeof(char) * map->win_height
			* map->win_width * 3 + 1);
	ft_bzero(temp, sizeof(char) * map->win_height * map->win_width * 3 + 1);
	while (i < len && j < len)
	{
		if (((j + 1) % 4) == 0)
			j++;
		temp[i++] = map->str[j + 2];
		temp[i++] = map->str[j + 1];
		temp[i++] = map->str[j];
		j += 3;
	}
	return (temp);
}

char				**ft_get_months(void)
{
	char		**months;

	months = (char**)malloc(sizeof(char*) * 12 + 1);
	months[0] = ft_strdup("Jan");
	months[1] = ft_strdup("Feb");
	months[2] = ft_strdup("Mar");
	months[3] = ft_strdup("Apr");
	months[4] = ft_strdup("May");
	months[5] = ft_strdup("Jun");
	months[6] = ft_strdup("Jul");
	months[7] = ft_strdup("Aug");
	months[8] = ft_strdup("Sep");
	months[9] = ft_strdup("Oct");
	months[10] = ft_strdup("Nov");
	months[11] = ft_strdup("Dec");
	months[12] = NULL;
	return (months);
}

char				*ft_find_month(const char *str)
{
	size_t		i;
	char		**mon_names;

	i = 0;
	mon_names = ft_get_months();
	while (mon_names[i])
	{
		if (!ft_strcmp(mon_names[i], str))
			break ;
		i++;
	}
	ft_free_bidarr(mon_names, ft_bidlen(mon_names));
	return (ft_itoa(i + 1));
}

char				*ft_get_time_part(const char *curr_time)
{
	char		*res;
	char		*str;
	char		**temp;
	char		**time;
	char		*month;

	temp = ft_strsplit(curr_time, ' ');
	time = ft_strsplit(temp[3], ':');
	res = ft_strjoin(temp[2], "_");
	month = ft_find_month(temp[1]);
	str = ft_strjoin(res, month);
	ft_strdel(&month);
	ft_strdel(&res);
	res = ft_strjoin(str, "_");
	ft_strdel(&str);
	str = ft_strjoin(res, time[0]);
	ft_strdel(&res);
	res = ft_strjoin(str, "_");
	ft_strdel(&str);
	str = ft_strjoin(res, time[1]);
	ft_strdel(&res);
	ft_free_bidarr(temp, ft_bidlen(temp));
	ft_free_bidarr(time, ft_bidlen(time));
	return (str);
}

char				*ft_get_fractol_name(const t_map *map)
{
	char		*fractol_name;

	if (!map->f_num)
		fractol_name = ft_strdup("mandelbrot_");
	else if (map->f_num == 1)
		fractol_name = ft_strdup("io_");
	else if (map->f_num == 2)
		fractol_name = ft_strdup("ship_");
	else if (map->f_num == 3)
		fractol_name = ft_strdup("julia_");
	else if (map->f_num == 4)
		fractol_name = ft_strdup("newton_");
	else
		fractol_name = ft_strdup("sample_");
	return (fractol_name);
}
