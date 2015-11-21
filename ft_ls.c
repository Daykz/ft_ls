#include "ft_ls.h"

void	print_list(t_list *list)
{
	if (list)
	{
		while (list)
		{
			ft_putstr((char *)list->data);
			ft_putchar(' ');
			list = list->next;
		}
	}
}

int main(int ac, char **av)
{
	t_list			*list;
	DIR				*dir;
	struct dirent	*ret;

	list = NULL;
	printf("%s\n", av[1]);
	if (ac == 1)
	{
		dir = opendir(".");
		while ((ret = readdir(dir)))
		{
			list_add_next(&list, link_init((void *)(ret->d_name)));
			sort_files(list);
		}
		print_list(list);
		closedir(dir);
	}
	return (0);
}
