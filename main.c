#include <stdio.h>
#include "cub3d.h"

int ft_creat_mprms(char *argv, char *line)
{
	t_mprms mprms;
	int fd;

	struct_init(&mprms);
	if (!(fd = open(argv, O_RDONLY)))
		return (0);
	while ((get_next_line(fd, &line) > 0) &&
			(parse_line(&mprms, line) != -1) && (ft_check_full(&mprms) != 8))
		free(line);
	free(line);
	clean_struct(&mprms);
	return (1);
}

int main(int argc, char **argv) {
	argc = 2;
	argv[1] = "/home/bwayfare/C_Project/cub3D/map1.cub";
	ft_creat_mprms(argv[1], NULL);

    return 0;
}
