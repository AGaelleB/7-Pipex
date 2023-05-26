/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnefo <abonnefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:37:03 by abonnefo          #+#    #+#             */
/*   Updated: 2023/05/26 13:53:24 by abonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*stock les paths*/
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

char	*ft_check_paths(char **envp, char *args)
{
	char	**temp_path;
	char	*valid_path;
	int		i;

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
		perror("Error : invalid path");
	return (valid_path);
}

t_cmd	split_cmd(char *cmd_av, char **envp)
{
	t_cmd	command;

	command.args = ft_split(cmd_av, ' ');
	command.path = ft_check_paths(envp, *command.args);
	return (command);
}

void	ft_get_argcs(t_data *data, char **av, char **envp)
{
	data->cmd1 = split_cmd(av[2], envp);
	if (data->cmd1.path == NULL)
	{
		ft_free_tab(data->cmd1.args);
		exit(0);
	}
	data->cmd2 = split_cmd(av[3], envp);
	if (data->cmd2.path == NULL)
	{
		ft_free_tab(data->cmd1.args);
		ft_free_tab(data->cmd2.args);
		free(data->cmd1.path);
		exit(0);
	}
}
