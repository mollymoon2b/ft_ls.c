/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-bonn <ade-bonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/25 11:38:44 by ade-bonn          #+#    #+#             */
/*   Updated: 2014/12/10 12:09:13 by ade-bonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <pwd.h>
# include <time.h>
# include <grp.h>
# include <sys/types.h>
# include "libft/libft.h"
# include <errno.h>

typedef struct		s_steve
{
	char			*file;
	char			*opt;
	char			*path;
	struct s_steve	*next;
	char			*group;
	char			*date;
	char			*user;
	int				link;
	int				space;
	char			*access;
	time_t			time;
	blkcnt_t		block;
	char			readlink;
	char			*mode;
}					t_steve;

typedef struct		s_opts
{
	int				l;
	int				gr;
	int				a;
	int				r;
	int				t;
	int				opt;
}					t_opts;

typedef struct		s_size
{
	int				link;
	int				uid;
	int				guid;
	int				space;
	int				date;
	int				file;
}					t_size;

char				*ft_path_steve(char *path);
int					ft_time(t_steve **list, t_steve *tmp2, t_opts *opts);
int					ft_time2(t_steve **list, t_steve *tmp2, t_opts *opt);
void				fs(t_steve **list, char *name, char *path, t_opts *opts);
void				ft_find(char *path, t_steve **list, t_opts *opts, int rec);

void				ft_ls_access(t_steve *list, struct stat info);
void				ft_ls_date(t_steve *list, struct stat info);
int					ft_ls_l(t_steve *list);
void				ft_ls_l2(t_steve *list);
t_opts				*ft_init_opt(t_opts *opt);

void				ft_opt_error(char *arg, t_opts *opt);
void				ft_what_opt(char *arg, t_opts *opt);
void				ft_ls_opt(char *arg, t_opts *opt, t_steve *list);
void				ft_steve(t_steve *list, t_size **space);

void				ft_add_space_endl(char *str);
void				ft_add_space(int space, char *info, int i);
void				ft_init_space(t_steve *list, t_size **space);
void				ft_add_ls_l(t_steve *list, t_opts *opt, t_size *space);
void				ft_l(t_steve *list, t_opts *opt);

void				ft_ls(t_steve *list, t_opts *opt);
void				ft_add_rec(t_steve *list, t_opts *opt);
void				ft_add_ls(t_steve *list, t_opts *opt);
void				ft_add_r(t_steve **list, t_steve *opt);
void				ft_r(t_steve **list, t_opts *opt);

void				ft_denied(t_steve *list);
void				ft_ls_l3(t_steve *list);
void				ft_readlink(t_steve *list);
void				ft_permission(char *path);
void				ft_init_struct_space(t_size **space);
#endif
