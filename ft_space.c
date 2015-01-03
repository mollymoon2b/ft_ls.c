/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_space.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-bonn <ade-bonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/25 09:11:01 by ade-bonn          #+#    #+#             */
/*   Updated: 2014/12/02 04:40:29 by ade-bonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_add_space_endl(char *str)
{
	ft_putchar(' ');
	ft_putendl(str);
}

void	ft_add_space(int space, char *info, int i)
{
	if (info != NULL)
	{
		space = space - ft_strlen(info) + i;
		while (space >= 0)
		{
			ft_putchar(' ');
			space--;
		}
		ft_putstr(info);
	}
}

void	ft_init_space(t_steve *list, t_size **space)
{
	(*space) = (t_size *)malloc(sizeof(t_size));
	(*space)->link = 0;
	(*space)->uid = 0;
	(*space)->guid = 0;
	(*space)->space = 0;
	(*space)->date = 0;
	while (list != NULL)
	{
		if (list->link)
			(*space)->link = ((*space)->link < ft_strlen(ft_itoa(list->link))
				? ft_strlen(ft_itoa(list->link)) : (*space)->link);
		if (list->space)
			(*space)->space = ((*space)->space < ft_strlen(ft_itoa(list->space))
				? ft_strlen(ft_itoa(list->space)) : (*space)->space);
		if (list->date)
			(*space)->date = ((*space)->date < ft_strlen(list->date)
				? ft_strlen(list->date) : (*space)->date);
		if (list->group)
			(*space)->guid = ((*space)->guid < ft_strlen(list->group)
				? ft_strlen(list->group) : (*space)->guid);
		if (list->user)
			(*space)->uid = ((*space)->uid < ft_strlen(list->user)
				? ft_strlen(list->user) : (*space)->uid);
		list = list->next;
	}
}

void	ft_add_ls_l(t_steve *list, t_opts *opt, t_size *space)
{
	while (list != NULL)
	{
		if (opt->a == 1 || list->file[0] != '.')
		{
			ft_putstr(list->access);
			ft_add_space(space->link, ft_itoa(list->link), 1);
			ft_add_space(space->uid, list->user, 0);
			ft_add_space(space->guid, list->group, 1);
			ft_add_space(space->space, ft_itoa(list->space), 1);
			ft_add_space(space->date, list->date, -1);
			ft_add_space_endl(list->file);
		}
		list = list->next;
	}
}

void	ft_l(t_steve *list, t_opts *opt)
{
	int		total;
	t_steve	*tmp;
	t_size	*space;

	total = 0;
	space = NULL;
	if (ft_ls_l(list) == 0)
	{
		tmp = list;
		while (tmp != NULL)
		{
			total = total + tmp->block;
			tmp = tmp->next;
		}
		free(tmp);
		ft_putstr("total ");
		ft_putnbr(total);
		write(1, "\n", 1);
		ft_init_space(list, &space);
		ft_add_ls_l(list, opt, space);
	}
	while (list != NULL)
		list = list->next;
}
