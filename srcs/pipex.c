/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnefo <abonnefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 10:40:53 by abonnefo          #+#    #+#             */
/*   Updated: 2023/05/17 15:17:32 by abonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int parent_process(int f2, int cmd2, t_data *data, char **av, char **envp)
{
	t_cmd	command;


	printf("ICI parent_process 1\n");

	ft_get_argcs(data, av, envp);
	ft_get_paths(envp, data);

	printf("\ncmd1 = %s\n", *data->cmd1.args);
	printf("cmd2 = %s\n", *data->cmd2.args);
	
	printf("\nPATH cmd1 = %s\n", data->cmd1.path);
	printf("PATH cmd2 = %s\n", data->cmd2.path);
	
	execve(data->cmd1.path, *data->cmd1.args, envp);

	// execve()
	
	printf("ICI END parent_process 2\n");

	return (0);
}

int child_process(int f1, int cmd1, t_data *data, char **av, char **envp)
{
	printf("ICI child_process 1\n");

	ft_get_argcs(data, av, envp);
	ft_get_paths(envp, data);

	printf("\ncmd1 = %s\n", *data->cmd1.args);
	printf("cmd2 = %s\n", *data->cmd2.args);
	printf("\nPATH cmd1 = %s\n", data->cmd1.path);
	printf("PATH cmd2 = %s\n", data->cmd2.path);
	
	execve(data->cmd1.path, *data->cmd1.args, envp);

	printf("ICI END child_process 2\n");

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
	
	if (pid < 0) //Erreur lors de la création du processus enfant
	{
		// free
		return (perror("Fork: "));
	}
	if (pid == 0) // executera la 1er cmd
	{
		printf("\n%sJe suis le processus enfant%s\n", MAGENTA, RESET);
		
		close(end[0]); // Ferme l'extrémité de lecture de la pipe
		dup2(end[1], STDOUT_FILENO); // Redirige la sortie standard vers l'extrémité d'écriture de la pipe
		child_process(f1, data->cmd1.args, data, av, envp);
		printf("END de pipex enfant\n");

		close(end[1]); // Ferme l'extrémité d'écriture de la pipe
	}
	else // executera la 2e cmd
	{
		printf("\n%sJe suis le processus parent%s\n", BLUE, RESET);
		
		wait_pid = waitpid(pid, &status, 0); // Attend la terminaison du processus enfant
		close(end[1]); // Ferme l'extrémité d'écriture de la pipe
		dup2(end[0], STDIN_FILENO); // Redirige l'entrée standard vers l'extrémité de lecture de la pipe
		
		printf("ICI pipex parent\n");
		
		parent_process(f2, data->cmd2.args, data, av, envp);
		
		printf("ICI END pipex parent\n");
		
		close(end[0]); // Ferme l'extrémité de lecture de la pipe
	}
	printf("END de pipex\n");

}

int main(int ac, char **av, char **envp)
{
	int	f1;
	int	f2;

	t_data data;
	
	// f1 = open(av[1], O_RDONLY);
	// f2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);

	// if (f1 < 0 || f2 < 0)
	// 	return (-1);
		
	pipex(f1, f2, &data, av, envp);
	
	printf("END je suis sortie youpie\n");

	return (0);
}


/*
int child_process(t_data *data, char **av, char **envp)
{
	pid_t pid;

	pid = fork();

	int fd[2];

	if (pid == 0) // executera la 1er cmd
	{
		printf("\n%sJe suis le processus enfant%s\n", MAGENTA, RESET);
		close(fd[1]);
		ft_get_argcs(data, av, envp);
		ft_get_paths(envp, data);
		close(fd[0]);
	}
	else if (pid > 0) // executera la 2e cmd
	{
		printf("\n%sJe suis le processus parent%s\n", BLUE, RESET);
		close(fd[0]);
		ft_get_argcs(data, av, envp);
		ft_get_paths(envp, data);
		close(fd[1]);
	}
	else
	{
		printf("\n%sErreur lors de la création du processus enfant.\n%s", RED, RESET);
	}

	return (0);
}

int main(int ac, char **av, char **envp)
{
	t_data	data;

	child_process(&data, av, envp);
	// ft_get_argcs(&data, av, envp);
	// ft_get_paths(envp, &data);

	// printf("\ncmd1 = %s\n", *data.cmd1.args);
	// printf("cmd2 = %s\n", *data.cmd2.args);
}
*/