/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toto <toto@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 22:42:38 by toto              #+#    #+#             */
/*   Updated: 2024/11/28 15:20:24 by toto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// ---------------- -------------------
int	ft_verif_newline(t_stash *stash)
{
	int	i;

	i = 0;
	if (!stash)
		return (0);
	while (stash)
	{
		i = 0;
		while (i < BUFFER_SIZE - 1)
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
t_stash	**ft_read(int fd, t_stash **stash)
{
	char	*buffer;
	t_stash *node;
	ssize_t	b_read;
	int i;

	i = 0;
	while (!ft_verif_newline(*stash))
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE));
		if (!buffer)
			return (NULL);
		b_read = read(fd, buffer, BUFFER_SIZE - 1);
		if (b_read == -1)
		{
			free (buffer);
			return (NULL);
		}
		buffer[b_read] = '\0';
		node = ft_lstnew(buffer);
		ft_lstadd_back(stash, node);
	}
	return (stash);
}

char	*ft_create_line(t_stash *stash)
{
	char	*line;
	int		i;
	int		j;
	
	i = 0;
	j = 0;
	line = malloc(sizeof(char) * 100);
	while (stash)
	{
		i = 0;
		while (i < BUFFER_SIZE - 1)
		{
			if (stash->content[i] == '\n')
			{
				line[j] = '\n';
				line[j+1] = '\0';
				return (line);
			}
			line[j] = stash->content[i];
			j++;
			i++;
		}
		stash = stash->next;
	}
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
	t = malloc(sizeof(char) * BUFFER_SIZE);
	tempnode =  ft_lstlast((*stash));
	while (tempnode->content[i] != '\n' && tempnode->content[i] != '\0')
		i++;
	i++;
	while (tempnode->content[i] != '\0')
	{
		t[j] = tempnode->content[i];
		i++;
		j++;
	}
	t[j] = '\0';
	ft_lstclear(stash);
	tempnode = ft_lstnew(t);
	printf("Nouvelle stash: |%s|\n", tempnode->content);
	ft_lstadd_back(stash, tempnode);
	return (stash);
}

char	*get_next_line(int fd)
{
	static	t_stash	*stash = NULL;
	char	*buffer;
	
	ft_read(fd, &stash);
	
    // Afficher le contenu de stash pour vérification
    // creation de la variable line
	buffer = ft_create_line(stash);
	
	// Vidage de la liste
	ft_stash(&stash);

	return (buffer);
}

int	main()
{
	int	fd;
	char	*result;
	
	fd = open("text.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Errour lors de la lecture du fichier");
		return (1);
	}
	result = get_next_line(fd);
	printf("Ligne : %s", result);
	free(result);
	result = get_next_line(fd);
	printf("Ligne : %s", result);
	free(result);
}