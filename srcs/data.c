/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnefo <abonnefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:37:03 by abonnefo          #+#    #+#             */
/*   Updated: 2023/06/01 13:30:28 by abonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	**ft_get_paths(char **envp)
{
	char	*path;
	char	**all_paths;

	while (*envp)
	{
		if (ft_strncmp_pipex("PATH=", *envp, 5) == 0)
		{
			path = &((*envp)[5]); // a revoir
			break ;
		}
		envp++;
	}
	if (path == NULL)
		return (NULL);
	all_paths = ft_split(path, ':');
	return (all_paths);
}

int	ft_strchr_slash(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_check_paths(char **envp, char *args)
{
	char	**temp_path;
	char	*valid_path;
	int		i;

	if (ft_strchr_slash(args, '/') == 1) // exec les chemins absolu ou ./a.out
	{
		if (access(args, F_OK | X_OK) == 0)
			return (args);
		else
			return (NULL);
	}
	
	temp_path = ft_get_paths(envp);
	valid_path = NULL;
	i = 0;
	while (temp_path[i] && !valid_path)
	{
		valid_path = ft_strjoin_pipex(temp_path[i], args);
		if (access(valid_path, F_OK | X_OK) != 0)
		{
			free(valid_path);
			valid_path = NULL;
		}
		i++;
	}
	ft_free_tab(temp_path);
	if (valid_path != NULL)
	{
		if (access(valid_path, F_OK | X_OK) == 0)
			return (valid_path);
	}
	else
		ft_print_error(args);
	return (valid_path);
}

void	ft_get_argcs(t_data *data, char **av, char **envp)
{
	data->cmd1.args = ft_split(av[2], ' ');
	data->cmd2.args = ft_split(av[3], ' ');
	data->cmd1.path = ft_check_paths(envp, *data->cmd1.args);
	data->cmd2.path = ft_check_paths(envp, *data->cmd2.args);
}
