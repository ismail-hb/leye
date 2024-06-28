/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrimaud <jgrimaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 05:20:38 by jgrimaud          #+#    #+#             */
/*   Updated: 2024/05/29 08:33:31 by jgrimaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @note The signals are sent to EVERY process, however, when execve is called,
 * the signals of the executable are reset to their default behavior.
 * i.e. CTRL-C kills the process, CTRL-\ quits the process.
 */
void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_signal_received = sig;
		printf("^C\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ignore_signal(int sig)
{
	(void)sig;
}

void	consume_signals(t_data *d)
{
	if (g_signal_received == SIGINT)
		d->exit_status = 130;
	g_signal_received = 0;
}
