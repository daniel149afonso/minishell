/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:28:18 by daniel149af       #+#    #+#             */
/*   Updated: 2025/06/05 02:37:07 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/*Détecter si une chaîne commence et finit par des guillemets.*/
int	is_quoted(char *s)
{
	int	len;

	len = ft_strlen(s);
	if (len >= 2)
	{
		if ((s[0] == '\'' && s[len - 1] == '\''))
			return (1);
		else if ((s[0] == '"' && s[len - 1] == '"'))
			return (2);
	}
	return (0);
}

/*check si entouré de guillemets*/
int	check_quotes(char *token)
{
	if (is_quoted(token))
		return (1);
	return (0);
}

/*construire une chaîne en enlevant les quotes autour*/
void	replace_string(char c, t_quote_state *q)
{
	char	str[2];

	if (c == '\'' && !q->in_double)
		q->in_single = !q->in_single;
	else if (c == '"' && !q->in_single)
		q->in_double = !q->in_double;
	else
	{
		str[0] = c;
		str[1] = '\0';
		q->res = ft_join_and_free(q->res, str);
	}
}

/*retirer les quotes autour de la chaîne en laissant les quotes imbriqué*/
char	*remove_quotes_2(char *str)
{
	int				i;
	t_quote_state	q;

	i = 0;
	q.in_single = 0;
	q.in_double = 0;
	q.res = ft_calloc(1, 1);
	if (!q.res)
		return (NULL);
	while (str[i])
	{
		replace_string(str[i], &q);
		i++;
	}
	return (q.res);
}

/*appliquer remove_quotes_2() à chaque élément de la liste de tokens*/
void	remove_quotes(t_list **lst)
{
	char	*tmp;
	t_list	*temp;

	tmp = NULL;
	temp = *lst;
	while (temp)
	{
		tmp = (char *)(temp)->content;
		temp->content = (void *)remove_quotes_2((char *)(temp)->content);
		free(tmp);
		temp = temp->next;
	}
}
