/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:01:45 by avan              #+#    #+#             */
/*   Updated: 2022/12/09 14:15:23 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* Takes the array of char and splits it at the '\n', returns the first part in
 * tocutre and the second part in the memory for the next reading
 *
 * @param tocutre: pointer to the array of char
 * @param i: index where '\n' is
 * @param len: index to calculate the size of the memory array of char
 *
 * @return a memory array of char, at the same time, it allocated new memory to
 * the tocutre array of char
 */
static char	*ft_minisplit(char **tocutre, int i, int len)
{
	int		j;
	char	*temp;
	char	*mem;
	char	*s;

	s = *tocutre;
	temp = (char *) malloc(sizeof(char) * (i + 1));
	if (temp == NULL)
		return (NULL);
	j = -1;
	while (s[++j] && j < i)
		temp[j] = s[j];
	temp[j] = '\0';
	while (s[len] != '\0')
		len++;
	mem = (char *) malloc(sizeof(char) * (len - i + 1));
	if (!mem)
		return (free(temp), NULL);
	j = -1;
	while (s[++j] && j < (len - i))
		mem[j] = s[j + i];
	mem[j] = '\0';
	free(*tocutre);
	*tocutre = temp;
	return (mem);
}

/* Whatever the buffer size, this function continues to add what it reads to the buffer
 *
 * @param fd
 * @param buffer: can read multiple fds, up to 1023
 * @param checkread: parameter that checks if the function has read anything
 * @param result: return value
 *
 * @return an array of char containing the next line read, it is dynamically allocated memory
 * wise, it must be freed by the user after use
 */
static char	*ft_growbuffer(int fd, char **buffer, int checkread, char *result)
{
	char	*temp;
	int		checkn;

	if (*buffer)
		result = *buffer;
	*buffer = NULL;
	while (checkread > 0)
	{
		temp = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!temp)
			return (NULL);
		ft_memset(temp, 0, BUFFER_SIZE);
		checkread = read(fd, temp, BUFFER_SIZE);
		if (checkread == -1)
			return (free(temp), NULL);
		temp[BUFFER_SIZE] = '\0';
		result = ft_strjoin(&result, &temp);
		checkn = ft_strchr_int(result, '\n');
		if (checkn > 0)
		{
			*buffer = ft_minisplit(&result, checkn, 0);
			break ;
		}
	}
	return (result);
}

/* Takes a file descriptor and give the next line read
 *
 * @param fd
 *
 * @return an array of char containing the next line read, it is dynamically allocated memory
 * wise, it must be freed by the user after use
 */
char	*get_next_line(int fd)
{
	char		*result;
	static char	*buffer[1024];

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	result = ft_growbuffer(fd, &buffer[fd], 1, NULL);
	if (result[0] == '\0')
		return (free(result), NULL);
	return (result);
}
