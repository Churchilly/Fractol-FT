/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 01:57:11 by yusudemi          #+#    #+#             */
/*   Updated: 2025/02/05 23:03:56 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "fractol_bonus.h"
#include "../minilibx/mlx.h"
#include <stdbool.h>

static void	mlx_setup(t_data *d)
{
	d->connection = mlx_init();
	if (!d->connection)
		exit(1);
	d->window = mlx_new_window(d->connection, WIDTH, HEIGHT, "Fractol");
	if (!d->window)
	{
		mlx_destroy_display(d->window);
		free(d->connection);
		exit(1);
	}
	d->image = mlx_new_image(d->connection, WIDTH, HEIGHT);
	if (!d->image)
	{
		mlx_destroy_window(d->connection, d->window);
		mlx_destroy_display(d->window);
		free(d->connection);
		exit(1);
	}
	d->addr = mlx_get_data_addr(d->image, &(d->bits_per_pixel),
			&(d->line_length), &(d->endian));
}

int	main(int argc, char **argv)
{
	t_data	data;

	init_data(&data);
	init_set(&data, argc, argv);
	if (data.set == NULL_SET)
	{
		write(1, "Usage: ./fractol Fractal-Set\n", 30);
		write(1, "                 mandelbrot\n", 29);
		write(1, "                 julia <real> <imaginary>\n", 43);
		write(1, "                 tricorn\n", 26);
		exit(1);
	}
	mlx_setup(&data);
	render_image(&data);
	events_setup(&data);
	mlx_loop(data.connection);
	return (0);
}
