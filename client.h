/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytailor <ytailor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/18 22:51:15 by ytailor           #+#    #+#             */
/*   Updated: 2014/05/18 23:00:12 by ytailor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H
# include <unistd.h>
# include <stdlib.h>
# include <sys/socket.h>
# include <netdb.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include "libft/includes/libft.h"

/*
**	ft_client.c
*/

void			ft_get_response(int sock, char *str);
int				ft_error(int nb);
int				ft_create_client(char *addr, int port);

/*
**	ft_get_put.c
*/

void			ft_get_file(int sock, char *file);
void			ft_put_file(int sock, char *file);

#endif
