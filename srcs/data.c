/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnefo <abonnefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:37:03 by abonnefo          #+#    #+#             */
/*   Updated: 2023/05/11 17:08:30 by abonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	**ft_get_paths(char **envp, t_data	*data) // stock les paths
{
	char	*path;

	path == NULL;
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
	data->all_paths = ft_split(path, ':');
	return (data->all_paths);
}


int	ft_get_argcs(char **argv, t_cmd *cmd1, t_cmd *cmd2)
{
	cmd1->path = argv[2]; // stocke les chaînes elles-mêmes
	cmd2->path = argv[3];
	cmd1->args = ft_split(argv[2], ' '); // changer args en tab
	cmd2->args = ft_split(argv[3], ' ');
	return (0);
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
