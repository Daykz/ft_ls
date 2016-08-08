/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/08 23:18:01 by dmathe            #+#    #+#             */
/*   Updated: 2016/08/08 23:18:03 by dmathe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	display(t_list *file, t_opt *opt)
{
	if (opt->t == 1)
	{
		sort_files(file);
		sort_times_file(file);
	}
	else
		sort_files(file);
	if (opt->r == 1)
		reverse_sort_files(file);
}