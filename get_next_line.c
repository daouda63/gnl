/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaouda <gdaouda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 09:39:49 by gdaouda           #+#    #+#             */
/*   Updated: 2021/08/19 09:36:59 by gdaouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*ft_line(char *l)
{
	int		i;
	char	*rl;

	i = 0;
	while (l[i] != '\n' && l[i])
		i++;
	rl = (char *)malloc((i + 1) * sizeof(char));
	if (rl == NULL)
		return (NULL);
	i = -1;
	while (l[++i])
	{
		rl[i] = l[i];
		if (l[i] == '\n')
		{
			rl[i + 1] = '\0';
			break ;
		}
	}
	return (rl);
}

char	*saveline(char *sl)
{
	int		i;
	int		j;
	char	*srl;

	i = 0;
	j = 0;
	while (sl[i] != '\n' && sl[i])
		i++;
	if (sl[i] == '\0')
	{
		free (sl);
		return (0);
	}
	srl = (char *)malloc(((ft_strlen(sl) - i) + 1) * sizeof(char));
	if (sl == NULL)
		return (NULL);
	i = i + 1;
	while (sl[i] != '\0')
		srl[j++] = sl[i++];
	srl[j] = '\0';
	free (sl);
	return (srl);
}

char	*end_fils(char *sv, char *t)
{
	t = ft_strjoin(sv, t);
	free(sv);
	return (t);
}

char	*mallOc(void)
{
	char	*buffer;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	return (buffer);
}

char	*get_next_line(int fd)
{
	char		*c;
	char		*t;
	int			k;
	static char	*sv;

	k = 1;
	c = mallOc();
	while (k != 0 && ch(sv) == 0)
	{
		k = read(fd, c, BUFFER_SIZE);
		if (k == -1)
			return (nll(c));
		c[k] = '\0';
		if (sv == NULL)
			sv = strdup(c);
		else
			sv = end_fils(sv, c);
	}
	t = ft_line(sv);
	free(c);
	sv = saveline(sv);
	if (k == 0 && ft_strlen(t) == 0)
		return (nll(t));
	return (t);
}
int	main()
{
	ssize_t	fd;
	char	*test;

		fd = open("text.txt", O_RDONLY);
	do
	{
		test = get_next_line(fd);
		puts("-------------main----------");
		printf("|%s|\n", test);
		if (test)
			free(test);
	} while (test != NULL);
	if (test)
		free(test);
	close(fd);
	return (0);
}
