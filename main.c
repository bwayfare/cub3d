#include <stdio.h>
#include "cub3d.h"

int ft_creat_mprms(char *argv)
{
	t_mprms mprms;
	int fd;
	t_list *list;
	char *line;

	list = NULL;
	struct_init(&mprms);
	if (!(fd = open(argv, O_RDONLY)))
		return (0);
	while ((get_next_line(fd, &line) > 0) &&
			(parse_line(&mprms, line) != -1) && (ft_check_full(&mprms) != 8))
		free(line);
	free(line);
	while (get_next_line(fd, &line) > 0 && ft_search_map(line))
		free(line);
	if (ft_search_map(line) == 0)
	{
		ft_lstadd_back(&list, ft_lstnew(line));
		while (get_next_line(fd, &line))
			ft_lstadd_back(&list, ft_lstnew(line));
		ft_lstadd_back(&list, ft_lstnew(line));
		map_creator(&list, &mprms);
	}
	while(*(mprms.map.map) != NULL)
	{
		printf("%s\n", *(mprms.map.map));
		free(*(mprms.map.map));
		mprms.map.map++;
	}
	free(mprms.map.map);
	clean_struct(&mprms);
	return (1);
}

int main(int argc, char **argv) {
	if (argc == 2 || argc == 3)
		ft_creat_mprms(argv[1]);
    return 0;
}
