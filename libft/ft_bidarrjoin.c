#include "libft.h"

char		*ft_bidarrjoin(char **arr, size_t len)
{
	char		*temp;
	char		*str;
	size_t		i;
	char 		**arr_temp;
	size_t		j;

	i = 0;
	temp = ft_strnew(0);
	ft_bzero(temp, sizeof(char*));
	str = temp;
	while (i < len && !(j = 0))
	{
		arr_temp = ft_strsplit(arr[i++], ' ');
		while (arr_temp[j])
		{
			temp = ft_strjoin(temp, arr_temp[j++]);
			ft_strdel(&str);
			str = temp;
			(j < ft_bidlen(arr_temp) || i != len) ? temp = ft_strjoin(temp, " ") : 0;
			(j < ft_bidlen(arr_temp) || i != len) ? ft_strdel(&str) : 0;
			(j < ft_bidlen(arr_temp) || i != len) ? str = temp : 0;
		}
		ft_free_bidarr(arr_temp, ft_bidlen(arr_temp));
	}
	return (temp);
}