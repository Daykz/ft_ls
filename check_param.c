/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 15:26:27 by dmathe            #+#    #+#             */
/*   Updated: 2015/11/23 15:26:30 by dmathe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				check_opt(char *param, t_opt *opt)
{
	int 	i;

	i = 1;
	while (param[i])
	{
		if (param[i] == 'a')
			opt->a = 1;
		else if (param[i] == 'r')
			opt->r = 1;
		else if (param[i] == 'R')
			opt->rmaj = 1;
		else if (param[i] == 't')
			opt->t = 1;
		else if (param[i] == 'l')
			opt->l = 1;
		i++;
	}
}

void				init_opt(t_opt *opt)
{
	opt->a = 0;
	opt->r = 0;
	opt->rmaj = 0;
	opt->t = 0;
	opt->l = 0;
}

void				check_param(char **param, t_opt *opt)
{
	int 			i;

	i = 1;
	while (param[i])
	{
		if (param[i][0] == '-')
			check_opt(param[i], opt);
		i++;
	}
}