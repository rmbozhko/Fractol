/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bidarrjoin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 16:34:29 by rbozhko           #+#    #+#             */
/*   Updated: 2018/07/21 16:37:56 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_bidarrjoin(char **arr, size_t l)
{
	char		*t;
	char		*str;
	size_t		i;
	char		**at;
	size_t		j;

	i = 0;
	t = ft_strnew(0);
	ft_bzero(t, sizeof(char*));
	str = t;
	while (i < l && !(j = 0))
	{
		at = ft_strsplit(arr[i++], ' ');
		while (at[j])
		{
			t = ft_strjoin(t, at[j++]);
			ft_strdel(&str);
			str = t;
			(j < ft_bidlen(at) || i != l) ? t = ft_strjoin(t, " ") : 0;
			(j < ft_bidlen(at) || i != l) ? ft_strdel(&str) : 0;
			(j < ft_bidlen(at) || i != l) ? str = t : 0;
		}
		ft_free_bidarr(at, ft_bidlen(at));
	}
	return (t);
}
