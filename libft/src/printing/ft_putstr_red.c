/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_red.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:43:26 by fflamion          #+#    #+#             */
/*   Updated: 2024/09/20 13:53:41 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_red(const char *str)
{
	write(1, "\033[31m", 5);
	write(1, str, ft_strlen(str));
	write(1, "\033[0m", 4);
	exit (-1);
}
