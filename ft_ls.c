/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-bonn <ade-bonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/25 09:10:28 by ade-bonn          #+#    #+#             */
/*   Updated: 2014/12/02 04:00:36 by ade-bonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*ft_path_steve(char *path)
{
	int		i;
	char	*dest;

	i = 0;
	if (ft_strlen(path) == 1)
		return (ft_strjoin(path, "/"));
	while (path[i + 1])
		i++;
	if (path[i] != '/')
	{
		dest = ft_strjoin(path, "/");
		return (dest);
	}
	return (path);
}

int		ft_time2(t_steve **list, t_steve *tmp2, t_opts *opt)
{
	t_steve	*tmp;

	tmp = *list;
	if (tmp == NULL)
	{
		*list = tmp2;
		return (0);
	}
	else if ((opt->t == 1 && (tmp2->time > tmp->time
				|| (tmp2->time == tmp->time
				&& ft_strcmp(tmp2->file, tmp->file) < 0)))
				|| (opt->t == 0 && ft_strcmp(tmp2->file, tmp->file) < 0))
	{
		tmp2->next = *list;
		*list = tmp2;
		return (0);
	}
	return (1);
}

int		ft_time(t_steve **list, t_steve *tmp2, t_opts *opt)
{
	t_steve		*tmp;

	tmp = *list;
	if (ft_time2(list, tmp2, opt) == 0)
		return (0);
	while (tmp->next != NULL)
	{
		if ((opt->t == 1 && (tmp2->time > tmp->next->time
			|| (tmp2->time == tmp->next->time
			&& ft_strcmp(tmp2->file, tmp->next->file) < 0)))
			|| (opt->t == 0 && ft_strcmp(tmp2->file, tmp->next->file) < 0))
		{
			tmp2->next = tmp->next;
			tmp->next = tmp2;
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

void	ft_a(t_steve **list, char *name, char *path, t_opts *opt)
{
	t_steve		*file;
	t_steve		*tmp;
	struct stat	info;

	file = (t_steve *)malloc(sizeof(t_steve));
	file->file = ft_strdup(name);
	path = ft_path_steve(path);
	file->path = ft_strjoin(path, file->file);
	stat(file->path, &info);
	file->time = info.st_mtime;
	ft_ls_access(file, info);
	file->next = NULL;
	if (*list == NULL)
		*list = file;
	else
	{
		if (ft_time(list, file, opt) == 1)
		{
			tmp = *list;
			while (tmp->next != NULL)
				tmp = tmp->next;
			tmp->next = file;
		}
	}
}

void	ft_find(char *path, t_steve **list, t_opts *opt, int rec)
{
	DIR				*dir;
	struct dirent	*entree;

	if ((dir = opendir(path)) == NULL)
	{
		if (errno == EACCES)
		{
			ft_permission(path);
		}
		else
		{
			ft_putstr_fd("ls: ", 2);
			ft_putstr_fd(path, 2);
			ft_putendl_fd(": No such file or directory", 2);
			exit(1);
		}
	}
	else
	{
		while ((entree = readdir(dir)) != 0)
			ft_a(list, entree->d_name, path, opt);
		closedir(dir);
	}
	if (rec == 0)
		ft_add_ls(*list, opt);
}
