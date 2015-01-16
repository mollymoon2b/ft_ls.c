/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_option.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-bonn <ade-bonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/25 09:10:48 by ade-bonn          #+#    #+#             */
/*   Updated: 2015/01/15 10:06:06 by ade-bonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_opt_error(char *arg, t_opts *opt)
{
	int	i;

	i = 1;
	if (ft_strcmp(arg, "--") == 0)
	{
		opt->opt = 1;
		return ;
	}
	while (arg[i])
	{
		if (arg[i] != 'l' && arg[i] != 'R' && arg[i] != 'a'
			&& arg[i] != 'r' && arg[i] != 't')
		{
			ft_putstr_fd("ls: illegal option -- ", 2);
			ft_putchar_fd(arg[i], 2);
			ft_putchar_fd('\n', 2);
			ft_putendl_fd("usage: ls [-Ralrt] [file ...]", 2);
			exit(1);
		}
		i++;
	}
}

void	ft_what_opt(char *arg, t_opts *opt)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		if (arg[i] == 'l')
			opt->l = 1;
		if (arg[i] == 'R')
			opt->gr = 1;
		if (arg[i] == 'a')
			opt->a = 1;
		if (arg[i] == 'r')
			opt->r = 1;
		if (arg[i] == 't')
			opt->t = 1;
		i++;
	}
}

void	ft_ls_4(t_steve *list, struct stat *info)
{
	if (list->access[0] == 'c' || list->access[0] == 'b')
	{
		list->space = major(info->st_rdev);
		list->space2 = minor(info->st_rdev);
	}
	else
		list->space = info->st_size;
	list->block = info->st_blocks;
	ft_major(list);
}

void	ft_ls_opt(char *arg, t_opts *opt, t_steve *list)
{
	int	rec;

	rec = 0;
	list = NULL;
	if (opt->opt == 0 && arg[0] != '-')
		opt->opt = 1;
	if (opt->opt)
		ft_find(arg, &list, opt, rec);
	else
	{
		ft_opt_error(arg, opt);
		if (opt->opt == 0)
			ft_what_opt(arg, opt);
	}
}

void	ft_major(t_steve *list)
{
	if (list->access[0] == 'l')
		ft_readlink(list);
}
