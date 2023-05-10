/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnefo <abonnefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:37:03 by abonnefo          #+#    #+#             */
/*   Updated: 2023/05/10 17:36:31 by abonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	**ft_get_paths(char **envp, t_data	*data) // stock les paths
{
	char	*path;

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
		return(0); // faire return mon erreur ici
	data->all_paths = ft_split(path, ':');
	return (data->all_paths);
}



char	**ft_get_argc(char **cmd1, char **cmd2, t_data	*data) // stock les argc
{

	return (data->all_argcs);
}


// char	**ft_get_argc(int ac, char **av, t_data	*data) // stock les argc
// {
// 	int		i;

// 	i = 1;
// 	while(i < ac)
// 	{
// 		data->all_argcs = ft_split(av[i], ' '); // av[1] av[2]
// 		printf("argc = %s\n", *data->all_argcs); // test impression argc
// 		i++;
// 	}
// 	return (data->all_argcs);
// }
