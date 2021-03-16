#include "cub3d.h"

int ft_search_map(char *line)
{
	char *tmp;

	if (!line || *line == '\0')
		return (1);
	tmp = line;
	while (tmp && *tmp == 32)
		tmp++;
	if (*tmp == '0' || *tmp == '1' || *tmp == '2' || *tmp == 'N' ||
			*tmp == 'S' || *tmp == 'E' || *tmp == 'W')
		return (0);
	return (1);
}

void size_map(t_list *list, t_mprms *mprms)
{
	int len;
	int i;

	len = 0;
	i = 0;
	mprms->map.size = ft_lstsize(list);
	while (list)
	{
		if ((len = ft_strlen((char *)list->content)) > mprms->map.len)
			mprms->map.len = len;
		list = list->next;
	}
	mprms->map.map = ft_calloc(mprms->map.size + 1, sizeof (char));
	while(i < mprms->map.size)
	{
		mprms->map.map[i] = ft_calloc(mprms->map.len + 1, sizeof (char));
		i++;
	}
}

void map_copy(char *line, char *mprms, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		if (line[i])
		{
			mprms[i] = line[i];
			i++;
			continue;
		}
		mprms[i] = ' ';
		i++;
	}
}

void input_map(t_list **list, t_mprms *mprms)
{
	t_list *head;
	int i;

	i= 0;
	head = *list;
	while (*list)
	{
		map_copy((*list)->content, mprms->map.map[i], mprms->map.len);
		(*list) = (*list)->next;
		i++;
	}
	while (head)
	{
		free(ft_lstlast(head));
	}
	free(head);
}

int map_creator(t_list **list, t_mprms *mprms)
{
	if (*list && (*list)->content != NULL)
	{
		size_map((*list), mprms);
		input_map(list, mprms);
		return (1);
	}
	return (0);
}