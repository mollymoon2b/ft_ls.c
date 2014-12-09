/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_l.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-bonn <ade-bonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/25 09:10:37 by ade-bonn          #+#    #+#             */
/*   Updated: 2014/11/25 14:48:53 by ade-bonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_ls_access(t_steve *list, struct stat info)
{
	list->access = (char *)malloc(sizeof(char) * 11);
	if (S_ISREG(info.st_mode))
		list->access[0] = '-';
	if (S_ISLNK(info.st_mode))
		list->access[0] = 'l';
	if (S_ISDIR(info.st_mode))
		list->access[0] = 'd';
	if (S_ISSOCK(info.st_mode))
		list->access[0] = 's';
	if (S_ISFIFO(info.st_mode))
		list->access[0] = 'p';
	if (S_ISCHR(info.st_mode))
		list->access[0] = 'c';
	if (S_ISBLK(info.st_mode))
		list->access[0] = 'b';
	list->access[1] = (info.st_mode & S_IRUSR ? 'r' : '-');
	list->access[2] = (info.st_mode & S_IWUSR ? 'w' : '-');
	list->access[3] = (info.st_mode & S_IXUSR ? 'x' : '-');
	list->access[4] = (info.st_mode & S_IRGRP ? 'r' : '-');
	list->access[5] = (info.st_mode & S_IWGRP ? 'w' : '-');
	list->access[6] = (info.st_mode & S_IXGRP ? 'x' : '-');
	list->access[7] = (info.st_mode & S_IROTH ? 'r' : '-');
	list->access[8] = (info.st_mode & S_IWOTH ? 'w' : '-');
	list->access[9] = (info.st_mode & S_IXOTH ? 'x' : '-');
	list->access[10] = '\0';
}

void		ft_ls_date(t_steve *list, struct stat info)
{
	char	*date;
	time_t	t;

	date = ctime(&(info.st_mtime));
	if ((t = time(&t)) > info.st_mtime)
		list->date = ft_strsub(date, 3, 13);
	else
	{
		list->date = ft_strjoin(ft_strsub(date, 4, 7), " ");
		list->date = ft_strjoin(list->date, ft_strsub(date, 20, 4));
	}
}

void		ft_ls_l2(t_steve *list, struct stat	info)
{
	ft_ls_access(list, info);
	ft_ls_date(list, info);
	list->link = info.st_nlink;
	list->user = ft_strdup((getpwuid(info.st_uid))->pw_name);
	list->group = ft_strdup((getgrgid(info.st_gid))->gr_name);
	list->space = info.st_size;
	list->block = info.st_blocks;
}

int		ft_ls_l(t_steve *list)
{
	struct stat	info;
	t_steve		*tmp;
	int ret;
	struct passwd *lol;

	tmp = list;
	while (tmp != NULL)
	{
		if ((ret = lstat(tmp->path, &info)) == 0)
		{
			ft_ls_access(tmp, info);
			ft_ls_date(tmp, info);
			tmp->link = info.st_nlink;
			//lol=(char *)malloc(sizeof(char) * 10000);
			//if (getpwuid(info.st_uid) == 0)
			//	printf("ERROR GETPWUID\n");
			//printf("---> %p %u\n", getpwuid(info.st_uid), info.st_uid);
			//exit(0);
			lol = getpwuid(info.st_uid);
			if (lol == NULL)
				tmp->user= ft_strdup(ft_itoa((int)info.st_uid));
			else
				tmp->user = ft_strdup(lol->pw_name);
			//tmp->user = ft_strdup(lol);
			tmp->group = ft_strdup((getgrgid(info.st_gid))->gr_name);
			tmp->space = info.st_size;
			tmp->block = info.st_blocks;
		}
		else if ((ret = lstat(tmp->path, &info)) == 0)
			ft_ls_l2(tmp, info);
		else
		{
			ft_ls_access(tmp, info);
			ft_putstr_fd("ls:", 2);
			ft_putstr_fd(tmp->file, 2);
			ft_putendl_fd(": Permission denied", 2);
		}
		tmp = tmp->next;
	}
	return (ret);
}

t_opts		*ft_init_opt(t_opts *opt)
{
	opt = (t_opts *)malloc(sizeof(t_opts));
	opt->l = 0;
	opt->gr = 0;
	opt->a = 0;
	opt->r = 0;
	opt->t = 0;
	opt->opt = 0;
	return (opt);
}
