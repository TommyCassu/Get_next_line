/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toto <toto@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 22:43:48 by toto              #+#    #+#             */
/*   Updated: 2024/11/28 14:59:19 by toto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 6
# endif

typedef	struct s_stash
{
	char			*content;
	struct s_stash	*next;
}				t_stash;

void	ft_lstadd_back(t_stash **lst, t_stash *new);
t_stash	*ft_lstnew(void *content);
t_stash	*ft_lstlast(t_stash *lst);
void	ft_lstclear(t_stash **lst);

#endif