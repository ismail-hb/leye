/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrimaud <jgrimaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 05:50:46 by jgrimaud          #+#    #+#             */
/*   Updated: 2024/05/30 09:12:57 by jgrimaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_open(char *file, int flags, mode_t mode, t_data *d)
{
	int		fd;

	fd = open(file, flags, mode);
	if (fd == -1)
		return (-1);
	ft_lstadd_front(&d->fds, ft_lstnew((void *)(long)fd, d));
	return (fd);
}

void	ft_close(int fd, t_data *d)
{
	if (fd < 0)
		return ;
	if (close(fd) == -1)
		clean_exit_with_error("close failed", d);
	ft_lstdelshiftbycontent(&d->fds, (void *)(long)fd, NULL, d);
}

int	ft_dup(int fd, t_data *d)
{
	int	out_fd;

	if (fd < 0)
		return (-1);
	out_fd = dup(fd);
	if (out_fd == -1)
		clean_exit_with_error("dup failed", d);
	ft_lstadd_front(&d->fds, ft_lstnew((void *)(long)out_fd, d));
	return (out_fd);
}

int	ft_dup2(int from_fd, int to_fd, t_data *d)
{
	int	out_fd;

	if (from_fd == to_fd || from_fd < 0 || to_fd < 0)
		return (-1);
	out_fd = dup2(from_fd, to_fd);
	if (out_fd == -1)
		clean_exit_with_error("dup2 failed", d);
	ft_lstadd_front(&d->fds, ft_lstnew((void *)(long)out_fd, d));
	return (out_fd);
}
