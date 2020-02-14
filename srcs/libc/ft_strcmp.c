/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 14:34:11 by rpinoit           #+#    #+#             */
/*   Updated: 2020/02/14 14:34:17 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char c1;
	unsigned char c2;

	c1 = (unsigned char)*s1++;
	c2 = (unsigned char)*s2++;
	if (c1 == '\0')
		return (c1 - c2);
	while (c1 == c2)
	{
		c1 = (unsigned char)*s1++;
		c2 = (unsigned char)*s2++;
		if (c1 == '\0')
			return (c1 - c2);
	}
	return (c1 - c2);
}
