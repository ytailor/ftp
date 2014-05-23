/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytailor <ytailor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/18 23:02:16 by ytailor           #+#    #+#             */
/*   Updated: 2014/05/18 23:02:19 by ytailor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int						ft_create_client(char *addr, int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;
	struct hostent		*host;

	proto = getprotobyname("tcp");
	if (!proto)
		return (-1);
	if (!(host = gethostbyname(addr)))
		return (-1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr *)host->h_addr));
	if (connect(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		ft_putendl("Connect error");
		return (-1);
	}
	return (sock);
}

int						ft_error(int nb)
{
	if (nb == 1)
		ft_putstr("Usage : ./client addr port\n");
	else if (nb == 2)
		ft_putendl("Error open file");
	return (-1);
}

void					ft_get_response(int sock, char *str)
{
	char				*line;

	while (get_next_line_recv(sock, &line) > 0)
	{
		if (!ft_strcmp(line, "\002"))
		{
			ft_put_file(sock, ft_strsplit(str, ' ')[1]);
			continue ;
		}
		if (!ft_strcmp(line, "\003"))
		{
			ft_get_file(sock, ft_strsplit(str, ' ')[1]);
			continue ;
		}
		if (!ft_strcmp(line, "\004"))
			break ;
		if (!ft_strcmp(line, "\005"))
		{
			ft_putstr("ftp> ");
			continue ;
		}
		if (*line)
			ft_putendl(line);
		ft_strdel(&line);
	}
}

int						main(int ac, char **av)
{
	int					port;
	int					sock;
	char				*line;

	if (ac != 3)
		return (ft_error(1));
	port = ft_atoi(av[2]);
	if ((sock = ft_create_client(av[1], port)) == -1)
		return (-1);
	ft_putstr("ftp> ");
	while (get_next_line(0, &line) > 0)
	{
		if (*line)
		{
			send(sock, line, ft_strlen(line), 0);
			ft_putstr("ftp> ");
			ft_get_response(sock, line);
			if (!ft_strcmp(line, "quit"))
				break ;
			ft_strdel(&line);
		}
		ft_putstr("ftp> ");
	}
	close(sock);
	return (0);
}
