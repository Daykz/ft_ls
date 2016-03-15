#include "ft_ls.h"

t_list				*ft_ls(char *str, t_list *list, t_opt *opt)
{
	DIR 			*dir;
	struct dirent	*ret;

	dir = opendir(str);
	while ((ret = readdir(dir)))
		list_add_next(&list, link_init((void *)ret->d_name));
	closedir(dir);
	if (opt->t == 1)
		sort_times(list, str);
	else
		sort_files(list);
	return (list);
}

int 				check_valid(char *param, t_opt *opt)
{
	DIR 			*dir;
	struct stat		buf;

	if (param[0] == '-')
		return (0);
	dir = opendir(param);
	if (dir == NULL)
	{
		if (lstat(param, &buf) == -1)
		{
			printf("ls: %s: No such file or directory\n", param);
			return (0);
		}
	}
	else if (dir == NULL)
	{
		printf("ls: %s: No such file or directory\n", param);
		return (0);
	}
	if (dir != NULL)
	{
		opt->repert = 1;
		closedir(dir);
	}
	else
		opt->file = 1;
	return (1);
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
	int 			i;

	list = NULL;
	if (ac == 1)
		easy_ls(list);
	else
	{
		init_opt(&opt);
		i = check_param(av, &opt);
		while (i < ac)
		{
			check_valid(av[i], &opt);
			i++;
		}
		ls_files(av, &opt);
		ls_folder(av, &opt);
	}
	return (0);
}
