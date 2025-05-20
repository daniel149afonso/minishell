/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:04:38 by daniel149af       #+#    #+#             */
/*   Updated: 2025/05/20 17:14:33 by daafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	parsing_redir(t_list *lst)
{
	while (lst)
	{
		if (ft_strcmp((char *)lst->content, ">") == 0 && !lst->next)
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}

void	remove_token(t_list **lst, t_list **cur, t_list **prev)
{
	t_list	*file;
	t_list	*after;

	file = (*cur)->next;
	after = file->next;
	if (*prev)
		(*prev)->next = after;
	else
		*lst = after;
	free((*cur)->content);
	free(*cur);
	free(file->content);
	free(file);
}

void	remove_redir_token(t_list **lst)
{
	t_list	*curr;
	t_list	*prev;

	curr = *lst;
	prev = NULL;
	while (curr && curr->next)
	{
		if (!ft_strcmp((char *)curr->content, ">") \
		|| !ft_strcmp((char *)curr->content, ">>") \
		|| !ft_strcmp((char *)curr->content, "<"))
		{
			remove_token(lst, &curr, &prev);
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
}

int	one_stdout(t_g *g, t_list *redir)
{
	int		fd;

	fd = open((char *)redir->next->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open failed");
		return (1);
	}
	// 💾 sauvegarder stdout
	g->s_stdout = dup(STDOUT_FILENO);

	// 🔁 rediriger stdout vers le fichier
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	double_stdout(t_g *g, t_list *redir)
{
	int		fd;

	fd = open((char *)redir->next->content, \
		O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("open failed");
		return (1);
	}
	g->s_stdout = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	one_stdin(t_g *g, t_list *redir)
{
	int		fd;

	fd = open((char *)redir->next->content, O_RDONLY, 0644);
	if (fd < 0)
	{
		printf("%s: No such file or directory", (char *)redir->next->content);
		return (1);
	}
	g->s_stdin = dup(STDIN_FILENO);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	double_stdin(t_list *redir)
{
	char	*occur;
	char	*buffer;
	t_list	*lst;
	int		turn;

	buffer = ft_calloc(1, 1);
	if (!buffer)
		return (1);
	occur = ((char *)redir->next->content);
	turn = 1;
	if (!occur)
	{
		printf("minishell: syntax error near unexpected token `newline'");
		return (1);
	}
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		buffer = readline("> ");
		if (buffer)
		{
			printf("Debug: %s\n", buffer);
			if (ft_strcmp(buffer, occur))
				break ;
			if (turn)
				lst = ft_lstnew(ft_strdup(buffer));
			else
				ft_lstadd_back(&lst, ft_lstnew(ft_strdup(buffer)));
			turn = 0;
		}
	}
	printf("jai fini\n");
	//ft_put_lst(lst);
	return (0);
}

void	restore_std(t_g *g)
{
	if (g->s_stdout != -1)
	{
		// 🔁 restaurer stdout
		dup2(g->s_stdout, STDOUT_FILENO);
		close(g->s_stdout);
	}
	if (g->s_stdin != -1)
	{
		// 🔁 restaurer stdin
		dup2(g->s_stdin, STDIN_FILENO);
		close(g->s_stdin);
	}
}

int	is_redirection(t_g *g)
{
	t_list	*tmp;

	tmp = g->lst;
	if (parsing_redir(g->lst))
		return (1);
	while (tmp)
	{
		if (ft_strcmp((char *)tmp->content, ">") == 0)
			one_stdout(g, tmp);
		else if (ft_strcmp((char *)tmp->content, ">>") == 0)
			double_stdout(g, tmp);
		else if (ft_strcmp((char *)tmp->content, "<") == 0)
			one_stdin(g, tmp);
		else if (ft_strcmp((char *)tmp->content, "<<") == 0)
			double_stdin(tmp);
		tmp = tmp->next;
	}
	return (0);
}
