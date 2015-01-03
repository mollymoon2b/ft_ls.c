/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minifct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-bonn <ade-bonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/10 09:53:25 by ade-bonn          #+#    #+#             */
/*   Updated: 2014/12/10 09:53:26 by ade-bonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_denied(t_steve *list)
{
	struct stat info;

	ft_ls_access(list, info);
	ft_putstr_fd("ls:", 2);
	ft_putstr_fd(list->file, 2);
	ft_putendl_fd(": Permission denied", 2);
}

void	ft_permission(char *path)
{
	ft_putstr_fd("ls:", 2);
	ft_putstr_fd(path, 2);
	ft_putendl_fd(": Permission denied", 2);
}

void	ft_ls_l3(t_steve *list)
{
	struct stat		info;
	struct passwd	*tmp;
	struct group	*tmp2;

	lstat(list->path, &info);
	ft_ls_access(list, info);
	ft_ls_date(list, info);
	list->link = info.st_nlink;
	tmp = getpwuid(info.st_uid);
	if (tmp == NULL)
		list->user = ft_strdup(ft_itoa((int)info.st_uid));
	else
		list->user = ft_strdup(tmp->pw_name);
	tmp2 = getgrgid(info.st_gid);
	if (tmp2 == NULL)
		list->group = ft_strdup(ft_itoa((int)info.st_gid));
	else
		list->group = ft_strdup(tmp2->gr_name);
	list->space = info.st_size;
	list->block = info.st_blocks;
	if (list->access[0] == 'l')
		ft_readlink(list);
}

void	ft_readlink(t_steve *list)
{
	char	buf[1024];
	int		len;

	if ((len = readlink(list->file, buf, 1023)) != -1)
	{
		buf[len] = '\0';
		list->file = ft_strjoin(list->file, " -> ");
		list->file = ft_strjoin(list->file, buf);
	}
}
