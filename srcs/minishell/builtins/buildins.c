/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 12:40:22 by imicah            #+#    #+#             */
/*   Updated: 2020/09/17 11:33:29 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		echo(t_arguments *arguments, t_list *env_list)
{
	int		flag;

	(void)env_list;
	flag = 1;
	if (*arguments->argv && !ft_strcmp(*(arguments->argv), "-n"))
	{
		flag = 0;
		arguments->argv++;
	}
	while (*(arguments->argv))
	{
		ft_putstr_fd(*(arguments->argv)++, 1);
		if (*(arguments->argv))
			write(1, " ", 1);
	}
	write(1, "\n", (size_t)flag);
	return (errno);
}

int		pwd(t_arguments *arguments, t_list *env_list)
{
	char	*cwd;

	(void)arguments;
	(void)env_list;
	cwd = getcwd(NULL, 0);
	ft_putendl_fd(cwd, 1);
	free(cwd);
	return (errno);
}

void	export_home_env(char *key, t_list *env_list)
{
	t_arguments	argument;
	char		*arg[2];
	char		*cwd;

	cwd = getcwd(NULL, 0);
	arg[0] = ft_strjoin(key, cwd);
	arg[1] = NULL;
	argument.argv = arg;
	export(&argument, env_list);
	free(cwd);
	free(arg[0]);
}

int		cd(t_arguments *arguments, t_list *env_list)
{
	char	*home;

	export_home_env("OLDPWD=", env_list);
	if (*arguments->argv == NULL)
	{
		home = get_env_value("HOME", env_list);
		if (*home)
			chdir(home);
		else
		{
			ft_putstderr("minishell: cd: HOME not set");
			return (errno);
		}
	}
	else
	{
		ft_lower(*arguments->argv);
		chdir(*arguments->argv);
	}
	export_home_env("PWD=", env_list);
	return (errno);
}

int		ft_exit(t_arguments *arguments, t_list *env_list)
{
	int		exit_number;

	exit_number = 0;
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (ft_str_double_len(arguments->argv) > 1)
	{
		ft_putstderr("minishell: exit: argument list too long");
		return (errno);
	}
	else if (*arguments->argv && ((!ft_isdigit(*arguments->argv) &&
			**arguments->argv != '-') || !**arguments->argv))
	{
		ft_putstr_fd("\e[1m\e[31mminishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(*arguments->argv, STDERR_FILENO);
		ft_putendl_fd(": a numeric is required\e[0m", STDERR_FILENO);
		exit_number = 255;
	}
	if (*arguments->argv && exit_number == 0)
		exit_number = ft_atoi(*arguments->argv);
	ft_lstclear(env_list, &free_env);
	free_double_array(arguments->argv);
	exit(exit_number);
}
