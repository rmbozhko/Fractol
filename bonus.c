#include "fractol.h"

unsigned char   *ft_get_proper(t_map *map)
{
    unsigned char       *temp;
    size_t              i;
    size_t              j;
    unsigned long       len;
    
    i = 0;
    j = 0;
    len = map->win_height * map->sl;
    temp = (unsigned char*)malloc(sizeof(char) * map->win_height * map->win_width * 3 + 1);
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
    // temp[i] = '\0';
    return (temp);
}

// unsigned char       *ft_to_rgb(unsigned char *str, t_map *map)
// {
//     unsigned char       c;
//     size_t              i;
//     size_t              j;
//     unsigned long       len;
//     unsigned char       *temp;

//     i = 0;
//     j = 0;
//     len = sizeof(char) * map->win_height * map->win_width * 3;
//     temp = (unsigned char*)malloc(len + 1);
//     while (i < len && j < len)
//     {
        
//     }
//     temp[j] = '\0';
//     return (temp);
// }

// unsigned char       *ft_to_rgb(unsigned char *str, t_map *map)
// {
//     unsigned char       c;
//     size_t              i;
//     size_t              j;
//     unsigned long       len;
//     unsigned char       *temp;

//     i = 0;
//     j = 0;
//     len = sizeof(char) * map->win_height * map->win_width * 3;
//     temp = (unsigned char*)malloc(len + 1);
//     while (i < len && j < len)
//     {
//         temp[j++] = str[i + 2];
//         temp[j++] = str[i + 1];
//         temp[j++] = str[i];
//         i += 3;
//     }
//     temp[j] = '\0';
//     return (temp);
// }

char            *ft_find_month(const char *str)
{
    size_t      i;
    const char mon_names[][4] = {"Jan", "Feb", "Mar", "Apr", "May",
    "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    i = 0;
    while (mon_names[i])
    {
        if (!ft_strcmp(mon_names[i], str))
            break ;
        i++;
    }
    return (ft_itoa(i + 1));
}

char            *ft_get_time_part(const char *curr_time)
{
    char        *res;
    char        *str;
    char        **temp;
    char        **time;

    temp = ft_strsplit(curr_time, ' ');
    time = ft_strsplit(temp[3], ':');
    res = ft_strjoin(temp[2], "_");
    str = ft_strjoin(res, ft_find_month(temp[1]));
    ft_strdel(&res);
    res = ft_strjoin(str, "_");
    ft_strdel(&str);
    temp[4] = ft_strsub(temp[4], 0, ft_strlen(temp[4]) - 2);
    str = ft_strjoin(res, temp[4]);
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

char        *ft_get_fractol_name(const t_map *map)
{
    char        *fractol_name;

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

char        *ft_get_fname(const t_map *map)
{
  time_t        rawtime;
  char          *filename;
  char          *temp;
  struct tm     *timeinfo;
  char          *fractol_name;

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

int        ft_make_printscreen(t_map *map)
{
    char        *filename;
    struct      jpeg_compress_struct cinfo; // RGB
    struct      jpeg_error_mgr jerr;
    JSAMPROW    row_pointer[1];
    FILE        *outfile;
    unsigned char *lol;
    unsigned char *temp;

    filename = ft_get_fname(map);
    outfile = fopen(filename, "wb");
    ft_strdel(&filename);
    if (!outfile)
        ft_throw_exception("Error opening output jpeg file.\n");    
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);
    jpeg_stdio_dest(&cinfo, outfile);

    cinfo.image_width = map->win_width;
    cinfo.image_height = map->win_height;
    cinfo.input_components = 3;
    cinfo.in_color_space = JCS_RGB;

    jpeg_set_defaults(&cinfo);
    jpeg_start_compress(&cinfo, TRUE);
    printf("%d\n", ((map->win_height * map->sl) < ALLOWED_WIN_AREA_FOR_THREADS_COEF));
    if ((map->win_height * map->win_width) < ALLOWED_WIN_AREA_FOR_THREADS_COEF)
    {
        temp = ft_get_proper(map);
        // lol = ft_to_rgb(temp, map);
    }
    else
        temp = ft_get_threads_proper(map, cinfo.input_components);
    while(cinfo.next_scanline < cinfo.image_height)
    {
        row_pointer[0] = &temp[cinfo.next_scanline * cinfo.image_width * cinfo.input_components];
        jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }
    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);
    fclose(outfile);
    printf("Printscreen!\n");
    return 1;
}
