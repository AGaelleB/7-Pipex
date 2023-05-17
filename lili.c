/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lili.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnefo <abonnefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:21:25 by abonnefo          #+#    #+#             */
/*   Updated: 2023/05/17 14:22:49 by abonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_cmd
{
	char	*path;
	char	**args;
}	t_cmd;

typedef struct s_data
{
	char	**all_argcs;
	t_cmd	cmd1;
	t_cmd	cmd2;
	struct s_data	*next; //
}	t_data;


size_t	ft_strlcpy_pipex(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (dstsize == 0)
		return (ft_strlen(src));
	i = 0;
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '/';
	return (ft_strlen(src));
}

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
	char	*str;
	size_t	size_s1;
	size_t	size_s2;

	if (s1 == 0 || s2 == 0)
		return (NULL);
	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	str = malloc(sizeof(*str) * (size_s1 + size_s2 + 1));
	if (str == 0)
		return (NULL);
	ft_strlcpy_pipex(str, s1, (size_s1 + 1));
	ft_strlcat(str, s2, (size_s1 + size_s2 + 2));
	return (str);
}

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

t_cmd	split_cmd(t_data *data, char *cmd_av, char **envp)
{
	t_cmd	command;

	command.args = ft_split(cmd_av, ' ');
	command.path = ft_check_paths(data, envp, *command.args);
	if (execve(command.path, command.args, envp) == -1)
	{
		perror("Execve");
		exit (0);
	}
	else
		execve(command.path, command.args, envp);
	return (command);
}

char	**ft_get_paths(char **envp, t_data	*data)
{
	printf("\n *** ft_get_paths *** \n");
	char	*path;
	char	**all_paths;

	while (*envp)
	{
		if (ft_strncmp_pipex("PATH=", *envp, 5) == 0)
		{
			path = &((*envp)[5]);
			break ;
		}
		envp++;
	}
	if (path == NULL)
		return (NULL);
	all_paths = ft_split(path, ':');
	return (all_paths);
}

void	ft_get_argcs(t_data *data, char **av, char **envp)
{
	printf("\n *** ft_get_argcs *** \n");
	data->cmd1 = split_cmd(data, av[2], envp);
	data->cmd2 = split_cmd(data, av[3], envp);
}


int parent_process(int f2, int cmd2, t_data *data, char **av, char **envp)
{
	ft_get_argcs(data, av, envp);
	ft_get_paths(envp, data);

	return (0);
}

int child_process(int f1, int cmd1, t_data *data, char **av, char **envp)
{
	ft_get_argcs(data, av, envp);
	ft_get_paths(envp, data);

	return (0);
}

void	pipex(int f1, int f2, t_data *data, char **av, char **envp)
{
	int	end[2];

	pid_t	pid;
	pid_t	wait_pid;
	int		status;

	pipe(end);

	pid = fork();
	
	if (pid < 0)
	{
		return (perror("Fork: "));
	}
	if (pid == 0) // executera la 1er cmd
	{
		printf("\n%sJe suis le processus enfant%s\n", MAGENTA, RESET);
		
		close(end[0]); // Ferme l'extrémité de lecture de la pipe
		dup2(end[1], STDOUT_FILENO); // Redirige la sortie standard vers l'extrémité d'écriture de la pipe
		child_process(f1, data->cmd1.args, data, av, envp);
			printf("END de pipex\n");

		close(end[1]); // Ferme l'extrémité d'écriture de la pipe
	}
	else // executera la 2e cmd
	{
		printf("\n%sJe suis le processus parent%s\n", BLUE, RESET);
		
		wait_pid = waitpid(pid, &status, 0); // Attend la terminaison du processus enfant
		close(end[1]); // Ferme l'extrémité d'écriture de la pipe
		dup2(end[0], STDIN_FILENO); // Redirige l'entrée standard vers l'extrémité de lecture de la pipe
		parent_process(f2, data->cmd2.args, data, av, envp);
		close(end[0]); // Ferme l'extrémité de lecture de la pipe
	}
	printf("END de pipex\n");

}

int main(int ac, char **av, char **envp)
{
	int	f1;
	int	f2;

	t_data data;

	pipex(f1, f2, &data, av, envp);
	
	printf("END je suis sortie youpie\n");

	return (0);
}