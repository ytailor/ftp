/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytailor <ytailor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/18 13:52:14 by ytailor           #+#    #+#             */
/*   Updated: 2014/05/18 21:31:04 by ytailor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

char					*ft_ls(t_serveur *d)
{
	pid_t				pid;
	struct rusage		usage;
	int					status;
	int					option;

	option = 0;
	if ((pid = fork()) == 0)
	{
		close(1);
		dup2(d->cs, 1);
		dup2(d->cs, 2);
		if (execv("/bin/ls", d->arg) == -1)
			return ("ERROR ls");
	}
	else
		wait4(pid, &status, option, &usage);
	send(d->cs, "\005\n", 2, 0);
	return ("SUCCESS");
}

char					*ft_quit(t_serveur *d)
{
	send(d->cs, "SUCCESS", 7, 0);
	send(d->cs, "\n\004\n", 3, 0);
	close(d->cs);
	exit(1);
	return ("SUCCESS");
}

char					*ft_cd(t_serveur *d)
{
	char				*tmp;

	tmp = getcwd(NULL, 0);
	if ((ft_strcmp(d->arg[0], "cd") == 0) && !d->arg[1])
	{
		chdir(d->limit);
		return ("SUCCESS");
	}
	else if ((ft_strcmp(d->arg[0], "cd") == 0) && d->arg[1])
	{
		if (chdir(d->arg[1]) == 0)
		{
			if (ft_strncmp(d->limit, getcwd(NULL, 0), ft_strlen(d->limit)))
			{
				chdir(tmp);
				return ("ERROR Cannot access");
			}
			d->cwd = getcwd(NULL, 0);
			return ("SUCCESS");
		}
	}
	return ("ERROR CD");
}

char					*ft_pwd(t_serveur *d)
{
	char				*pwd;

	pwd = d->cwd + ft_strlen(d->limit) + 1;
	pwd = ft_strjoin("/", pwd);
	send(d->cs, pwd, ft_strlen(pwd), 0);
	send(d->cs, "\n\005\n", 3, 0);
	return ("SUCCESS");
}
