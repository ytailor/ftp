/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_put.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytailor <ytailor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/18 21:09:32 by ytailor           #+#    #+#             */
/*   Updated: 2014/05/18 22:56:10 by ytailor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void					ft_get_file(int sock, char *file)
{
	int					fd;
	char				*line;

	fd = open(file, O_RDWR | O_APPEND | O_CREAT, 0644);
	while (get_next_line_recv(sock, &line) > 0)
	{
		if (!ft_strcmp(line, "\004"))
		{
			close(fd);
			break ;
		}
		ft_putendl_fd(line, fd);
	}
}

void					ft_put_file(int sock, char *file)
{
	int					fd;
	char				*line;
	int					space;

	space = 0;
	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		if (space)
			send(sock, "\n", 1, 0);
		send(sock, line, ft_strlen(line), 0);
		space = 1;
	}
	send(sock, "\n\004\n", 3, 0);
}
