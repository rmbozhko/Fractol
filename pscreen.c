/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pscreen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 18:33:39 by rbozhko           #+#    #+#             */
/*   Updated: 2018/07/21 18:33:41 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

char		*ft_get_fname(const t_map *map)
{
	time_t			rawtime;
	char			*filename;
	char			*temp;
	struct tm		*timeinfo;
	char			*fractol_name;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	filename = ft_get_time_part(asctime(timeinfo));
	temp = ft_strjoin(filename, ".jpg");
	ft_strdel(&filename);
	fractol_name = ft_get_fractol_name(map);
	filename = ft_strjoin(fractol_name, temp);
	ft_strdel(&fractol_name);
	ft_strdel(&temp);
	return (filename);
}

FILE		*ft_get_file(t_map *map)
{
	char		*filename;
	FILE		*outfile;

	filename = ft_get_fname(map);
	outfile = fopen(filename, "wb");
	ft_strdel(&filename);
	if (!outfile)
		ft_throw_exception("Error opening output jpeg file.\n");
	return (outfile);
}

void		ft_init_st(struct jpeg_compress_struct *c, t_map *m, FILE *o)
{
	struct jpeg_error_mgr		jerr;

	c->err = jpeg_std_error(&jerr);
	jpeg_create_compress(c);
	jpeg_stdio_dest(c, o);
	c->image_width = m->win_width;
	c->image_height = m->win_height;
	c->input_components = 3;
	c->in_color_space = JCS_RGB;
	jpeg_set_defaults(c);
	jpeg_start_compress(c, TRUE);
}

int			ft_make_printscreen(t_map *map)
{
	FILE							*outfile;
	struct jpeg_compress_struct		cinfo;
	JSAMPROW						row_pointer[1];
	unsigned char					*temp;

	outfile = ft_get_file(map);
	ft_init_st(&cinfo, map, outfile);
	if ((map->win_height * map->win_width) < ALLOWED_WIN_AREA_FOR_THREADS_COEF)
		temp = ft_get_proper(map);
	else
		temp = ft_get_threads(map, cinfo.input_components, 0, 0);
	while (cinfo.next_scanline < cinfo.image_height)
	{
		row_pointer[0] = &temp[cinfo.next_scanline * cinfo.image_width
			* cinfo.input_components];
		jpeg_write_scanlines(&cinfo, row_pointer, 1);
	}
	jpeg_finish_compress(&cinfo);
	jpeg_destroy_compress(&cinfo);
	fclose(outfile);
	ft_strdel((char**)&temp);
	return (1);
}
