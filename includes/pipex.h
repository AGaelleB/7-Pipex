/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnefo <abonnefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 10:59:39 by abonnefo          #+#    #+#             */
/*   Updated: 2023/06/14 14:54:43 by abonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdio.h>
# include <stdint.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>

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

void	ft_get_argcs(t_data *data, char **av, char **envp);

/***************************** libft_modify.c *********************************/

int		ft_strchr_slash(char *str, char c);
int		ft_strncmp_pipex(char *s1, char *s2, int n);
char	*ft_strjoin_pipex(char *s1, char *s2);

/********************************* utils.c ************************************/

void	ft_free_tab(char **tab);
void	ft_free_all_data(t_data *data);
void	ft_print_error(char *str);

/********************************** path.c ************************************/

char	*ft_check_paths(char **envp, char *args);
t_cmd	split_cmd(char *cmd_av, char **envp);
char	**ft_get_paths(char **envp);
void	ft_get_argcs(t_data *data, char **av, char **envp);

#endif