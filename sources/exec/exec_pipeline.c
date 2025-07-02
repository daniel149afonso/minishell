/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bullestico <bullestico@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:40:09 by bullestico        #+#    #+#             */
/*   Updated: 2025/07/02 18:40:12 by bullestico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

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

static void	get_access(char *cmd, t_cmd *cmds, char **envp)
{
	char	*path;

	path = NULL;
	if (strchr(cmd, '/'))
	{
		path = ft_strdup(cmd);
		if (!path || access(path, X_OK) != 0)
			return (perror(cmd), free(path), exit(127));
	}
	else
	{
		path = get_path(cmd, envp);
		if (!path)
			return (printf("%s: ", cmd), perror("command not found\n"),
				exit(127));
	}
	execve(path, cmds->argv, envp);
	perror("execve");
	exit(1);
}

static char	*parse_cmd_exec(t_g *g, t_cmd *cmds)
{
	char	*cmd;
	int		i;

	i = 0;
	while (g->envbuilt[i].name)
	{
		if (ft_strcmp(cmds->argv[0], g->envbuilt[i].name) == 0)
			exit(g->envbuilt[i].e(g->env));
		i++;
	}
	i = 0;
	while (g->builtin[i].name)
	{
		if (ft_strcmp(cmds->argv[0], g->builtin[i].name) == 0)
			exit(g->builtin[i].f(g, g->cmds));
		i++;
	}
	cmd = cmds->argv[0];
	return (cmd);
}

static void	check_pid(int pid, t_g *g, t_cmd *cmds, char **envp)
{
	if (pid == 0)
	{
		if (g->prev_fd != -1)
		{
			dup2(g->prev_fd, STDIN_FILENO);
			close(g->prev_fd);
		}
		if (cmds->next && !cmds->outfile)
		{
			close(g->pipefd[0]);
			dup2(g->pipefd[1], STDOUT_FILENO);
			close(g->pipefd[1]);
		}
		if (redirect_cmd_io(g, cmds) != 0)
			exit(1);
		g->cmd = parse_cmd_exec(g, cmds);
		get_access(g->cmd, cmds, envp);
		if (g->cmd)
			free (g->cmd);
	}
	if (g->prev_fd != -1)
		close(g->prev_fd);
}

int	exec_pipeline(t_g *g, t_cmd *cmds, char **envp)
{
	pid_t	pid;

	while (cmds)
	{
		if (cmds->next && pipe(g->pipefd) == -1)
			return (perror("pipe"), 0);
		pid = fork();
		if (pid == -1)
			return (perror("fork"), 0);
		check_pid(pid, g, cmds, envp);
		if (cmds->next)
		{
			close(g->pipefd[1]);
			g->prev_fd = g->pipefd[0];
		}
		cmds = cmds->next;
	}
	while (wait(&g->status) > 0)
		g->last_status = g->status;
	free_split(envp);
	if (WIFEXITED(g->last_status))
		return_code(g->env, WEXITSTATUS(g->last_status));
	return (1);
}
