/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bullestico <bullestico@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/06/27 03:53:49 by bullestico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/*

 A NORMER QUAND FINIS

*/

void free_cmds(t_cmd *cmds)
{
	t_cmd *tmp;
	while (cmds)
	{
		tmp = cmds->next;
		int i = 0;
		while (cmds->argv[i])
			free(cmds->argv[i++]);
		free(cmds->argv);
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

int exec_pipeline(t_g *g, t_cmd *cmds, char **envp)
{
    int    pipefd[2];
    int    prev_fd = -1;
    pid_t  pid;
    int    status;
    int    last_status = 0;

    while (cmds)
    {
        if (cmds->next && pipe(pipefd) == -1)
            return (perror("pipe"), 0);
        pid = fork();
        if (pid == -1)
            return (perror("fork"), 0);

        if (pid == 0) // CHILD
        {
            if (prev_fd != -1)
            {
                dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
            }
            if (cmds->next && !cmds->outfile)
            {
                close(pipefd[0]);
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[1]);
            }
            // redirections
            if (redirect_cmd_io(cmds) != 0)
                exit(1);

            // builtins envbuilt
            for (int i = 0; g->envbuilt[i].name; i++)
                if (strcmp(cmds->argv[0], g->envbuilt[i].name) == 0)
                    exit(g->envbuilt[i].e(g->env));

            // builtins classiques
            for (int i = 0; g->builtin[i].name; i++)
                if (strcmp(cmds->argv[0], g->builtin[i].name) == 0)
                    exit(g->builtin[i].f(g, g->cmds));

            /* === nouvelle logique pour les chemins avec '/' === */
            char *cmd = cmds->argv[0];
            char *path;
            if (strchr(cmd, '/'))
            {
                path = strdup(cmd);
                if (!path || access(path, X_OK) != 0)
                {
                    perror(cmd);
                    free(path);
                    exit(127);
                }
            }
            else
            {
                path = get_path(cmd, envp);
                if (!path)
                {
                    fprintf(stderr, "%s: command not found\n", cmd);
                    exit(127);
                }
            }

            execve(path, cmds->argv, envp);
            perror("execve");
            exit(1);
        }

        // PARENT
        if (prev_fd != -1)
            close(prev_fd);
        if (cmds->next)
        {
            close(pipefd[1]);
            prev_fd = pipefd[0];
        }
        cmds = cmds->next;
    }

    // attendre les enfants et récupérer le dernier code
    while (wait(&status) > 0)
        last_status = status;

    if (WIFEXITED(last_status))
        return_code(g->env, WEXITSTATUS(last_status));
    return 1;
}

