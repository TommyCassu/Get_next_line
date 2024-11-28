/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toto <toto@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 22:42:38 by toto              #+#    #+#             */
/*   Updated: 2024/11/28 21:30:47 by toto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// ---------------- -------------------
int	ft_verif_newline(t_stash *stash)
{
	int	i;

	i = 0;
	if (stash == NULL)
		return (0);
	while (stash)
	{
		i = 0;
		while (i < BUFFER_SIZE && stash->content[i] != '\0')
		{
			if (stash->content[i] == '\n')
				return (1);
			i++;
		}
		stash = stash->next;
	}
	return (0);
}

// Lis le fichier et alloue une memoire en fonction de la size choisi
// L'ajoute a la fin de la lst
void	ft_read(int fd, t_stash **stash)
{
	char	*buffer;
	t_stash *node;
	ssize_t	b_read;

	while (!ft_verif_newline(*stash))
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer)
			return ;
		b_read = read(fd, buffer, BUFFER_SIZE);
		if (b_read <= 0)
		{
			free(buffer);
			return ;
		}
		buffer[b_read] = '\0';
		node = ft_lstnew(buffer);
		ft_lstadd_back(stash, node);
	}
}

char	*ft_create_line(t_stash *stash)
{
	char	*line;
	int		i;
	int		j;
	
	i = 0;
	j = 0;

	line = malloc(sizeof(char) * (ft_count_lst(stash) + 2));
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				line[j] = '\n';
				line[++j] = '\0';
				return (line);
			}
			line[j++] = stash->content[i++];
		}
		stash = stash->next;
	}
	line[j] = '\0';
	return (line);
}

t_stash	**ft_stash(t_stash **stash)
{
	t_stash	*tempnode;
	char	*t;
	int	i;
	int	j;

	i = 0;
	j = 0;
	t = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!t)
		return (NULL);
	tempnode =  ft_lstlast((*stash));
	if (!tempnode || !tempnode->content) 
	{
		free(t);
    	return NULL;
	}
	while (tempnode->content[i] != '\n' && tempnode->content[i])
		i++;
	while (tempnode->content[i] && tempnode->content[++i])
		t[j++] = tempnode->content[i];		
	t[j] = '\0';
	ft_lstclear(stash);
	tempnode = ft_lstnew(t);
	ft_lstadd_back(stash, tempnode);
	return (stash);
}

char	*get_next_line(int fd)
{
	static	t_stash	*stash = NULL;
	char	*buffer;
	
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &buffer, 0) < 0)
		return (NULL);
	ft_read(fd, &stash);

	buffer = ft_create_line(stash);
	if ((buffer == NULL || buffer[0] == '\0') && !ft_verif_newline(stash)) { 
        ft_lstclear(&stash);
		free(buffer);
		buffer = NULL;
        return NULL; // Retournez NULL
    }
	// Vidage de la liste
	ft_stash(&stash);

	return (buffer);
}
