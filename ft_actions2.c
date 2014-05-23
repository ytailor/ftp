/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_actions2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytailor <ytailor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/18 19:29:36 by ytailor           #+#    #+#             */
/*   Updated: 2014/05/18 23:00:25 by ytailor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

char	*ft_get(t_serveur *d)
{
	int		fd;
	char	*line;
	int		space;

	space = 0;
	if (d->arg[1])
	{
		if ((fd = open(d->arg[1], O_RDONLY)) < 0)
			return ("ERROR OPEN");
		send(d->cs, "\n\003\n", 3, 0);
		while (get_next_line(fd, &line) > 0)
		{
			if (space)
				send(d->cs, "\n", 1, 0);
			send(d->cs, line, ft_strlen(line), 0);
			ft_strdel(&line);
			space = 1;
		}
		send(d->cs, "\n\004\n", 3, 0);
		return ("SUCCESS");
	}
	return ("ERROR ARG");
}

char	*ft_put(t_serveur *d)
{
	int					fd;
	char				*line;

	send(d->cs, "\n\002\n", 3, 0);
	if ((fd = open(d->arg[1], O_RDWR | O_APPEND | O_CREAT, 0644)) == -1)
		return ("ERROR PUT : Cannot open file");
	while (get_next_line_recv(d->cs, &line) > 0)
	{
		if (!ft_strcmp(line, "\004"))
		{
			close(fd);
			break ;
		}
		ft_putendl_fd(line, fd);
	}
	return ("SUCCESS");
}
