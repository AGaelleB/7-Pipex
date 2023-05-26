/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnefo <abonnefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 10:59:39 by abonnefo          #+#    #+#             */
/*   Updated: 2023/05/26 09:53:29 by abonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// # define INT_MAX 2147483647
// # define INT_MIN -2147483648

# define RESET "\033[0m"
# define BLACK "\033[30m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdint.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>

# include "../includes/ft_printf.h"
# include "../includes/get_next_line.h"
# include "../includes/libft.h"

typedef struct s_cmd
{
	char	*path;
	char	**args;
}	t_cmd;

typedef struct s_data
{
	char			**all_argcs;
	t_cmd			cmd1;
	t_cmd			cmd2;
	struct s_data	*next;
}	t_data;

/********************************* pipex.c ************************************/

/********************************* utils.c ************************************/

int		ft_strncmp_pipex(char *s1, char *s2, int n);
char	*ft_strjoin_pipex(char *s1, char *s2);
void	ft_free_tab(char **tab);

/********************************* data.c ************************************/

char	*ft_check_paths(char **envp, char *args);
t_cmd	split_cmd(char *cmd_av, char **envp);
char	**ft_get_paths(char **envp);
void	ft_get_argcs(t_data *data, char **av, char **envp);

#endif