/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:12:45 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/03 17:15:14 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast_node	*parse_parentheses(t_token **current_token)
{
	t_ast_node	*node;
	char		*token_value;

	if ((*current_token)->type == TOKEN_LPAREN)
	{
		*current_token = (*current_token)->next;
		node = parse_and_or_sequence(current_token);
		if (!(*current_token) || (*current_token)->type != TOKEN_RPAREN)
		{
			if (*current_token)
				token_value = (*current_token)->value;
			else
				token_value = "newline";
			fprintf(stderr,
				"minishell: syntax error near unexpected token `%s'\n",
				token_value);
			return (NULL);
		}
		*current_token = (*current_token)->next;
		return (node);
	}
	return (parse_command(current_token));
}

t_ast_node	*parse_pipeline(t_token **current_token)
{
	t_ast_node	*left;
	t_ast_node	*node;

	left = parse_parentheses(current_token);
	while (*current_token && (*current_token)->type == TOKEN_PIPE)
	{
		*current_token = (*current_token)->next;
		node = create_ast_node(AST_PIPE);
		node->left = left;
		node->right = parse_parentheses(current_token);
		left = node;
	}
	return (left);
}

t_ast_node	*parse_command(t_token **current_token)
{
	t_ast_node	*node;

	if (!*current_token)
		return (NULL);
	node = create_ast_node(AST_COMMAND);
	while (*current_token && ((*current_token)->type == TOKEN_COMMAND
			|| (*current_token)->type == TOKEN_ARGUMENT
			|| (*current_token)->type == TOKEN_STRING
			|| (*current_token)->type == TOKEN_EXPAND))
	{
		add_argument(node, (*current_token)->value);
		*current_token = (*current_token)->next;
	}
	parse_redirections(current_token, node);
	return (node);
}