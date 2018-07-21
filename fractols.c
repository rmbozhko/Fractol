/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractols.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 17:37:32 by rbozhko           #+#    #+#             */
/*   Updated: 2018/07/21 17:46:58 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		mandelbrot(struct s_map *map)
{
	t_complex		ft_curr;
	t_complex		ft_prev;
	t_complex		constant;

	constant.real = CALC_REAL;
	constant.im = CALC_IMG;
	ft_prev.real = 0.0;
	ft_prev.im = 0.0;
	while (map->iter < map->max_iter)
	{
		ft_curr.real = ft_prev.real;
		ft_curr.im = ft_prev.im;
		ft_prev.real = ft_curr.real * ft_curr.real
						- ft_curr.im * ft_curr.im + constant.real;
		ft_prev.im = 2.0 * ft_curr.real * ft_curr.im + constant.im;
		if ((ft_prev.real * ft_prev.real + ft_prev.im * ft_prev.im) > 4.0)
		{
			ft_get_color(map->iter, map);
			break ;
		}
		map->iter++;
	}
}

void		ship(struct s_map *map)
{
	t_complex		ft_curr;
	t_complex		ft_prev;
	t_complex		constant;

	constant.real = CALC_REAL;
	constant.im = CALC_IMG;
	ft_prev.real = 0.0;
	ft_prev.im = 0.0;
	while (map->iter < map->max_iter)
	{
		ft_curr.real = ft_prev.real;
		ft_curr.im = ft_prev.im;
		ft_prev.real = ft_curr.real * ft_curr.real
						- ft_curr.im * ft_curr.im + constant.real;
		ft_prev.im = 2.0 * fabs(ft_curr.real) * fabs(ft_curr.im) + constant.im;
		if ((ft_prev.real * ft_prev.real + ft_prev.im * ft_prev.im) > 4.0)
		{
			ft_get_color(map->iter, map);
			break ;
		}
		map->iter++;
	}
}

void		julia(struct s_map *map)
{
	t_complex		ft_curr;
	t_complex		ft_prev;

	ft_prev.real = CALC_REAL;
	ft_prev.im = CALC_IMG;
	while (map->iter < map->max_iter)
	{
		ft_curr.real = ft_prev.real;
		ft_curr.im = ft_prev.im;
		ft_prev.real = ft_curr.real * ft_curr.real
						- ft_curr.im * ft_curr.im + map->julia_coef_x;
		ft_prev.im = 2.0 * ft_curr.real * ft_curr.im + map->julia_coef_y;
		if ((ft_prev.real * ft_prev.real + ft_prev.im * ft_prev.im) > 4.0)
		{
			ft_get_color(map->iter, map);
			break ;
		}
		map->iter++;
	}
}

void		newton(struct s_map *map)
{
	t_complex		ft_curr;
	t_complex		ft_prev;
	double			constant;

	ft_curr.real = CALC_REAL;
	ft_curr.im = CALC_IMG;
	constant = 1.0;
	while (constant > 0.000001 && map->iter < map->max_iter)
	{
		ft_prev.real = ft_curr.real;
		ft_prev.im = ft_curr.im;
		constant = (ft_curr.real * ft_curr.real + ft_curr.im * ft_curr.im) *
			(ft_curr.real * ft_curr.real + ft_curr.im * ft_curr.im);
		ft_curr.real = (2 * ft_curr.real * constant + ft_curr.real
			* ft_curr.real - ft_curr.im * ft_curr.im) / (3.0 * constant);
		ft_curr.im = (2 * ft_curr.im * (constant - ft_prev.real))
			/ (3.0 * constant);
		constant = (ft_curr.real - ft_prev.real)
			* (ft_curr.real - ft_prev.real) + (ft_curr.im - ft_prev.im)
			* (ft_curr.im - ft_prev.im);
		map->iter++;
	}
	if (map->iter != map->max_iter)
		ft_get_color(map->iter, map);
}

void		io(struct s_map *map)
{
	t_complex		ft_curr;
	t_complex		ft_prev;

	ft_curr.real = CALC_REAL;
	ft_curr.im = CALC_IMG;
	while (map->iter < map->max_iter)
	{
		ft_prev.real = ft_curr.real;
		ft_prev.im = ft_curr.im;
		ft_curr.real = ft_prev.real * ft_prev.real * ft_prev.real * ft_prev.real
			+ ft_prev.im * ft_prev.im * ft_prev.im * ft_prev.im -
			6 * ft_prev.real * ft_prev.real * ft_prev.im
			* ft_prev.im + map->julia_coef_x;
		ft_curr.im = 4 * ft_prev.real * ft_prev.real * ft_prev.real
			* ft_prev.im - 4 * ft_prev.real * ft_prev.im * ft_prev.im
			* ft_prev.im + map->julia_coef_y;
		if (ft_prev.real * ft_prev.im > 4 || ft_prev.im * ft_prev.im > 4)
		{
			if ((fabs(ft_curr.real)) > 10 || (fabs(ft_curr.im) > 1000))
				ft_get_color(map->iter, map);
			break ;
		}
		map->iter++;
	}
}
