/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leye <leye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 05:25:24 by jgrimaud          #+#    #+#             */
/*   Updated: 2024/05/31 23:18:57 by jgrimaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_data *d);
bool	main_loop(t_data *d);
char	*main_readline(t_data *d);

volatile sig_atomic_t	g_signal_received = 0;

/**
 * @note If readline returns NULL, it means CTRL+D was pressed.
 */
int	main(int ac, char **av, char **env)
{
	t_data	d;

	(void)av;
	if (ac != 1)
		return (write(2, "Usage: ./minishell", 18), 1);
	init_data(&d);
	d.env = strs_to_lst(env, &d);
	d.stdin_cpy = ft_dup(STDIN_FILENO, &d);
	d.stdout_cpy = ft_dup(STDOUT_FILENO, &d);
	rl_catch_signals = 0;
	signal(SIGQUIT, handle_signal);
	increment_shlvl(&d.env, &d);
	while (1)
		if (!main_loop(&d))
			break ;
	return (cleanup(&d), d.exit_status);
}

void	init_data(t_data *d)
{
	d->ptrs = NULL;
	d->fds = NULL;
	d->env = NULL;
	d->stdin_cpy = -1;
	d->stdout_cpy = -1;
	d->is_pipe = false;
	d->last_pid = -1;
	d->exit_status = 0;
	d->last_exit_status = 0;
}

bool	main_loop(t_data *d)
{
	char	*input;
	t_list	*segments;

	signal(SIGINT, handle_signal);
	input = main_readline(d);
	consume_signals(d);
	if (!input)
		return (false);
	signal(SIGINT, ignore_signal);
	d->last_exit_status = d->exit_status;
	segments = parse(input, d);
	execute(segments, d);
	free(input);
	free_segments(segments, d);
	return (true);
}

char	*main_readline(t_data *d)
{
	char	*cwd;
	char	*prompt;
	char	*input;

	cwd = getcwd(NULL, 0);
	prompt = ft_strjoin_multiple(d, cwd, " $ ", NULL);
	input = readline(prompt);
	free(cwd);
	ft_free(prompt, d);
	if (input && input[0])
		add_history(input);
	return (input);
}
