/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_alloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrimaud <jgrimaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:47:44 by jgrimaud          #+#    #+#             */
/*   Updated: 2024/04/26 08:32:28 by jgrimaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s, void *data)
{
	return (ft_strndup(s, ft_strlen(s), data));
}

char	*ft_strndup(const char *s, size_t n, void *data)
{
	char	*dup;
	size_t	i;

	dup = ft_malloc(sizeof(char) * (n + 1), data);
	i = 0;
	while (s[i] && i < n)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strjoin(char const *s1, char const *s2, void *data)
{
	char	*str;
	size_t	str_len;

	if (!s1 || !s2)
		return (NULL);
	str_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = ft_malloc(sizeof(char) * str_len, data);
	str[0] = '\0';
	ft_strlcat(str, s1, str_len);
	ft_strlcat(str, s2, str_len);
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len, void *data)
{
	char	*substr;
	size_t	strlen;
	size_t	i;

	if (!s || len == 0)
		return (NULL);
	strlen = ft_strlen(s);
	if (start >= strlen)
		return (NULL);
	if (len > strlen - start)
		len = strlen - start;
	substr = ft_malloc(sizeof(char) * (len + 1), data);
	i = 0;
	while (s[start + i] && i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

char	*ft_strtrim(char const *s1, char const *set, void *data)
{
	size_t	i;
	size_t	start;
	size_t	end;

	if (!s1 || !set || ft_strlen(s1) == 0)
		return ((char *)s1);
	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	start = i;
	i = ft_strlen(s1) - 1;
	while (i > 0 && ft_strchr(set, s1[i]))
		i--;
	end = i;
	if (end >= start)
		return (ft_substr(s1, start, end - start + 1, data));
	else
		return (NULL);
}
