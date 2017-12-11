#include "libft.h"

size_t			ft_omit_whitespaces(char *str, size_t i)
{
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	return (i);
}
