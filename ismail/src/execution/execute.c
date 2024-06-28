/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leye <leye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 08:18:27 by jgrimaud          #+#    #+#             */
/*   Updated: 2024/05/31 06:09:55 by jgrimaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_segment(t_segment *segment, int *last_pipe_out, bool is_last,
			t_data *d);
int		wait_for_last_process(t_data *d);

void	execute(t_list *segments, t_data *d)
{
	int		last_pipe_out;
	t_list	*tmp;

	d->is_pipe = segments && segments->next != NULL;
	d->last_pid = -1;
	last_pipe_out = -1;
	tmp = segments;
	while (tmp)
	{
		execute_segment(
			(t_segment *)tmp->content, &last_pipe_out, tmp->next == NULL, d);
		tmp = tmp->next;
	}
	ft_close(last_pipe_out, d);
	if (d->last_pid != -1
		&& !is_builtin(((t_segment *)ft_lstlast(segments)->content)->command))
		d->exit_status = wait_for_last_process(d);
	while (wait(NULL) > 0)
		;
}

void	execute_segment(t_segment *segment, int *last_pipe_out, bool is_last,
						t_data *d)
{
	int	pipe[2];

	pipe[0] = -1;
	pipe[1] = -1;
	if (!is_last)
		ft_pipe(pipe, d);
	ft_dup2(*last_pipe_out, 0, d);
	ft_dup2(pipe[1], 1, d);
	d->exit_status = process_redirections(segment->redirs, d);
	if (d->exit_status == 0 && segment->command)
	{
		d->exit_status = execute_builtin(segment->command, d);
		if (d->exit_status == -1)
			execve_command(segment->command, pipe[0], d);
	}
	ft_close(pipe[1], d);
	ft_close(*last_pipe_out, d);
	*last_pipe_out = pipe[0];
	ft_dup2(d->stdin_cpy, 0, d);
	ft_dup2(d->stdout_cpy, 1, d);
}

int	wait_for_last_process(t_data *d)
{
	int		status;

	status = 0;
	waitpid(d->last_pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
	{
		printf("Quit\n");
		return (131);
	}
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		printf("\n");
		return (130);
	}
	return (WEXITSTATUS(status));
}
