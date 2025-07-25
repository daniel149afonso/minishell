/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiscopo <apiscopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:40:09 by bullestico        #+#    #+#             */
/*   Updated: 2025/07/25 17:19:13 by apiscopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static void	get_access(t_g *g, char *cmd, t_cmd *cmds, char **envp)
{
	char	*path;

	path = NULL;
	if (ft_strchr(cmd, '/'))
		path = check_binary_file(path, cmd);
	else
	{
		path = get_path(cmd, envp);
		if (!path)
			return (write(2, cmd, ft_strlen(cmd)),
				write(2, ": command not found\n", 20), free_n_exit_child(g, cmds,
					envp, 127));
	}
	execve(path, cmds->argv, envp);
	if (path)
		free(path);
	if (errno == ENOENT)
		free_n_exit_child(g, NULL, envp, 127);
	else if (errno == EACCES)
		free_n_exit_child(g, NULL, envp, 126);
	else
		return (write(2, cmd, ft_strlen(cmd)), perror(": execution error"),
			free_n_exit_child(g, NULL, envp, 127));
}

static char	*parse_cmd_exec(t_g *g, t_cmd *cmds)
{
	char	*cmd;
	int		i;

	cmd = NULL;
	i = 0;
	if (!cmds->argv || !cmds->argv[0])
		return (ft_strdup(""));
	while (g->envbuilt[i].name)
	{
		if (ft_strcmp(cmds->argv[0], g->envbuilt[i].name) == 0)
			exit(g->envbuilt[i].e(g->env, g->lst));
		i++;
	}
	i = 0;
	while (g->builtin[i].name)
	{
		if (ft_strcmp(cmds->argv[0], g->builtin[i].name) == 0)
			exit(g->builtin[i].f(g, cmds));
		i++;
	}
	cmd = cmds->argv[0];
	return (cmd);
}

static void	check_pid(int pid, t_g *g, t_cmd *cmds, char **envp)
{
	if (pid == 0)
	{
		setup_stdin(g, cmds);
		setup_stdout(g, cmds);
		if (apply_redirections(g, cmds) != 0)
			return ;
		g->cmd = parse_cmd_exec(g, cmds);
		if (g->cmd && g->cmd[0] != '\0')
			get_access(g, g->cmd, cmds, envp);
		else
		{
			dup2(open("/dev/null", O_RDONLY), STDIN_FILENO);
			dup2(open("/dev/null", O_WRONLY), STDOUT_FILENO);
			free(g->cmd);
			exit(0);
		}
		free(g->cmd);
	}
	if (g->prev_fd != -1)
	{
		close(g->prev_fd);
		g->prev_fd = -1;
	}
}

int	execution(t_g *g, t_cmd *cmds, char **envp)
{
	pid_t	pid;

	while (cmds)
	{
		if (prepare_redirections(g, cmds) != 0)
			return (0);
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
	return (1);
}

int	exec_pipeline(t_g *g, t_cmd *cmds, char **envp)
{
	if (!execution(g, cmds, envp))
		return (1);
	while (wait(&g->status) > 0)
		g->last_status = g->status;
	if (WIFEXITED(g->last_status))
		return_code(g->env, WEXITSTATUS(g->last_status));
	if (WIFSIGNALED(g->status) && WTERMSIG(g->status) == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
	free_split(envp);
	return (1);
}
