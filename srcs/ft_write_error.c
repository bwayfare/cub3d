/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwayfare <bwayfare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 00:22:05 by bwayfare          #+#    #+#             */
/*   Updated: 2021/04/23 01:05:00 by bwayfare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int		put_rtfm(char *str)
{
	write(1, str, ft_strlen(str));
	exit(0);
}

int		ft_exit(void)
{
	exit(0);
}