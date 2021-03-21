#include "cub3d.h"

int ft_ch_elem_map(t_mprms *mprms)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	while (i < mprms->map.size && mprms->check)
	{
		j = 0;
		while (j < mprms->map.len && mprms->check)
		{
			tmp = mprms->map.map[i][j];
			if (tmp != '0')
				if(tmp != '1')
					if (tmp != '2')
						if (tmp != ' ')
					{
						if (tmp == 'N' || tmp == 'W' || tmp == 'S' ||
							tmp == 'E')
						{
							if (mprms->plr.pl == '\0')
								mprms->plr.pl = tmp;
							else
								mprms->check = 0;
						}
						else
							mprms->check = 0;
					}
			j++;
		}
		i++;
	}
	if (mprms->plr.pl == '\0')
		mprms->check = 0;
	return (mprms->check);
}

int ch_wall(t_mprms *mprms)
{
	int		i;
	int		j;
	char	**arr;

	i = 0;
	arr = mprms->map.map;

	while (i < mprms->map.size && mprms->check)
	{
		j = 0;
		while (j < mprms->map.len && mprms->check)
		{
			if (arr[i][j] == ' ')
			{
				if(i > 0 && arr[i - 1][j - 1] && !(arr[i - 1][j - 1] == '\0' ||
				arr[i - 1][j - 1] == ' ' || arr[i - 1][j - 1] == '1'))
					mprms->check = 0;
				if(i != 0 && arr[i - 1][j] && !(arr[i - 1][j] == '\0' ||
				   arr[i - 1][j] == ' ' || arr[i - 1][j] == '1'))
					mprms->check = 0;
				if(i != (mprms->map.size - 1) && i != 0 && arr[i + 1][j + 1] && !(arr[i + 1][j + 1] == '\0' ||
				   arr[i + 1][j + 1] == ' ' || arr[i + 1][j + 1] == '1'))
					mprms->check = 0;
				if(j != 0 && arr[i][j - 1] && !(arr[i][j - 1] == '\0' ||
				   arr[i][j - 1] == ' ' || arr[i][j - 1] == '1'))
					mprms->check = 0;
				if(i != (mprms->map.size - 1) && arr[i][j + 1] && !(arr[i][j + 1] == '\0' ||
				   arr[i][j + 1] == ' ' || arr[i][j + 1] == '1'))
					mprms->check = 0;
				if(i != (mprms->map.size - 1) && j != 0 && arr[i + 1][j - 1] && !(arr[i + 1][j - 1] == '\0' ||
				   arr[i + 1][j - 1] == ' ' || arr[i + 1][j - 1] == '1'))
					mprms->check = 0;
				if(i != (mprms->map.size - 1) && arr[i + 1][j] && !(arr[i + 1][j] == '\0' ||
				   arr[i + 1][j] == ' ' || arr[i + 1][j] == '1'))
					mprms->check = 0;
				if(i != (mprms->map.size - 1) && arr[i + 1][j + 1] && !(arr[i + 1][j + 1] == '\0' ||
				   arr[i + 1][j + 1] == ' ' || arr[i + 1][j + 1] == '1'))
					mprms->check = 0;
				j++;
			}
			else
				j++;
		}
		i++;
	}
	return (mprms->check);
}