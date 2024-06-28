/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leye <leye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 08:19:38 by jgrimaud          #+#    #+#             */
/*   Updated: 2024/06/01 13:10:50 by leye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_command_executable(char *cmd, t_data *d);
bool	is_dir(char *path);
char	*find_command_in_path(char *cmd, t_data *d);
char	**get_path(t_data *d);
void	exit_with_eaccess(char *perm_denied_file);
void	exit_with_command_not_found(char *cmd);
void	exit_with_is_a_directory(char *cmd);

void	execve_command(t_list *command, int pipe_end, t_data *d)
{
	pid_t	pid;
	char	*executable;

	pid = ft_fork(d);
	d->last_pid = pid;
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		ft_close(pipe_end, d);
		executable = find_command_executable(command->content, d);
		execve(executable,
			(char **)list_to_arr(command, d),
			(char **)list_to_arr(d->env, d));
	}
}

char	*find_command_executable(char *cmd, t_data *d)
{
	char	*executable_path;

	if (!cmd || !*cmd)
		exit_with_command_not_found(cmd);
	executable_path = NULL;
	if (ft_strchr(cmd, '/'))
	{
		if (is_dir(cmd))
			exit_with_is_a_directory(cmd);
		if (access(cmd, X_OK) == 0)
			executable_path = ft_strdup(cmd, d);
	}
	else
		executable_path = find_command_in_path(cmd, d);
	if (!executable_path && errno == EACCES)
		exit_with_perror(126, cmd);
	else if (!executable_path && errno == ENOENT)
		exit_with_perror(127, cmd);
	else if (!executable_path && errno == ENOEXEC)
		exit_with_command_not_found(cmd);
	return (executable_path);
}

bool	is_dir(char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) == -1)
		return (false);
	return (S_ISDIR(statbuf.st_mode));
}

char	*find_command_in_path(char *cmd, t_data *d)
{
	char	*executable_path;
	char	*perm_denied_file;
	char	**path;

	perm_denied_file = NULL;
	path = get_path(d);
	if (!path)
	{
		errno = ENOENT;
		return (NULL);
	}
	while (*path)
	{
		executable_path = ft_strjoin_multiple(d, *path, "/", cmd, NULL);
		if (access(executable_path, X_OK) == 0)
			return (executable_path);
		if (errno != ENOENT && !perm_denied_file)
			perm_denied_file = executable_path;
		path++;
	}
	if (perm_denied_file)
		exit_with_eaccess(perm_denied_file);
	else
		errno = ENOEXEC;
	return (NULL);
}

char	**get_path(t_data *d)
{
	t_list	*env;

	env = get_env_var_lst("PATH", d->env, d);
	if (env && env->content && ((char *)env->content)[4]
		&& ((char *)env->content)[5])
		return (ft_split(env->content + 5, ':', d));
	return (NULL);
}
