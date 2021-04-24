/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwayfare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 03:26:35 by bwayfare          #+#    #+#             */
/*   Updated: 2021/04/24 14:16:07 by bwayfare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memcpy_gnl(void *dest, void *src, size_t n)
{
	size_t	i;
	char	*pdest;
	char	*psrc;

	i = 0;
	pdest = dest;
	psrc = src;
	if (dest == NULL && src == NULL)
		return (NULL);
	while (i < n)
	{
		pdest[i] = psrc[i];
		i++;
	}
	return (dest);
}

char	*ft_strdup_gnl(char *str)
{
	size_t	len;
	char	*copy;

	len = ft_strlen_gnl(str) + 1;
	if ((copy = malloc(len)) == NULL)
		return (NULL);
	ft_memcpy_gnl(copy, (char *)str, len);
	return (copy);
}

char	*ft_getrem_gnl(char *buf, int fd)
{
	char	*tmp;
	int		rf;

	rf = 1;
	if ((tmp = (char *)malloc(BUFFER_SIZE + 1)) == NULL)
		return (NULL);
	if (!buf)
	{
		if ((rf = read(fd, tmp, BUFFER_SIZE)) < 0)
		{
			free(tmp);
			return (NULL);
		}
		tmp[rf] = '\0';
		buf = ft_strdup_gnl(tmp);
	}
	while (rf && !(ft_strchr_gnl(buf, '\n')))
	{
		rf = read(fd, tmp, BUFFER_SIZE);
		tmp[rf] = '\0';
		buf = ft_strjoin_gnl(buf, tmp);
	}
	free(tmp);
	return (buf);
}

int		get_next_line(int fd, char **line)
{
	static char *buf;
	int			len;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE < 1 || !line)
		return (-1);
	if (!(buf = ft_getrem_gnl(buf, fd)))
		return (-1);
	len = ft_eol_gnl(buf);
	if (ft_strchr_gnl(buf, '\n'))
	{
		tmp = buf;
		*line = ft_substr_gnl(buf, 0, len);
		buf = ft_substr_gnl(tmp, len + 1,
				ft_strlen_gnl(buf) - ft_strlen_gnl(*line));
		free(tmp);
		return (1);
	}
	*line = ft_substr_gnl(buf, 0, len);
	free(buf);
	buf = NULL;
	return (0);
}
