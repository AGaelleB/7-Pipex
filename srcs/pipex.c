/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnefo <abonnefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 10:40:53 by abonnefo          #+#    #+#             */
/*   Updated: 2023/05/09 14:49:31 by abonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"


char *ft_rev_print(char *str)
{
	int i = 0;

	while(str[i])
		i++;
	while(str[i])
		write(1, &str[i--], 1);
	return((char *)str);
}