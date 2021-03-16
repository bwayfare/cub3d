#include <stdio.h>
#include "cub3d.h"

void ft_createmap(t_list **list, int size)
{
	int i = 0;
	t_list *head = *list;
	t_mprms mprms;
	char **map;

	map = ft_calloc(size + 1, sizeof(char *));
	struct_init(&mprms);
	while (head)
	{
		map[i++] = head->content;
		head = head->next;
	}
	i = 0;
//	while (map[i])
//		ft_putendl_fd(map[i++], 1);
//	i = 0;
	while ((parse_line(&mprms, map[i]) != -1) && (ft_check_full(&mprms) != 8))
	{
		printf("%s\n", map[i]);
		i++;
	}
	printf("%s\n", map[i]);

	return;
}

int main(int argc, char **argv) {
    t_list *list = NULL;
    char *line;
    int fd;
	argc = 2;
	argv[1] = "/home/bwayfare/C_Project/cub3D/map1.cub";
    fd = open(argv[1], O_RDONLY);
    line = NULL;
    while (get_next_line(fd, &line) != 0)
	{
    	ft_lstadd_back(&list, ft_lstnew(line));
	}
	ft_lstadd_back(&list, ft_lstnew(line));
	ft_createmap(&list, ft_lstsize(list));
	close(fd);
	char tmp[22] = "1    32  , 7   ,  58\0";
	char *temp = tmp;
	temp += 7;
//	printf("\n%d\n", ft_jmp_sp(&temp));
	//ft_trimm_sp(&temp);
	//printf("\n%s\n", temp);
    return 0;
}
