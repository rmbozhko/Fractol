/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 16:32:45 by rbozhko           #+#    #+#             */
/*   Updated: 2018/07/21 18:41:25 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static bool			ft_is_str_numeric(const char *str)
{
	if (ft_strlen(str) == 1)
		return ((!ft_isdigit(str[0])) ? false : true);
	return (false);
}

static void			ft_show_color_options(char **color_arr)
{
	size_t		i;

	i = 0;
	ft_putstr("Choose any allowed color.");
	ft_putendl("To select one, just type its number.");
	while (color_arr[i])
	{
		ft_putnbr(i);
		ft_putstr(". ");
		ft_putstr(color_arr[i]);
		ft_putstr("\t\t");
		i++;
		ft_putnbr(i);
		ft_putstr(". ");
		ft_putendl(color_arr[i]);
		i++;
	}
	ft_putendl("Type \"info\" to review this menu again.");
	ft_putstr("Your choice: ");
}

static char			**ft_get_color_options_arr(void)
{
	char		**arr;

	arr = (char**)malloc(sizeof(char*) * COLOR_OPTIONS_NUM + 1);
	arr[0] = ft_strdup("red");
	arr[1] = ft_strdup("green");
	arr[2] = ft_strdup("blue");
	arr[3] = ft_strdup("yellow");
	arr[4] = ft_strdup("pink");
	arr[5] = ft_strdup("rainbow");
	arr[COLOR_OPTIONS_NUM] = NULL;
	return (arr);
}

static	short		ft_get_custom_color(int status, short option)
{
	char				*line;
	char				**color_option_arr;

	line = ft_strnew(0);
	color_option_arr = ft_get_color_options_arr();
	ft_show_color_options(color_option_arr);
	while ((status = get_next_line(0, &line, ft_strnew(0))) > 0)
	{
		if (ft_is_str_numeric(line))
		{
			option = ft_atoi(line);
			break ;
		}
		else if (!ft_strcmp("info", line))
			ft_show_color_options(color_option_arr);
		else
			ft_putendl_fd("Wrong input.", 2);
		ft_putstr("Your choice: ");
		ft_strdel(&line);
	}
	ft_strdel(&line);
	ft_free_bidarr((char**)color_option_arr, COLOR_OPTIONS_NUM);
	if (status == -1)
		ft_throw_exception("Something bad during reading happened.");
	return (option);
}

void				ft_change_default_color(t_map *map)
{
	short		new_color;

	new_color = ft_get_custom_color(-1, -1);
	if (new_color == 0)
		map->pltt = (t_color){.freq = 0.3F, .center = 128, .width = 127,
			.b_coef = 0, .g_coef = 0, .r_coef = 1};
	else if (new_color == 1)
		map->pltt = (t_color){.freq = 0.3F, .center = 128, .width = 127,
			.b_coef = 0, .g_coef = 1, .r_coef = 0};
	else if (new_color == 2)
		map->pltt = (t_color){.freq = 0.3F, .center = 128, .width = 127,
			.b_coef = 1, .g_coef = 0, .r_coef = 0};
	else if (new_color == 3)
		map->pltt = (t_color){.freq = 0.3F, .center = 128, .width = 127,
			.b_coef = 10, .g_coef = 0, .r_coef = 1};
	else if (new_color == 4)
		map->pltt = (t_color){.freq = 0.3F, .center = 128, .width = 127,
			.b_coef = 1, .g_coef = 0, .r_coef = 1};
	else if (new_color == 5)
		map->pltt = (t_color){.freq = 0.3F, .center = 128, .width = 127,
			.b_coef = 2, .g_coef = 0, .r_coef = 4};
	ft_draw_fractol(map);
}
