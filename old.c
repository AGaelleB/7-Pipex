
char	*ft_check_paths(char **envp, char *args) // a decouper
{
	char	**temp_path;
	char	*valid_path;
	int		i;

	if (ft_strchr_slash(args, '/') == 1)
	{
		if (access(args, F_OK | X_OK) == 0)
		{
			valid_path = ft_strdup(args);
			return (valid_path);
		}
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