/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lower.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 17:39:43 by imicah            #+#    #+#             */
/*   Updated: 2020/09/22 17:39:45 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_lower(char *c)
{
	int 	i;

	i = 0;
	while (c[i])
	{
		if (c[i] >= 65 && c[i] <= 90)
			c[i] += 32;
		i++;
	}
	return (c);
}
