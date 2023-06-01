/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnefo <abonnefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:29:20 by abonnefo          #+#    #+#             */
/*   Updated: 2023/06/01 13:45:44 by abonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	ft_strncmp_pipex(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while ((i < n) && (s1[i] == s2[i]) && s1[i] && s2[i])
		i++;
	if (i < n)
		return (s1[i] - s2[i]);
	return (0);
}

char	*ft_strjoin_pipex(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*dest;

	i = ft_strlen(s1) + ft_strlen(s2);
	dest = malloc(sizeof(char) * (i + 2));
	if (!dest)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '/';
	i++;
	while (s2[j])
	{
		dest[i + j] = s2[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	ft_free_all_data(t_data *data)
{
	free(data->cmd1.path);
	free(data->cmd2.path);
	ft_free_tab(data->cmd1.args);
	// if (data->cmd2.args[2])
		ft_free_tab(data->cmd2.args);
	// else
		// free(data->cmd2.args);
}

void	ft_print_error(char *str)
{
	int len;

	len = ft_strlen(str);
	write(2, str, len);
	write(2, " : invalid command\n", 19);
}