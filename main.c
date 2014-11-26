/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-bonn <ade-bonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/25 09:29:57 by ade-bonn          #+#    #+#             */
/*   Updated: 2014/11/25 09:33:33 by ade-bonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_ls.h"

int		main(int ac, char **av)
{
	int			i;
	t_opts		*opt;
	t_steve		*list;
	int			rec;

	list = NULL;
	opt = NULL;
	opt = ft_init_opt(opt);
	rec = 0;
	i = 1;
	if (ac == 1 || (ac == 2 && (ft_strcmp(av[1], "--") == 0)))
		ft_find("./", &list, opt, rec);
	else
	{
		while (i < ac)
		{
			ft_ls_opt(av[i], opt, list);
			i++;
		}
	}
	if (opt->opt == 0 && ac != 1)
		ft_find("./", &list, opt, rec);
	return (0);
}
