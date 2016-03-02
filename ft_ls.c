#include "ft_ls.h"

void 				check_repert(char **param)
{
	DIR 			*dir;
	//struct dirent	*ret;
	int 			i;

	i = 1;
	while (param[i])
	{
		dir = opendir(param[i]);
		if (dir == NULL)
			printf("ls: %s: No such file or directory", param[i]);
		i++;
	}
}

void 				easy_ls(t_list *list)
{
	DIR				*dir;
	struct dirent	*ret;
	
	dir = opendir(".");
	while ((ret = readdir(dir)))
		list_add_next(&list, link_init((void *)ret->d_name));
	sort_files(list);
	print_list_without_point(list);
	closedir(dir);
}

int 				main(int ac, char **av)
{
	t_list			*list;
	t_opt			opt;

	list = NULL;
	if (ac == 1)
		easy_ls(list);
	else
	{
		init_opt(&opt);
		check_param(av, &opt);
		check_repert(av);
	}
	return (0);
}
