/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 09:33:37 by hthomas           #+#    #+#             */
/*   Updated: 2020/09/18 15:41:13 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef minishell_H
# define minishell_H

# include <unistd.h>
# include <sys/types.h>
# include <time.h>
# include <stdlib.h>
# include <math.h>
# include <errno.h>
# include "../libft/libft.h"
# include "../ft_printf/includes/ft_printf.h"
# include "get_next_line.h"

//Commands
char	*ft_echo(char **args);
char	*ft_cd(char **args);
char	*ft_pwd(void);
char	*ft_export(char **args);
char	*ft_unset(char **args);
char	*ft_env(char **args);
char	*ft_exit(char **args);

//Parse
int		parse_input(char *line, char ***args);

//Utils
void	ft_putstr_clean(char *str);











































# define WELCOME_MSG "────────────▄███████████████▄───────────\n\
─────────██████▀───██───▀███████────────\n\
──────███───▀███───██───███▀───███──────\n\
─────██████───██───██───██───██████─────\n\
─────██───██───██──██──██───██───██─────\n\
────███────██──██──██──██──██────███────\n\
────██─██───██──█──██──█──██───██─██────\n\
────██──███──██─██─██─██─██──███──██────\n\
────██────██──██─█─██─█─██──██────██────\n\
────████▄───██─█──█──█──█──█───▄████────\n\
───────████───█──────────█───████───────\n\
──────────██────────────────██──────────\n\
──────────████████▄──▄████████──────────\n\
──────────────────▀██▀──────────────────\n\
           _       _     _          _ _\n\
 _ __ ___ (_)_ __ (_)___| |__   ___| | |\n\
| '_ ` _ \\| | '_ \\| / __| '_ \\ / _ \\ | |\n\
| | | | | | | | | | \\__ \\ | | |  __/ | |\n\
|_| |_| |_|_|_| |_|_|___/_| |_|\\___|_|_|\n\n"


/*
────────────────────────────────\n\
────────▄███████████████▄───────\n\
───────███████████████████──────\n\
─────██████▀───██───▀███████────\n\
───████████────██────████████───\n\
──███───▀███───██───███▀───███──\n\
──████────██───██───██────████──\n\
─██████───██───██───██───██████─\n\
─██──██───██───██───██───██──██─\n\
─██───██───██──██──██───██───██─\n\
███───██───██──██──██───██───███\n\
███────██──██──██──██──██────███\n\
████───██──██──██──█───██───████\n\
██─██───██──█──██──█──██───██─██\n\
██──██──██──██─██─██──██──██──██\n\
██──███──██─██─██─██─██──███──██\n\
██───██──██──█─██─█──██──██───██\n\
██────██──██─█─██─█─██──██────██\n\
███▄───██──█─█─██─█─█───█───▄███\n\
████▄───██─█──█──█──█──█───▄████\n\
─█████───█──█─█──█─█──█───█████─\n\
───████───█──────────█───████───\n\
─────███────────────────███─────\n\
──────██────────────────██──────\n\
──────██────────────────██──────\n\
──────████████▄──▄████████──────\n\
──────████████████████████──────\n\
──────────────▀██▀──────────────\n\
*/

#endif