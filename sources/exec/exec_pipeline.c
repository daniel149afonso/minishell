/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:03:28 by apiscopo          #+#    #+#             */
/*   Updated: 2025/06/18 17:24:26 by daafonso         ###   ########.fr       */
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

void	get_sub_lst(t_list *lst, t_list **sub_lst)
{
	char	pipe[2];
	int		turn;

	turn = 1;
	pipe[0] = '|';
	pipe[1] = '\0';
	while (lst)
	{
		if (!ft_strcmp((char *)lst->content, pipe))
			break ;
		if (turn)
		{
			*sub_lst = ft_lstnew(ft_strdup((char *)lst->content));
			turn = 0;
		}
		else
			ft_lstadd_back(sub_lst, ft_lstnew(ft_strdup((char *)lst->content)));
		lst = lst->next;
	}
	ft_put_lst(*sub_lst);
}

int exec_pipeline(t_g *g, t_cmd *cmds, char **envp)
{
	int    pipefd[2];
	int    prev_fd = -1;
	pid_t  pid;
	t_list *old_lst;
	t_list *sub_lst;

	while (cmds)
	{
		if (cmds->next && pipe(pipefd) == -1)
		{
			perror("pipe");
			return (0);
		}

		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			return (0);
		}

		if (pid == 0)  /* === CHILD === */
		{
			//redirect stdin or stdout
			redirect_std_to_file(g);
			/* 1) Si on lit dans un pipe précédent, redirige stdin */
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}

			/* 2) Si une commande suit, redirige stdout vers ce pipe */
			if (cmds->next)
			{
				close(pipefd[0]);
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[1]);
			}

			/* 3) Builtins “envbuilt” (env/export/unset) dans un pipeline */
			for (int i = 0; g->envbuilt[i].name; i++)
			{
				if (strcmp(cmds->argv[0], g->envbuilt[i].name) == 0)
				{
					g->envbuilt[i].e(g->env);
					exit(0);
				}
			}

			/* 4) Builtins classiques (cd/pwd/echo/exit) dans un pipeline */
			for (int i = 0; g->builtin[i].name; i++)
			{
				if (strcmp(cmds->argv[0], g->builtin[i].name) == 0)
				{
					old_lst = g->lst;
					get_sub_lst(g->lst, &sub_lst);
					g->lst = sub_lst;
					g->builtin[i].f(g);
					g->lst = old_lst;
					exit(0);
				}
			}

			/* 5) Commande externe */
			char *path = get_path(cmds->argv[0], envp);
			if (!path)
			{
				fprintf(stderr, "%s: command not found\n", cmds->argv[0]);
				exit(127);
			}
			execve(path, cmds->argv, envp);

			/* si execve échoue */
			perror("execve");
			exit(1);
		}

		/* === PARENT === */
		if (prev_fd != -1)
			close(prev_fd);
		if (cmds->next)
		{
			close(pipefd[1]);
			prev_fd = pipefd[0];
		}
		cmds = cmds->next;
	}

	/* attendre tous les children */
	while (wait(NULL) > 0)
		;
	return (1);
}
