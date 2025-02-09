/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:13:06 by yusudemi          #+#    #+#             */
/*   Updated: 2025/02/10 02:41:14 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>

static void	error(char *message)
{
	int	len;

	len = 0;
	while (message[len])
		len++;
	write(2, message, len);
	write(1, "Julia Parameters must be double values.\n", 41);
	write(1, "Usage: ./fractol Fractal-Set\n", 30);
	write(1, "                 mandelbrot\n", 29);
	write(1, "                 julia <real> <imaginary>\n", 43);
	exit(1);
}

static double	helper(char *str, double fraction, bool dot)
{
	double	res;

	res = 0.0;
	while ((*str >= '0' && *str <= '9') || *str == '.')
	{
		if (*str == '.')
		{
			if (dot)
				error("Error: Wrong input for julia parameter\n");
			dot = true;
			str++;
		}
		if (dot && *str <= '9' && *str >= '0')
		{
			fraction /= 10.0;
			res += (*str - '0') * fraction;
		}
		else if (!dot && *str <= '9' && *str >= '0')
			res += res * 10.0 + (*str - '0');
		else
			error("Error: Wrong input for julia parameter\n");
		str++;
	}
	if (*str)
		error("Error: Wrong input for julia parameter\n");
	return (res);
}

double	atod(char *str)
{
	int		sign;
	double	res;

	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	res = helper(str, 1.0, false);
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
	if ((!(*str2) && *str1) || (!(*str1) && *str2))
		return (0);
	return (1);
}
