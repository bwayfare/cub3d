/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwayfare <bwayfare@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 00:50:28 by bwayfare          #+#    #+#             */
/*   Updated: 2021/02/28 20:17:05 by bwayfare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_getsize(int n)
{
	int	size;

	size = 0;
	while (n != 0)
	{
		size++;
		n = n / 10;
	}
	return (size);
}

char	*ft_createascii(char *res, long n, int size, int len)
{
	res[size] = '\0';
	size--;
	while (size > len)
	{
		if (n > 9)
		{
			res[size] = n % 10 + '0';
			n = n / 10;
		}
		else
		{
			res[size] = n % 10 + '0';
			n = 0;
		}
		size--;
	}
	return (res);
}

char	*ft_itoa(int number)
{
	int		size;
	char	*res;
	long	n;

	n = number;
	size = ft_getsize(number);
	if (n == 0)
		size = 1;
	if (n < 0)
		res = (char *)ft_calloc(sizeof(char), size + 2);
	else
		res = (char *)ft_calloc(sizeof(char), size + 1);
	if (!res)
		return (NULL);
	if (n < 0)
	{
		res[0] = '-';
		return (ft_createascii(res, (n * -1), size + 1, 0));
	}
	else
		return (ft_createascii(res, n, size, -1));
}
