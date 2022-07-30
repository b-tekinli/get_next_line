/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btekinli <btekinli@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 20:29:38 by btekinli          #+#    #+#             */
/*   Updated: 2022/07/27 14:54:57 by btekinli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_get_new_str(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (0);
	}
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!new_str)
		return (0);
	i++;
	j = 0;
	while (str[i] != '\0')
		new_str[j++] = str[i++];
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

char	*ft_get_line(char *str)
{
	int		i;
	int		j;
	char	*line;

	if (str[0] == '\0')
		return (0);
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (0);
	i = 0;
	j = 0;
	while (str[i] != '\n' && str[i] != '\0')
		line[i++] = str[j++];
	if (str[j] == '\n')
		line[i++] = str[j];
	line[i] = '\0';
	return (line);
}

char	*ft_get_str(int fd, char *str)
{
	int		count;
	char	*buff;

	count = 1;
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (0);
	while (!ft_strchr(str, '\n') && count != 0)
	{
		count = read(fd, buff, BUFFER_SIZE);
		if (count == -1)
		{
			free(buff);
			return (0);
		}
		buff[count] = '\0';
		str = ft_strjoin(str, buff);
	}
	free(buff);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str[256];
	char		*line;

	if (fd == -1 && BUFFER_SIZE <= 0)
	{
		free(str);
		return (0);
	}
	str[fd] = ft_get_str(fd, str[fd]);
	if (!str[fd])
		return (0);
	line = ft_get_line(str[fd]);
	str[fd] = ft_get_new_str(str[fd]);
	return (line);
}

/*
int main()
{
	int fd;

	fd = open("t1.txt", O_RDONLY);
	fd = open("t2.txt", O_RDONLY);
	fd = open("t3.txt", O_RDONLY);

	printf("%d", fd);
	return 0;
}
*/

/*
int main()
{
	int fd1 = open("t1.txt", O_CREAT|O_RDWR, 0777);
	int fd2 = open("t2.txt", O_CREAT|O_RDWR, 0777);
	int fd3 = open("t3.txt", O_CREAT|O_RDWR, 0777);

	write(fd1, "11111\naaaaaaaaa\n444444", 30);
	write(fd2, "22222\nbbbbbbb\n5555555", 30);
	write(fd3, "333333\ncccccccc\n66666", 30);

	close(fd1);
	close(fd2);	
	close(fd3);

	fd1 = open("t1.txt", O_CREAT|O_RDWR, 0777);
	fd2 = open("t2.txt", O_CREAT|O_RDWR, 0777);
	fd3 = open("t3.txt", O_CREAT|O_RDWR, 0777);

	printf("a : %d\n", fd1);
	printf("b : %d\n", fd2);
	printf("c : %d\n", fd3);

	
	printf("d : %s\n", get_next_line(fd1));
	printf("e : %s\n", get_next_line(fd2));
	printf("f : %s\n", get_next_line(fd3));

	printf("g : %s\n", get_next_line(fd1));
	printf("h : %s\n", get_next_line(fd2));
	printf("j : %s\n", get_next_line(fd3));
	
	close(fd1);
	close(fd2);
	close(fd2);

	return 0;
}
*/
