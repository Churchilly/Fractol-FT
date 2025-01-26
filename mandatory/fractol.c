/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 01:57:11 by yusudemi          #+#    #+#             */
/*   Updated: 2025/01/26 20:40:32 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "../minilibx/mlx.h"
#include "../fractol.h"

static int	strcomp(char *str1, char *str2)
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

void	_init(t_fractal fractal)
{
	t_mlx mlx;

	mlx.connection = mlx_init();
	mlx.window = mlx_new_window(mlx.connection, 600, 800, "FRACTOL");
	mlx.image = mlx_new_image(mlx.connection, 600, 800);
	mlx.addr = mlx_get_data_addr(mlx.connection, &mlx.bits_per_pixel, &mlx.line_length, &mlx.endian)
}

void	julia(t_fractal fractal);
{
	
}

void	mandelbrot(t_fractal fractal)
{
	
}
int	main(int argc, char **argv)
{
	t_fractal fractal;
		
	_init()
	if (argc == 4 && strcomp(argv[1], "julia"))
		julia(mlx);
	else if (argc == 2 && strcomp(argv[1], "mandelbrot"))
		mandelbrot();		
	else
	{
		write(1, "Usage: ./fractol [FRACTAL-SET]\n", 27);
		write(1, "                 Mandelbrot\n", 27);
		write(1, "                 Julia <parameters>\n", 27);
		exit(EXIT_FAILURE);
	}
	mlx_put_image_to_window();
	mlx_hook();
	mlx_loop();
}
