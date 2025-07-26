/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bullestico <bullestico@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 00:37:41 by bullestico        #+#    #+#             */
/*   Updated: 2025/07/26 07:20:46 by bullestico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*check_binary_file(t_g *g, t_cmd *cmds, char **envp, char *cmd)
{
	struct stat	sb;

	g->path = ft_strdup(cmd);
	if (!g->path || access(g->path, X_OK) != 0)
		return (write(2, cmd, ft_strlen(cmd)),
			perror(": command not found\n"), free_n_exit_child(g, cmds,
				envp, 127), NULL);
	if (stat(g->path, &sb) == 0 && S_ISDIR(sb.st_mode))
		return (write(2, cmd, ft_strlen(cmd)),
			perror(": is a directory\n"), free(g->path), free_n_exit_child(g,
				cmds, envp, 127), NULL);
	if (access(g->path, X_OK) != 0)
		return (write(2, cmd, ft_strlen(cmd)),
			perror(": permission denied\n"), free(g->path), free_n_exit_child(g,
				cmds, envp, 127), NULL);
	return (g->path);
}

char	*get_path(char *cmd, char **envp)
{
	char	**paths;
	char	*full;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		full = ft_strjoin(paths[i], "/");
		full = ft_strjoin_free(full, cmd, 1);
		if (access(full, X_OK) == 0)
			return (free_split(paths), full);
		free(full);
		i++;
	}
	free_split(paths);
	return (NULL);
}

void	setup_stdin(t_g *g, t_cmd *cmds)
{
	t_redir	*r;

	r = cmds->redirections;
	while (r)
	{
		if (r->type == 4)
		{
			if (r->heredoc_fd != -1)
			{
				if (g->s_stdin == -1)
					g->s_stdin = dup(STDIN_FILENO);
				dup2(r->heredoc_fd, STDIN_FILENO);
				close(r->heredoc_fd);
				return ;
			}
		}
		r = r->next;
	}
	if (g->prev_fd != -1)
	{
		dup2(g->prev_fd, STDIN_FILENO);
		close(g->prev_fd);
	}
}

void	setup_stdout(t_g *g, t_cmd *cmds)
{
	if (cmds->next)
	{
		close(g->pipefd[0]);
		dup2(g->pipefd[1], STDOUT_FILENO);
		close(g->pipefd[1]);
	}
}

void	second_parse_cmd(t_g *g, t_cmd *cmds, char **envp)
{
	int	i;
	int	error_code;

	i = 0;
	error_code = 0;
	while (g->builtin[i].name)
	{
		if (ft_strcmp(cmds->argv[0], g->builtin[i].name) == 0)
		{
			error_code = g->builtin[i].f(g, cmds);
			free_n_exit_child(g, cmds, envp, error_code);
		}
		i++;
	}
}