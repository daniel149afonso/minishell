/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:35:12 by apiscopo          #+#    #+#             */
/*   Updated: 2025/07/29 18:52:48 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static char	*get_home(void)
{
	char	*cwd;
	char	*home;
	char	*short_path;
	int		home_len;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ft_strdup("?"));
	home = getenv("HOME");
	if (home && ft_strncmp(cwd, home, ft_strlen(home)) == 0)
	{
		home_len = ft_strlen(home);
		if (cwd[home_len] == '\0')
			short_path = ft_strdup("~");
		else
			short_path = ft_strjoin("~", cwd + home_len);
		free(cwd);
		return (short_path);
	}
	return (cwd);
}

char	*ft_prompt(void)
{
	char	*username;
	char	*result;
	char	*home;

	result = ft_strdup(PROMPT);
	if (!result)
		return ("ERR");
	username = getenv("USER");
	if (!username)
		username = "unknown";
	result = ft_join_and_free(result, username);
	result = ft_join_and_free(result, "\001\033[0m\002:\001\033[0;34m\002");
	home = get_home();
	if (!home)
		return ("ERR");
	result = ft_join_and_free(result, home);
	if (!result)
		return (free(home), "ERR");
	result = ft_join_and_free(result, "\001\033[0;34m\002\001\033[0m");
	if (!result)
		return (free(home), "ERR");
	result = ft_join_and_free(result, "\001\033[0m\002:\001\033[0;33m\002❯ \001\033[0m");
	if (!result)
		return (free(home), "ERR");
	return (free(home), result);
}
