/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:12:45 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/06 12:40:52 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast_node	*parse_parentheses(t_token **current_token, t_sh *shell)
{
	t_ast_node	*node;
	char		*token_value;

	if ((*current_token)->type == TOKEN_LPAREN)
	{
		*current_token = (*current_token)->next;
		node = parse_and_or_sequence(current_token, shell);
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
	return (parse_command(current_token, shell));
}

t_ast_node	*parse_pipeline(t_token **current_token, t_sh *shell)
{
	t_ast_node	*left;
	t_ast_node	*node;

	left = parse_parentheses(current_token, shell);
	while (*current_token && (*current_token)->type == TOKEN_PIPE)
	{
		*current_token = (*current_token)->next;
		node = create_ast_node(AST_PIPE, shell);
		node->left = left;
		node->right = parse_parentheses(current_token, shell);
		left = node;
	}
	return (left);
}

// t_ast_node	*parse_command(t_token **current_token, t_sh *shell)
// {
// 	t_ast_node	*node;

// 	if (!*current_token)
// 		return (NULL);
// 	node = create_ast_node(AST_COMMAND, shell);
// 	while (*current_token && ((*current_token)->type == TOKEN_COMMAND
// 			|| (*current_token)->type == TOKEN_ARGUMENT
// 			|| (*current_token)->type == TOKEN_STRING
// 			|| (*current_token)->type == TOKEN_EXPAND))
// 	{
// 		add_argument(node, (*current_token)->value);
// 		*current_token = (*current_token)->next;
// 	}
// 	parse_redir(current_token, node, shell);
// 	return (node);
// }
t_ast_node	*parse_command(t_token **current_token, t_sh *shell)
{
	t_ast_node	*node;

	// Initialiser le nœud de commande
	node = create_ast_node(AST_COMMAND, shell);

	// Analyser toutes les redirections avant de chercher la commande
	while (*current_token && is_redirection_token(*current_token))
	{
		parse_redir(current_token, node, shell);
	}

	// Rechercher la commande principale et ses arguments après les redirections
	while (*current_token && ((*current_token)->type == TOKEN_COMMAND
			|| (*current_token)->type == TOKEN_ARGUMENT
			|| (*current_token)->type == TOKEN_STRING
			|| (*current_token)->type == TOKEN_EXPAND))
	{
		add_argument(node, (*current_token)->value);
		*current_token = (*current_token)->next;
	}

	// Analyser d'autres redirections possibles après la commande et les arguments
	while (*current_token && is_redirection_token(*current_token))
	{
		parse_redir(current_token, node, shell);
	}

	return (node);
}
