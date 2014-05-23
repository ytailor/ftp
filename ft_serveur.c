/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_serveur.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytailor <ytailor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/18 23:02:27 by ytailor           #+#    #+#             */
/*   Updated: 2014/05/18 23:02:29 by ytailor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

const t_tab		g_tab[] =
{
	{"ls", ft_ls},
	{"quit", ft_quit},
	{"cd", ft_cd},
	{"pwd", ft_pwd},
	{"get", ft_get},
	{"put", ft_put},
	{NULL, NULL}
};

int				ft_create_serveur(t_serveur *d)
{
	int			sock;

	d->proto = getprotobyname("tcp");
	if (!d->proto)
		return (-2);
	sock = socket(PF_INET, SOCK_STREAM, d->proto->p_proto);
	d->sin.sin_family = AF_INET;
	d->sin.sin_port = htons(d->port);
	d->sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (const struct sockaddr *)&d->sin, sizeof(d->sin)) == -1)
		return (-3);
	listen(sock, 42);
	return (sock);
}

int				ft_error(int nb)
{
	if (nb == 1)
		ft_putstr("Usage : ./serveur port\n");
	if (nb == -2)
		ft_putstr("Error : getprotobyname\n");
	if (nb == -3)
		ft_putstr("Error : bind\n");
	return (-1);
}

void			ft_init(t_serveur *d)
{
	d->limit = getcwd(NULL, 0);
	d->cwd = getcwd(NULL, 0);
	signal(SIGCHLD, SIG_IGN);
}

char			*ft_check_commande(t_serveur *d)
{
	int			i;

	i = -1;
	while (g_tab[++i].cmd)
	{
		if (!ft_strcmp(g_tab[i].cmd, d->arg[0]))
			return (g_tab[i].func(d));
	}
	return ("ERROR");
}

int				main(int ac, char **av)
{
	t_serveur	d;

	if (ac != 2)
		return (ft_error(1));
	d.port = ft_atoi(av[1]);
	if ((d.sock = ft_create_serveur(&d)) < 0)
		return (ft_error(d.sock));
	ft_init(&d);
	while (42)
	{
		d.cs = accept(d.sock, (struct sockaddr *)&d.csin, &d.cslen);
		if ((d.pid = fork()) == 0)
		{
			while ((d.r = recv(d.cs, d.buf, 1023, 0)) > 0)
			{
				d.buf[d.r] = '\0';
				d.arg = ft_strsplit(d.buf, ' ');
				d.str = ft_check_commande(&d);
				send(d.cs, d.str, ft_strlen(d.str), 0);
				send(d.cs, "\n\004\n", 3, 0);
			}
		}
	}
	close(d.sock);
	return (0);
}
