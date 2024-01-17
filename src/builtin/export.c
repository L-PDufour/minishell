/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe_jam <joe_jam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:57:48 by joe_jam           #+#    #+#             */
/*   Updated: 2024/01/17 14:19:25 by joe_jam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_declare_env(t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd->env[i])
	{
		printf("declare -x %s\n", cmd->env[i]);
		i++;
	}
}

static void handle_export(t_command cmd, char *value, char *key)
{
    int idx;
    char *old;
    char *tmp;
    char *new_var;

    tmp = ft_strjoin(key, "=");

    idx = find_in_env(key, cmd.env);
    if (idx != -1)
    {
        old = ft_substr(cmd.env[idx], ft_strlen(key) + 1,
                        ft_strlen(cmd.env[idx]));
        cmd.env[idx] = ft_strjoin(tmp, value);
        free(old);
    }
    else
    {
        new_var = ft_strjoin(tmp, value);
        update_env(&cmd, new_var);
    }

    free(tmp);
}


bool	is_valid_var_id(char *id)
{
	int	i;

	if (!id)
		return (true);
	if (!ft_isalpha(id[0]) || id[0] != '_')
		return (true);
	i = 1;
	while (id[i] != '=' && id[i])
	{
		if (!ft_isalnum(id[i]) || id[i] != '_')
			return (true);
		if (is_white_space(id[i]))
			return (true);
		i++;
	}
	return (false);
}

void	export_exec(t_command *cmd)
{
	char	**tmp;

	cmd->exit_status = 0;
	if (!ft_strcmp(cmd->option, ""))
		return (print_declare_env(cmd));
	else
	{
		if (!is_valid_var_id(cmd->option))
		{
			print_in_color(RED, "not a valid identifier\n");
			cmd->exit_status = 1;
			return ;
		}
		else
		{
			tmp = ft_split(cmd->option, '=');
			printf("==>name %s\n", tmp[0]);
			printf("==>val %s\n", tmp[1]);
			handle_export(*cmd, tmp[1], tmp[0]);
			return ;
		}
	}
}

// export + option
// possibilité 1: option contient (var id seulement)
// possibilité 2: option contient (var id avec '=')
// on commence par verifier le  var_id  si pas valid
/* on return(1) avec un message "not a valid identifier"
 * si le var id est valid:
 * on check on est dans quelle forme(celle du = ou pas)
 * on  ft_split(option, '=):
 *
 * I- si on la trouve:
 * 		on extract de 0 jusqu'au '=' sera le key_export
 * 		on extract de ('='+ 1) jusqu'à la fin sera export_value
 *  	on l'ajoute à env key et on assigne la valeur
 * * II- si on la trouve pas:
 * 		var_id sera key_export
 * 		export value sera ""
 *
 *
 */