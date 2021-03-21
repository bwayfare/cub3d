#include "cub3d.h"

//int ft_search_map(char *line, t_mprms *mprms, t_list *list, int *res)
//{
//	char *tmp;
//
//	if (!line || *line == '\0')
//	{
//		if (*res == 1)
//			*res = 2;
//		return (1);
//	}
//	tmp = line;
//	while (tmp && *tmp == 32)
//		tmp++;
//	if (*tmp == '1' && *res != 2)
//	{
//		*res = 1;
//		return (0);
//	}
//	else
//	{
//		*res = 2;
//		mprms->check = 0;
//	}
//	return (-1);
//}

int ft_search_map(char *line, t_mprms *mprms, t_list *list, int *res)
{
	char *tmp;

	if (!line || *line == '\0')
		return (1);
	tmp = line;
	while (tmp && *tmp == 32)
		tmp++;
	if (*tmp == '1' && *res != 2)
	{
		*res = 1;
		return (0);
	}
	else
	{
		*res = 2;
		mprms->check = 0;
	}
	return (-1);
}

void size_map(t_list *list, t_mprms *mprms)
{
	int len;
	int i;

	len = 0;
	i = 0;
	mprms->map.size = ft_lstsize(list) + 2;
	while (list)
	{
		if ((len = ft_strlen((char *)(list->content))) > mprms->map.len)
			mprms->map.len = len;
		list = list->next;
	}
	mprms->map.len += 2;
	mprms->map.map = ft_calloc(mprms->map.size + 1, sizeof (char *));
	if(!mprms->map.map)
		mprms->check = 0;
	while(i < mprms->map.size && mprms->check)
	{
		mprms->map.map[i] = ft_calloc(mprms->map.len + 1, sizeof (char));
		if (!mprms->map.map[i])
			mprms->check = 0;
		i++;
	}
}

void map_copy(void *str, char *mprms, int len)
{
	int i;
	char *line;

	i = 0;
	line = (char *)str;
	while (i < len)
	{
		if (line &&*line && i > 0)
		{
			mprms[i] = *line++;
			i++;
			continue;
		}
		mprms[i] = ' ';
		i++;
	}
	mprms[i] = '\0';
}

void input_map(t_list *list, t_mprms *mprms)
{
	int i;

	i = 0;
	while (list)
	{
		if (i > 0)
		{
			map_copy(list->content, mprms->map.map[i], mprms->map.len);
			list = list->next;
		}
		else
			map_copy(NULL, mprms->map.map[i], mprms->map.len);
		i++;
	}
	map_copy(NULL, mprms->map.map[i], mprms->map.len);
	mprms->map.map[i + 1] = NULL;
}

int map_creator(t_list *list, t_mprms *mprms)
{
	if (list)
	{
		size_map(list, mprms);
		input_map(list, mprms);
		return (1);
	}
	return (0);
}