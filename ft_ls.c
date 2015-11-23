#include "ft_ls.h"

int 				main(int ac, char **av)
{
	t_list			*list;
	t_opt			opt;
	DIR				*dir;
	struct dirent	*ret;

	list = NULL;
	(void)av;
	if (ac == 1)
	{
		dir = opendir(".");
		while ((ret = readdir(dir)))
			list_add_next(&list, link_init((void *)ret->d_name));
		sort_files(list);
		print_list_without_point(list);
		closedir(dir);
	}
	else
	{
		init_opt(&opt);
		check_param(av, &opt);
	}
	return (0);
}
