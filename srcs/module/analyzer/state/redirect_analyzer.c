/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_analyzer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 14:57:46 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <fcntl.h>
#include <unistd.h>

void			dup_stderr(t_analyze *analyze)
{
	t_action	action;
	t_token		token;
	t_list		*node;

	ft_bzero(&action, sizeof(t_action));
	action.type = A_DUP;
	token.type = E_IO_NUMBER;
	token.data = ft_strdup("1");
	node = ft_lstnew(&token, sizeof(t_token));
	ft_lstadd(&action.data, node);
	token.data = ft_strdup("2");
	node = ft_lstnew(&token, sizeof(t_token));
	ft_lstadd(&action.data, node);
	ft_stckpush(&analyze->tree_node, &action, sizeof(t_action));
}

enum e_actions	define_redirect(t_token *token)
{
	if (token->type == E_GREAT || token->type == E_ANDGREAT)
		return (A_STDOUT_TRUNCATE_FILE);
	if (token->type == E_GREATAND)
		return (A_STDOUT_TRUNCATE_FILE_SPECIAL);
	if (token->type == E_DGREAT || token->type == E_ANDDGREAT)
		return (A_STDOUT_APPEND_FILE);
	if (token->type == E_LESS)
		return (A_STDIN_READ_FILE);
	if (token->type == E_LESSAND)
		return (A_STDIN_READ_FD);
	return (-1);
}

void			flush_redirect(t_analyze *analyze)
{
	enum e_type	type;
	t_list		*node;
	t_action	action;

	analyze->state = P_REDIRECT_FLUSH;
	ft_bzero(&action, sizeof(t_action));
	node = ft_stckpopnode(&analyze->stack);
	ft_lstaddback(&action.data, node);
	node = ft_stckpopnode(&analyze->stack);
	action.type = define_redirect(node->data);
	type = ((t_token *)node->data)->type;
	ft_lstdelone(&node, NULL);
	ft_stckpush(&analyze->tree_node, &action, sizeof(t_action));
	if (type == E_ANDGREAT || type == E_ANDDGREAT)
		dup_stderr(analyze);
}

void			redirect_and_analyzer(t_analyze *analyze)
{
	analyze->state = P_REDIRECT_AND;
	ft_stckpush(&analyze->stack, &analyze->token, sizeof(t_token));
	get_token(analyze);
}

void			redirect_analyzer(t_analyze *analyze)
{
	if (analyze->token.type == E_DLESS || analyze->token.type == E_DLESSDASH)
		analyze->state = P_HEREDOC_REDIRECT;
	else
		analyze->state = P_REDIRECT;
	ft_stckpush(&analyze->stack, &analyze->token, sizeof(t_token));
	get_token(analyze);
}
