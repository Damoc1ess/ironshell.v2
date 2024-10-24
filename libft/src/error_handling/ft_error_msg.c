/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_msg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:32:54 by fflamion          #+#    #+#             */
/*   Updated: 2024/09/17 12:33:24 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_error_msg(const char *msg)
{
	if (msg)
	{
		while (*msg)
		{
			write(2, msg, 1);
			msg++;
		}
		write(2, "\n", 1);
	}
}