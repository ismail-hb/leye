/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrimaud <jgrimaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 08:15:05 by jgrimaud          #+#    #+#             */
/*   Updated: 2024/05/29 11:21:07 by jgrimaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	process_redirection(t_redir *redir, t_data *d);

int	process_redirections(t_list *redirs, t_data *d)
{
	while (redirs)
	{
		if (process_redirection((t_redir *)redirs->content, d) == 1)
			return (1);
		redirs = redirs->next;
	}
	return (0);
}

int	process_redirection(t_redir *redir, t_data *d)
{
	int	new_fd;

	if (redir->type == REDIR_OUT)
		new_fd = ft_open(redir->to, O_WRONLY | O_CREAT | O_TRUNC, 0644, d);
	else if (redir->type == REDIR_APPEND)
		new_fd = ft_open(redir->to, O_WRONLY | O_CREAT | O_APPEND, 0644, d);
	else
		new_fd = ft_open(redir->to, O_RDONLY, 0644, d);
	if (new_fd == -1)
	{
		write_perror(redir->to);
		return (1);
	}
	if (redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
		ft_dup2(new_fd, 1, d);
	else if (redir->type == REDIR_IN || redir->type == REDIR_HEREDOC)
		ft_dup2(new_fd, 0, d);
	ft_close(new_fd, d);
	return (0);
}
