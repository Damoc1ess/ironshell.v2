/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 12:36:31 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/03 17:17:59 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "lexer.h"
# include "debugger.h"

typedef enum e_ast_node_type
{
	AST_COMMAND,
	AST_PIPE,
	AST_AND,
	AST_OR,
	AST_REDIRECTION_IN,
	AST_REDIRECTION_OUT,
	AST_REDIRECTION_APPEND,
	AST_REDIRECTION_HEREDOC
}	t_ast_node_type;

typedef struct s_ast_node
{
	t_ast_node_type		type;
	char				**argv;
	char				*filename;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

t_ast_node	*create_ast_node(t_ast_node_type type);
void		add_argument(t_ast_node *node, char *argument);
void		free_ast(t_ast_node *node);

// parser
t_ast_node	*ast_parser(t_t_list *token_list);
t_ast_node	*parse_parentheses(t_token **current_token);
t_ast_node	*parse_command(t_token **current_token);
t_ast_node	*parse_pipeline(t_token **current_token);
t_ast_node	*parse_and_or_sequence(t_token **current_token);

// execution
int			execute_ast(t_ast_node *node, t_sh *shell);
int			execute_command_node(t_ast_node *node, t_sh *shell);
int			execute_pipe_node(t_ast_node *node, t_sh *shell);
int			execute_and_node(t_ast_node *node, t_sh *shell);
int			execute_or_node(t_ast_node *node, t_sh *shell);

// execution utils
void		handle_redir_in(t_ast_node *node);
void		handle_redir_out(t_ast_node *node, int flags);
void		handle_redirections(t_ast_node *node);

// parse_redir
void		chain_redirection(t_ast_node *command_node, t_ast_node *redir_node);
t_ast_node	*create_redirection_node(t_token_type type);
void		parse_redirections(t_token **current_token, t_ast_node *cmd_node);

// parse_pipeline
t_ast_node	*parse_pipeline(t_token **current_token);
t_ast_node	*parse_parentheses(t_token **current_token);

#endif
