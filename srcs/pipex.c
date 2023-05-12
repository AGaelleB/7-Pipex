/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnefo <abonnefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 10:40:53 by abonnefo          #+#    #+#             */
/*   Updated: 2023/05/12 15:10:19 by abonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*
utiliser sstrjoin pour coller la cmd au path ex : /mnt/nfs/homes/abonnefo/bin/ls
Faire une fonction qui cherchera si chaque commande a un chemin qui correspond
Puis verifier si le chemin de la fonction marche
*/

char	*ft_check_paths(t_data *data, char **envp, char *args) 
{
	char	**temp_path;
	int		i;
	char	*valid_path;

	i = 0;
	temp_path = ft_get_paths(envp, data);
	while(temp_path[i])
	{
		valid_path = ft_strjoin_pipex(temp_path[i], args);
		 printf("PATH de mes cmd : %s\n", valid_path);
		i++;
	}
	return (valid_path);
}

t_cmd	split_cmd(t_data *data, char *cmd_av, char **envp)
{
	t_cmd	command;

	command.args = ft_split(cmd_av, ' ');
	
	command.path = ft_check_paths(data, envp, *command.args);

	return (command);
}

void	ft_get_argcs(t_data *data, char **av, char **envp)
{
	data->cmd1 = split_cmd(data, av[2], envp);
	data->cmd2 = split_cmd(data, av[3], envp);

}

char	**ft_get_paths(char **envp, t_data	*data) // stock les paths
{
	char	*path;
	char	**all_paths;

	while(*envp)
	{
		if (ft_strncmp_pipex("PATH=", *envp, 5) == 0)
		{
			path = &((*envp)[5]); // a revoir
			printf("\nenvp = %s\n", *envp); // test impression paths
			break;
		}
		envp++;
	}
	if (path == NULL)
		return(NULL); // faire return mon erreur ici avec perror()
	all_paths = ft_split(path, ':');
	return (all_paths);
}

int main(int ac, char **av, char **envp)
{
	t_data	data;

	ft_get_argcs(&data, av, envp);
	
	ft_get_paths(envp, &data);

	printf("\ncmd1 = %s\n", *data.cmd1.args);
	printf("cmd2 = %s\n", *data.cmd2.args);
}
