/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwayfare <bwayfare@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 00:53:04 by bwayfare          #+#    #+#             */
/*   Updated: 2021/02/28 20:17:05 by bwayfare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_creat_malloc(char const *s, unsigned int start, size_t len)
{
	const char	*end;
	char		*temp;

	end = s;
	while (*end++)
		;
	if ((size_t)(end - &s[start]) >= len)
		temp = (char *)malloc(sizeof(*s) * (len + 1));
	else
		temp = (char *)malloc(sizeof(*s) * (end - &s[start] + 1));
	return (temp);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*temp;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	if (s == 0)
		return (NULL);
	temp = ft_creat_malloc(s, start, len);
	if (!temp)
		return (NULL);
	while (s[i])
	{
		if (i >= start && j < len)
			temp[j++] = s[i];
		i++;
	}
	temp[j] = 0;
	return (temp);
}
