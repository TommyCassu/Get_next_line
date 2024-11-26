/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toto <toto@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 22:42:38 by toto              #+#    #+#             */
/*   Updated: 2024/11/26 23:46:04 by toto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// ---------------- -------------------

void	ft_read(int fd, t_stash **stash)
{
	char	*buffer;
	ssize_t	b_read;
	int i;

	i = 0;
	while (!verif_newline(*stash))
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE));
		if (!buffer)
			return ;
		b_read = read(fd, buffer, BUFFER_SIZE - 1);
		if (b_read == -1)
		{
			free (buffer);
			return ;
		}
		buffer[b_read] = '\0';
		ft_lstadd_back(stash, buffer);
	}
	
	
}

char	*get_next_line(int fd)
{
	static	t_stash	*stash = NULL;
	t_stash *node;
	//char	*line;
	char	*buffer;
	ssize_t	b_read;
	
	
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
	printf("%s", result);
}