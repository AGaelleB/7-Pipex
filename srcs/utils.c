/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnefo <abonnefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:40:03 by abonnefo          #+#    #+#             */
/*   Updated: 2023/06/14 14:42:50 by abonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_free_all_data(t_data *data)
{
	free(data->cmd1.path);
	free(data->cmd2.path);
	ft_free_tab(data->cmd1.args);
	ft_free_tab(data->cmd2.args);
}

void	ft_print_error(char *str)
{
	int	len;

	len = ft_strlen(str);
	write(2, "command not found :", 19);
	write(2, str, len);
	write(2, "\n", 1);
}
