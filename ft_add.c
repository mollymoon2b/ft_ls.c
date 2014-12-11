/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-bonn <ade-bonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/25 09:23:28 by ade-bonn          #+#    #+#             */
/*   Updated: 2014/12/02 04:44:23 by ade-bonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_ls(t_steve *list, t_opts *opt)
{
	while (list != NULL)
	{
		if (opt->a == 0 && list->file[0] != '.')
			ft_putendl(list->file);
		else if (opt->a)
			ft_putendl(list->file);
		list = list->next;
	}
}

void	ft_add_gr(t_steve *list, t_opts *opt)
{
	int		rec;
	t_steve	*tmp;

	rec = 0;
	while (list != NULL)
	{
		tmp = NULL;
		if (opt->l == 1)
			ft_ls_l(list);
		if (list->access[0] == 'd' && ft_strcmp(list->file, ".") != 0
			&& ft_strcmp(list->file, "..") != 0)
		{
			ft_putchar('\n');
			ft_putstr(list->path);
			ft_putendl(":");
			ft_find(list->path, &tmp, opt, rec);
		}
		list = list->next;
	}
}

void	ft_add_ls(t_steve *list, t_opts *opt)
{
	if (opt->r)
		ft_r(&list, opt);
	if (opt->l)
		ft_l(list, opt);
	else
		ft_ls(list, opt);
	if (opt->gr)
		ft_add_gr(list, opt);
}

void	ft_add_r(t_steve **list, t_steve *normal)
{
	t_steve		*tmp;

	while (normal)
	{
		tmp = normal->next;
		normal->next = *list;
		*list = normal;
		normal = tmp;
	}
}

void	ft_r(t_steve **list, t_opts *opt)
{
	t_steve *normal;

	if (opt->r)
	{
		normal = *list;
		*list = NULL;
		ft_add_r(list, normal);
	}
}
