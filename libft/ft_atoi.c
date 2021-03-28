/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwayfare <bwayfare@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 00:48:14 by bwayfare          #+#    #+#             */
/*   Updated: 2021/03/28 23:51:43 by bwayfare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_gofast(char **str)
{
	while (*str && (**str == ' ' || **str == '\n' || **str == '\t' ||
		**str == '\v' || **str == '\f' || **str == '\r'))
		(*str)++;
	return (*str);
}

char		*ft_znak(char **str, int *znak)
{
	if (**str == '-')
	{
		(*str)++;
		*znak *= -1;
	}
	else if (**str == '+')
		(*str)++;
	return (*str);
}

void			ft_getres(char **str, long int *res)
{
	while (**str && **str >= '0' && **str <= '9')
	{
		*res = *res * 10 + (**str - '0');
		(*str)++;
	}
}

int				ft_atoi(char **str)
{
	long int	res;
	int			znak;
	int			i;

	res = 0;
	znak = 1;
	*str = ft_gofast(str);
	*str = ft_znak(str, &znak);
	ft_getres(str, &res);
	if (res > 2147483647 && znak == 1)
		return (-1);
	else if (res > -2147483648 && znak == -1)
		return (0);
	else
		return (res * znak);
}
