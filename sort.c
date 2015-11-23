
#include "ft_ls.h"

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