#include "cub3d.h"

void f_get_map(char **line, t_list **list, int *fd, t_mprms *mprms)
{
	if(ft_search_map(*line) != 0)
		free(*line);
	else
		ft_lstadd_back(list, ft_lstnew(*line));
	while (get_next_line(*fd, line) > 0 && ft_search_map(*line) > -1)
		if(ft_search_map(*line) == 0)
			ft_lstadd_back(list, ft_lstnew(*line));
		else
			free(*line);
	if (ft_search_map(*line) == 0)
		ft_lstadd_back(list, ft_lstnew(*line));
	else
		free(*line);
	map_creator(*list, mprms);
}

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

	while (mprms.check && (get_next_line(fd, &line) == 1) &&
			(parse_line(&mprms, line) != -1) && (ft_check_full(&mprms) != 8))
		free(line);

	f_get_map(&line, &list, &fd, &mprms);
	free_list(&list);
	clean_struct(&mprms);
	return (1);
}

int main(int argc, char **argv) {
	if (argc == 2 || argc == 3)
		ft_creat_mprms(argv[1]);
    return 0;
}
