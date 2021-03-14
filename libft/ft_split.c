/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwayfare <bwayfare@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 00:51:59 by bwayfare          #+#    #+#             */
/*   Updated: 2021/02/28 20:17:05 by bwayfare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_free(char **res, size_t i)
{
	while ((int)i >= 0)
	{
		free(res[i]);
		res[i] = NULL;
		i--;
	}
	free(res);
	res = NULL;
	return (NULL);
}

size_t	ft_column(const char *s, char c)
{
	size_t	i;
	size_t	f;
	size_t	j;

	i = 0;
	f = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == c && f == 1)
			f = 0;
		if (s[i] != c && f == 0)
		{
			f = 1;
			j++;
		}
		i++;
	}
	return (j);
}

char	**ft_creat(char **res, const char *s, char c, size_t col)
{
	size_t	end;
	size_t	i;
	size_t	beg;

	end = 0;
	i = 0;
	beg = 0;
	while (s[end++] != '\0')
	{
		if (s[beg] == c)
		{
			beg++;
			end = beg;
		}
		else if (s[end] == c || s[end] == '\0')
		{
			res[i] = ft_substr(s, beg, end - beg);
			if (res[i] == NULL)
				return (ft_free(res, col));
			beg = end;
			i++;
		}
	}
	res[i] = NULL;
	return (&res[0]);
}

char	**ft_split(char const *s, char c)
{
	size_t	column;
	char	**res;

	if (!s)
		return (NULL);
	column = ft_column(s, c);
	res = (char **)malloc((column + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	res = ft_creat(res, s, c, column);
	return (res);
}
