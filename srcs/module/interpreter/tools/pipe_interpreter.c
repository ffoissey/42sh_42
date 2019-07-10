/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_interpreter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 21:23:29 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>

t_list	*create_pipe_in(int from)
{
	t_action	action;
	t_list		*node;
	t_token		token;

	ft_bzero(&action, sizeof(t_action));
	action.type = A_MOVE;
	token.type = E_STRING;
	token.data = ft_itoa(from);
	node = ft_lstnew(&token, sizeof(t_token));
	ft_lstadd(&action.data, node);
	token.type = E_STRING;
	token.data = ft_itoa(STDIN_FILENO);
	node = ft_lstnew(&token, sizeof(t_token));
	ft_lstadd(&action.data, node);
	node = ft_lstnew(&action, sizeof(t_action));
	return (node);
}

t_list	*create_pipe_out(int to)
{
	t_action	action;
	t_list		*node;
	t_token		token;
	t_list		*pipe_out;

	ft_bzero(&action, sizeof(t_action));
	pipe_out = NULL;
	action.type = A_DUP;
	token.type = E_STRING;
	token.data = ft_itoa(to);
	node = ft_lstnew(&token, sizeof(t_token));
	ft_lstadd(&action.data, node);
	token.type = E_STRING;
	token.data = ft_itoa(STDOUT_FILENO);
	node = ft_lstnew(&token, sizeof(t_token));
	ft_lstadd(&action.data, node);
	node = ft_lstnew(&action, sizeof(t_action));
	ft_lstadd(&pipe_out, node);
	return (pipe_out);
}

int		setup_pipe(t_process *current, t_process *next, int pipe_fd[2])
{
	t_list		*pipe_node;
	t_action	action;
	t_token		token;
	t_list		*node;

	if ((pipe_node = create_pipe_out(pipe_fd[1])) == NULL)
		return (FAILURE);
	ft_bzero(&action, sizeof(t_action));
	action.type = A_CLOSE;
	token.type = E_STRING;
	token.data = ft_itoa(pipe_fd[0]);
	node = ft_lstnew(&token, sizeof(t_token));
	ft_lstadd(&action.data, node);
	node = ft_lstnew(&action, sizeof(t_action));
	ft_lstadd(&pipe_node, node);
	current->redirects = ft_lstmerge(&pipe_node, current->redirects);
	if ((pipe_node = create_pipe_in(pipe_fd[0])) == NULL)
		return (FAILURE);
	next->redirects = ft_lstmerge(&pipe_node, next->redirects);
	return (SUCCESS);
}

int8_t	launch_pipeline(t_list *process, uint8_t foreground)
{
	int			pipe_fd[2];

	pipe_fd[0] = 0;
	pipe_fd[1] = 0;
	if (process == NULL)
		return (SUCCESS);
	if (process->next)
	{
		if (pipe(pipe_fd) == FAILURE)
			return (FAILURE);
		if (setup_pipe(process->data, process->next->data, pipe_fd) == FAILURE)
			return (FAILURE);
	}
	if (run_process(process->data, foreground, pipe_fd[1]) == FAILURE)
	{
		pipe_fd[0] == 0 ? pipe_fd[0] : close(pipe_fd[0]);
		return (FAILURE);
	}
	if (launch_pipeline(process->next, foreground) == FAILURE)
	{
		pipe_fd[0] == 0 ? pipe_fd[0] : close(pipe_fd[0]);
		return (FAILURE);
	}
	pipe_fd[0] == 0 ? pipe_fd[0] : close(pipe_fd[0]);
	return (SUCCESS);
}
