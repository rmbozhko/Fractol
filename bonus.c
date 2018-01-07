#include "fractol.h"

unsigned char *raw_image = NULL;

int width = 1088;//1590;//2400;
int height = 1084;//1584;//3200;
int bytes_per_pixel = 3;   /* or 1 for GRACYSCALE images */
int color_space = JCS_RGB; /* or JCS_GRAYSCALE for grayscale images */

int read_jpeg_file( char *filename )
{
        struct jpeg_decompress_struct cinfo;
        struct jpeg_error_mgr jerr;

        JSAMPROW row_pointer[1];

        FILE *infile = fopen( filename, "rb" );
        unsigned long location = 0;
        int i = 0;

        if ( !infile )
        {
                printf("Error opening jpeg file %s\n!", filename );
                return -1;
        }

        cinfo.err = jpeg_std_error( &jerr );

        jpeg_create_decompress( &cinfo );

        jpeg_stdio_src( &cinfo, infile );

        jpeg_read_header( &cinfo, TRUE );


        jpeg_start_decompress( &cinfo );
        printf("components = %d|%d|%d\n", cinfo.num_components, cinfo.output_width, cinfo.output_height);

        raw_image = (unsigned char*)malloc( cinfo.output_width*cinfo.output_height*cinfo.num_components);

        row_pointer[0] = (unsigned char *)malloc( cinfo.output_width*cinfo.num_components );

        while( cinfo.output_scanline < cinfo.image_height)
        {
        //printf("width:%d|height:%d|components:%d\n", cinfo.output_width, cinfo.output_height, cinfo.num_components);
                jpeg_read_scanlines( &cinfo, row_pointer, 1 );
                for( i=0; i<cinfo.image_width*cinfo.num_components;i++)
                        raw_image[location++] = row_pointer[0][i];
        }
        jpeg_finish_decompress( &cinfo );
        jpeg_destroy_decompress( &cinfo );
        free( row_pointer[0] );
        fclose( infile );

        return 1;
}

int write_jpeg_file( char *filename )
{
        struct jpeg_compress_struct cinfo;
        struct jpeg_error_mgr jerr;

        JSAMPROW row_pointer[1];
        FILE *outfile = fopen( filename, "wb" );

        if ( !outfile )
        {
                printf("Error opening output jpeg file %s\n!", filename );
                return -1;
        }
        cinfo.err = jpeg_std_error( &jerr );
        jpeg_create_compress(&cinfo);
        jpeg_stdio_dest(&cinfo, outfile);


        cinfo.image_width = width;
        cinfo.image_height = height;
        cinfo.input_components = bytes_per_pixel;
        cinfo.in_color_space = color_space;

        jpeg_set_defaults( &cinfo );

        jpeg_start_compress( &cinfo, TRUE );
        // bzero(raw_image, cinfo.next_scanline * cinfo.image_width *  cinfo.input_components);
        while( cinfo.next_scanline < cinfo.image_height)
        {
                // printf("scanline:%d|width:%d|components:%d\n", cinfo.next_scanline, cinfo.image_width, cinfo.input_components);
                row_pointer[0] = &raw_image[ cinfo.next_scanline * cinfo.image_width *  cinfo.input_components];
                //printf("%d:%u\n", cinfo.next_scanline, &raw_image[ cinfo.next_scanline * cinfo.image_width *  cinfo.input_components]);
                jpeg_write_scanlines( &cinfo, row_pointer, 1 );
        //      printf("scanline:%d|height:%d\n", cinfo.next_scanline, cinfo.image_height);
        }

        jpeg_finish_compress( &cinfo );
        jpeg_destroy_compress( &cinfo );
        fclose( outfile );

        return 1;
}

unsigned char   *ft_get_proper(t_map *map)
{
    unsigned char       *temp;
    size_t              i;
    size_t              j;
    unsigned long       len;
    
    i = 0;
    j = 0;
    len = map->win_height * map->sl;
    temp = (unsigned char*)malloc(sizeof(char) * map->win_height * map->win_width * bytes_per_pixel + 1);
    // ft_bzero(temp, map->win_height * map->win_width * bytes_per_pixel);
    while (i < len && j < len)
    {
        temp[i++] = (unsigned char)map->str[j++];
        if (!(j % 4))
        {
            printf("LEN:%lu|J:%zu\n", len, j);
            j++;
        }
    }
    temp[i] = '\0';
    return (temp);
}

unsigned char       *ft_to_bgr(unsigned char *str, t_map *map)
{
    unsigned char       c;
    size_t              i;
    size_t              j;
    unsigned long       len;
    unsigned char       *temp;

    i = 0;
    j = 0;
    len = sizeof(char) * map->win_height * map->win_width * bytes_per_pixel;
    temp = (unsigned char*)malloc(len + 1);
    while (j < len)//(i < len) //&& j < len)
    {
        temp[j] = str[i + 2];
        temp[j + 1] = str[i + 1];
        temp[j + 2] = str[i];
        // c = str[i];
        // str[i] = str[i + 2];
        // str[i + 2] = c;
        i += 3;
        j += 3;
        printf("HERE!\n");
    }
    temp[j] = '\0';
    return (temp);
}

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
    struct      jpeg_compress_struct cinfo;
    struct      jpeg_error_mgr jerr;
    JSAMPROW    row_pointer[1];
    FILE        *outfile;

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
    cinfo.input_components = bytes_per_pixel;
    cinfo.in_color_space = color_space;

    jpeg_set_defaults(&cinfo);
    jpeg_start_compress(&cinfo, TRUE);
    unsigned char *temp = ft_get_proper(map);
    unsigned char *lol = ft_to_bgr(temp, map);
    printf("RESULT:%d\n", ft_strcmp(temp, lol));
    while(cinfo.next_scanline < cinfo.image_height)
    {
            // printf("scanline:%d|width:%d|components:%d\n", cinfo.next_scanline, cinfo.image_width, cinfo.input_components);
            // row_pointer[0] = &map->str[cinfo.next_scanline * cinfo.image_width * cinfo.input_components];
            // row_pointer[0] = &map->str[cinfo.next_scanline * cinfo.image_width * (cinfo.input_components + 1)];
            row_pointer[0] = &temp[cinfo.next_scanline * cinfo.image_width * cinfo.input_components];
            printf("%d:%u\n", cinfo.next_scanline, &raw_image[ cinfo.next_scanline * cinfo.image_width *  cinfo.input_components]);
            jpeg_write_scanlines(&cinfo, row_pointer, 1);
    //      printf("scanline:%d|height:%d\n", cinfo.next_scanline, cinfo.image_height);
    }

    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);
    fclose(outfile);
    printf("Printscreen!\n");
    return 1;
}

// int main()
// {
//   char *infilename = "fractol.jpg", *outfilename = "lol.jpg";

//   if( read_jpeg_file( infilename ) > 0 )
//     {
//       if( write_jpeg_file( outfilename ) < 0 ) return -1;
//     } else {
//     return -1;
//   }

//   return 0;
// }
