/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnefo <abonnefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:37:03 by abonnefo          #+#    #+#             */
/*   Updated: 2023/05/25 15:52:56 by abonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*ft_check_paths(t_data *data, char **envp, char *args)
{
	char	**temp_path;
	char	*valid_path;
	int		i;

	temp_path = ft_get_paths(envp, data);
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
	if (access(valid_path, F_OK | X_OK) == 0)
		return (valid_path);
	else
	{
		perror("Access");
		exit(0);
	}
	return (valid_path);
}

t_cmd	split_cmd(t_data *data, char *cmd_av, char **envp)// mets les args en tabs
{
	t_cmd	command;

	command.args = ft_split(cmd_av, ' ');
	command.path = ft_check_paths(data, envp, *command.args);
	// if (execve(command.path, command.args, envp) == -1)
	// {
	// 	perror("Execve");
	// 	exit (0);
	// }
	// else
	// {
	// 	execve(command.path, command.args, envp);
	// }

	return (command);
}

char	**ft_get_paths(char **envp, t_data	*data)// stock les paths
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

void	ft_get_argcs(t_data *data, char **av, char **envp) // recup les ARGS
{
	data->cmd1 = split_cmd(data, av[2], envp);
	data->cmd2 = split_cmd(data, av[3], envp);
}
