/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 11:30:13 by avan              #+#    #+#             */
/*   Updated: 2022/12/09 13:10:02 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* Sets all elements to the chosen value within a chosen length
 *
 * @param b: pointer to the element to set value for
 * @param c: chosen value
 * @param len: chosen length
 *
 * @return the pointer back after the setting
 */
void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;
	char	*str;

  if (!b)
    return (NULL);
	str = b;
	i = 0;
	while (i < len)
	{
		str[i] = c;
		i++;
	}
	return (b);
}

/* Joins two arrays of char and frees these
 *
 * @param s1: first array of char
 * @param s2: second array of char
 *
 * @return a dynamically memory allocated array of char resulting
 * of concatening of the second chosen array at the end of the first one
 */
char	*ft_strjoin(char **s1, char **s2)
{
	int		i;
	int		j;
	int		len;
	char	*str;

	len = 0;
	if (s1)
		len = ft_strlen(*s1);
	len += ft_strlen(*s2);
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < len && s1 && *s1 && s1[0][i] != '\0')
	{
		str[i] = s1[0][i];
		i++;
	}
	j = 0;
	while (i < len && s2 && *s2 && s2[0][j] != '\0')
		str[i++] = s2[0][j++];
	str[i] = '\0';
	free(*s1);
	free(*s2);
	return (str);
}

/* Search if the chosen value is found inside the array of char
 *
 * @param s: array of char
 *
 * @return 
 */
int	ft_strchr_int(const char *s, int c)
{
	int	i;

  if (!s)
    return (-1);
	i = 0;
	while (s[i] != (char) c)
	{
		if (!s[i])
			return (0);
		i++;
	}
	return (i + 1);
}

/* Give the length of the array of char
 *
 * @param str: array of char
 *
 * @return the array's length
 */
size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}
