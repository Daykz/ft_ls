
#include "ft_ls.h"

void	reverse_sort_files(t_list *list)
{
	t_list	*tmp;

	tmp = list;
	if (tmp)
	{
		while (tmp->next)
		{
			if (ft_strcmp((char *)tmp->data, (char *)tmp->next->data) <= 0)
			{
				list_swap_data((t_list *)tmp, (t_list *)tmp->next);
				tmp = list;
			}
			else 
				tmp = tmp->next;
		}
	}
}

void	sort_files(t_list *list)
{
	t_list	*tmp;

	tmp = list;
	if (tmp)
	{
		while (tmp->next)
		{
			if (ft_strcmp((char *)tmp->data, (char *)tmp->next->data) >= 0)
			{
				list_swap_data((t_list *)tmp, (t_list *)tmp->next);
				tmp = list;
			}
			else 
				tmp = tmp->next;
		}
	}
}

void	sort_times(t_list *list, char *str)
{
	t_list *tmp;
	char *path;
	struct stat buf;
	int		**tab;
	int		i;

	i = 0;
	tmp = list;
	tab = (int **)malloc(sizeof(int *) * 4096);
	if (tmp)
	{
		while (tmp->next)
		{
			path = (char *)malloc(sizeof(char) * (ft_strlen(str) + ft_strlen((char *)tmp->data) + 2));
			ft_strcpy(path, str);
			ft_strcat(path, "/");
			ft_strcat(path, (char *)tmp->data);
			lstat(path, &buf);
			tab[i] = (int *)buf.st_mtime;
			i++;
			tmp = tmp->next;
			ft_putstr("SLT");
		}
		i = 0;
		while (tab[i])
		{
			printf("%d\n", *(tab)[i]);
		ft_putstr("BANGBANG");
			i++;
		}
		print_list(list);
	}
}