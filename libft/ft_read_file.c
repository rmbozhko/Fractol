/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 21:39:32 by rbozhko           #+#    #+#             */
/*   Updated: 2017/11/12 18:35:28 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char		**ft_realoc_n_copy(char **a, size_t *l, size_t n, size_t m)
{
	char		**temp;
	size_t		i;

	i = 0;
	*l += m;
	temp = (char**)malloc((*l) * sizeof(char*) + 1);
	while (i < n)
	{
		temp[i] = ft_strdup(a[i]);
		i++;
	}
	temp[i] = NULL;
	ft_free_bidarr(a, i);
	return (temp);
}

char				**ft_read_file(const int fd, char **arr)
{
	size_t		i;
	size_t		len;
	char		*line;
	int			status;

	len = 10;
	arr = (char**)malloc(sizeof(char*) * len + 1);
	i = 0;
	line = ft_strnew(0);
	while ((status = get_next_line(fd, &line, ft_strnew(0))) > 0)
	{
		(i == len) ? arr = ft_realoc_n_copy(arr, &len, i, MEMORY_COEF) : 0;
		arr[i++] = ft_strdup(line);
	}
	arr[i] = NULL;
	ft_strdel(&line);
	return ((status == -1) ? NULL : arr);
}
