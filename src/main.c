#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char *tmp;

	while (*env)
	{
		if (!strncmp("PATH", *env, 4))
			tmp = ft_strdup(*env);
		env++;
	}

	printf("---------------\n%s\n------------------\n", tmp);
	char **en = ft_split(tmp, ':');
	while (*en)
		printf("%s\n", *en++);
	return 0;
}
