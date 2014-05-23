/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytailor <ytailor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/16 18:12:08 by ytailor           #+#    #+#             */
/*   Updated: 2014/05/18 22:58:02 by ytailor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVEUR_H
# define SERVEUR_H
# include <unistd.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/socket.h>
# include <netdb.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "libft/includes/libft.h"

typedef struct				s_serveur
{
	int						port;
	int						sock;
	int						cs;
	unsigned int			cslen;
	struct protoent			*proto;
	struct sockaddr_in		sin;
	struct sockaddr_in		csin;
	int						r;
	char					*str;
	char					buf[1024];
	char					**arg;
	char					*limit;
	char					*cwd;
	pid_t					pid;
}							t_serveur;

typedef struct				s_tab
{
	char					*cmd;
	char					*(*func)(t_serveur *);
}							t_tab;

/*
**	ft_serveur.c
*/
void						ft_init(t_serveur *d);
int							ft_error(int nb);
int							ft_create_serveur(t_serveur *d);
char						*ft_check_commande(t_serveur *d);

/*
**	ft_actions.c
*/
char						*ft_quit(t_serveur *d);
char						*ft_ls(t_serveur *d);
char						*ft_cd(t_serveur *d);
char						*ft_pwd(t_serveur *d);

/*
**	ft_actions2.c
*/
char						*ft_get(t_serveur *d);
char						*ft_put(t_serveur *d);

#endif
