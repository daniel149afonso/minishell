/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/06/30 19:44:24 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/*

 A NORMER QUAND FINIS

*/

void free_cmds(t_cmd *cmds)
{
	
	int		i;
	t_cmd	*tmp;

	i = 0;
	while (cmds)
	{
		tmp = cmds->next;
		
		while (cmds->argv[i])
			free(cmds->argv[i++]);
		free(cmds->argv);
		free(cmds->infile);
		free(cmds->outfile);
		free(cmds);
		cmds = tmp;
	}
}

char **get_envp_array(t_env *env)
{
	int count = 0;
	t_env *tmp = env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}

	char **envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return NULL;

	tmp = env;
	int i = 0;
	while (tmp)
	{
		envp[i] = ft_strjoin(tmp->key, "=");
		envp[i] = ft_strjoin_free(envp[i], tmp->value, 1);
		tmp = tmp->next;
		i++;
	}
	envp[i] = NULL;
	return envp;
}

char *ft_strjoin_free(char *s1, char *s2, int free_s1)
{
	char *res = ft_strjoin(s1, s2);
	if (free_s1)
		free(s1);
	return res;
}

void free_split(char **arr)
{
	int i = 0;
	while (arr && arr[i])
		free(arr[i++]);
	free(arr);
}

char *get_path(char *cmd, char **envp)
{
	char **paths;
	char *full;
	int i = 0;

	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return NULL;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		full = ft_strjoin(paths[i], "/");
		full = ft_strjoin_free(full, cmd, 1); // fonction join avec free
		if (access(full, X_OK) == 0)
		{
			free_split(paths);
			return full;
		}
		free(full);
		i++;
	}
	free_split(paths);
	return NULL;
}

static void	get_access(char *cmd, t_cmd *cmds, char **envp)
{
	char	*path;
	
	path = NULL;
	if (strchr(cmd, '/'))
	{
		path = strdup(cmd);
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

static char    *parse_cmd_exec(t_g *g, t_cmd *cmds)
{
	char    *cmd;
	int     i;

	i = 0;
	while (g->envbuilt[i].name)
	{
		if (strcmp(cmds->argv[0], g->envbuilt[i].name) == 0)
			exit(g->envbuilt[i].e(g->env));
		i++;
	}
	i = 0;
	while (g->builtin[i].name)
	{
		if (strcmp(cmds->argv[0], g->builtin[i].name) == 0)
			exit(g->builtin[i].f(g, g->cmds));
		i++;
	}
	cmd = cmds->argv[0];
	return (cmd);
}

static void	check_pid(int pid, t_g *g, t_cmd *cmds, int *pipefd, char **envp)
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
			close(pipefd[0]);
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
		}
		if (redirect_cmd_io(g, cmds) != 0)
			exit(1);
		g->cmd = parse_cmd_exec(g, cmds);
		get_access(g->cmd, cmds, envp);
		if (g->cmd)
			free (g->cmd);
	}
}

int exec_pipeline(t_g *g, t_cmd *cmds, char **envp)
{
	int    pipefd[2];
	pid_t  pid;

	while (cmds)
	{
		if (cmds->next && pipe(pipefd) == -1)
			return (perror("pipe"), 0);
		pid = fork();
		if (pid == -1)
			return (perror("fork"), 0);
		check_pid(pid, g, cmds, pipefd, envp);
		if (g->prev_fd != -1)
			close(g->prev_fd);
		if (cmds->next)
		{
			close(pipefd[1]);
			g->prev_fd = pipefd[0];
		}
		cmds = cmds->next;
	}
	while (wait(&g->status) > 0)
		g->last_status = g->status;
	if (WIFEXITED(g->last_status))
		return_code(g->env, WEXITSTATUS(g->last_status));
	return 1;
}
