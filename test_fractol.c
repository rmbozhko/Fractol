#include "libft/libft.h"
#include "minilibx/mlx.h"

# define WIDTH_1 500
# define HEIGHT_1 500
# define WIDTH_2 700
# define HEIGHT_2 700

int		main(void)
{
	char		*str1 = "Window 1";
	char		*str2 = "Window 2";

	void		*mlx_ptr_1 = mlx_init();
	void		*win_ptr_1 = mlx_new_window(mlx_ptr_1, WIDTH_1, HEIGHT_1, str1);
	// void		*mlx_ptr_2 = mlx_init();
	void		*win_ptr_2 = mlx_new_window(mlx_ptr_1, WIDTH_2, HEIGHT_2, str2);

	// mlx_loop(mlx_ptr_1);
	mlx_loop(mlx_ptr_1);
	return (0);
}