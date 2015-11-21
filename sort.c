
#include "ft_ls.h"

void	sort_files(t_list *list)
{
	t_list	*tmp;

	tmp = list;
	if (!tmp)
		return;
	while (tmp->next)
		tmp = tmp->next;
	while (tmp->prev)
	{
		while (ft_strcmp((char *)tmp->data, (char *)tmp->prev->data) <= 0)
		{
			list_swap_data((t_list *)tmp->data, (t_list *)tmp->prev->data);
		}
		tmp = tmp->prev;
	}
}