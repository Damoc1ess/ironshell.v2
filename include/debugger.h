/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugger.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 21:57:07 by fflamion          #+#    #+#             */
/*   Updated: 2024/10/27 14:08:19 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef DEBUGGER_H
#define DEBUGGER_H

#include "minishell.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

void	print_token_list(t_token_list *list);

#endif