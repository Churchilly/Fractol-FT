/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:13:06 by yusudemi          #+#    #+#             */
/*   Updated: 2025/02/02 04:41:00 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>

static void	error(char *message)
{
	int len;

	len = 0;
	while (message[len])
		len++;
	write(2, message, len);
	exit(1);
}

static double helper(char *str, double fraction, bool dot)
{
	double	res;

	res = 0.0;
	while ((*str >= '0' && *str <= '9') || *str == '.')
	{
		if (*str == '.')
		{
			if (dot)
				error("Wrong input for julia parameter");
			dot = true;
		}
		if (dot)
		{
			fraction /= 10.0;
			res += (*str - '0') * fraction;
		}
		else
			res = res * 10.0 + (*str - '0');
		str++;
	}
	if (*str)
		error("Wrong input for julia parameter");
	return (res);
}

double atod(char *str)
{
	int		sign = 1;
	double	res;

	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	res = helper(str, 1.0, 0);
	return (sign * res);
}

int	strcomp(char *str1, char *str2)
{
	if (!str1)
		return (0);
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (0);
		str1++;
		str2++;
	}
	return (1);
}
