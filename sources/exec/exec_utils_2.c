/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bullestico <bullestico@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 00:37:41 by bullestico        #+#    #+#             */
/*   Updated: 2025/07/05 08:49:23 by bullestico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*check_binary_file(char *path, char *cmd)
{
	struct stat	sb;

	path = ft_strdup(cmd);
	if (!path || access(path, X_OK) != 0)
		return (write(2, cmd, ft_strlen(cmd)),
			perror(": command not found\n"), exit(127), NULL);
	if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
		return (write(2, cmd, ft_strlen(cmd)),
			perror(": is a directory\n"), free(path), exit(126), NULL);
	if (access(path, X_OK) != 0)
		return (write(2, cmd, ft_strlen(cmd)),
			perror(": permission denied\n"), free(path), exit(126), NULL);
	return (path);
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
