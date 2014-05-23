/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_recv.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytailor <ytailor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/18 17:21:11 by ytailor           #+#    #+#             */
/*   Updated: 2014/05/18 20:58:56 by ytailor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include "libft.h"

int				get_next_line_recv(int const fd, char **line)
{
	static t_info	*list;
	t_info			*cur;
	int				result;
	int				len;
	int				ret;

	len = -1;
	if (line == NULL || ft_match_fd(&list, &cur, fd))
		return (-1);
	if (cur->offset != 0)
	{
		if ((result = ft_read_buf(line, cur, &len)) != 0)
			return (result);
	}
	while ((ret = recv(fd, cur->buf, BUFF_SIZE, 0)) > 0)
	{
		cur->offset = ret;
		cur->start = cur->buf;
		if ((result = ft_read_buf(line, cur, &len)) != 0)
			return (result);
	}
	ft_del_fd(&list, cur);
	if (ret == -1)
		return (-1);
	return (len != -1);
}
