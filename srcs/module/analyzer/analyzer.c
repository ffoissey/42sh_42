/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 15:44:20 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void		command_assign(t_stack *tree_node, t_command *command)
{
	t_list		*node;

	command->type = COMMAND_ASSIGN;
	while (ft_stcksize(tree_node) > 0)
	{
		node = ft_stckpopnode(tree_node);
		ft_lstadd(&command->av, node);
	}
}

static void		command_args(t_stack *tree_node, t_command *command)
{
	t_list		*node;

	command->type = COMMAND_RUN;
	while (ft_stcksize(tree_node) > 0)
	{
		if (((t_action *)ft_stcktop(tree_node))->type == A_ARGS)
			break ;
		node = ft_stckpopnode(tree_node);
		ft_lstadd(&command->actions, node);
	}
}

static t_list	*generate_cmd_list(t_stack *tree_node)
{
	t_command	command;
	t_action	*action;
	t_list		*node;

	ft_bzero(&command, sizeof(t_command));
	node = ft_stckpopnode(tree_node);
	action = node->data;
	if (action->type == A_ASSIGN)
	{
		command_assign(tree_node, &command);
		ft_lstadd(&command.av, node);
	}
	else
	{
		command.av = action->data;
		command_args(tree_node, &command);
		ft_lstdelone(&node, NULL);
	}
	node = ft_lstnew(&command, sizeof(t_command));
	return (node);
}

static int8_t	generate_cmd_group(t_list **cmd_group, t_stack *tree_node)
{
	t_group		group;
	t_action	*action;
	t_list		*node;

	if (ft_stcksize(tree_node) == 0)
		return (FAILURE);
	ft_bzero(&group, sizeof(t_group));
	action = ft_stckpop(tree_node);
	set_group_type(&group, action);
	free(action);
	while (ft_stcksize(tree_node) > 0)
	{
		if ((node = generate_cmd_list(tree_node)) == NULL)
			return (FAILURE);
		ft_lstadd(&group.command_list, node);
	}
	node = ft_lstnew(&group, sizeof(t_group));
	ft_lstaddback(cmd_group, node);
	return (SUCCESS);
}

t_list			*analyzer(t_list **tokens)
{
	t_analyze			analyze;
	static t_analyzer	*analyzer = NULL;
	t_list				*command_group;

	command_group = NULL;
	if (analyzer == NULL)
		analyzer = init_analyzer();
	ft_bzero(&analyze, sizeof(t_analyze));
	analyze.tokens = tokens;
	analyze.token.type = E_DEFAULT;
	get_token(&analyze);
	while (analyze.state != P_END)
	{
		if (analyze.state == P_STOP)
			generate_cmd_group(&command_group, &analyze.tree_node);
		(*analyzer)[analyze.state][analyze.token.type](&analyze);
	}
	if (analyze.valid == 1)
		if (generate_cmd_group(&command_group, &analyze.tree_node) == FAILURE)
			return (NULL);
	analyzer_print_debug(g_shell, command_group);
	return (command_group);
}
