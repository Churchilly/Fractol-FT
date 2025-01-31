/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 01:57:11 by yusudemi          #+#    #+#             */
/*   Updated: 2025/01/31 21:16:06 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "fractol.h"
#include "../minilibx/mlx.h"
#include <stdbool.h>

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

static void init_data(t_data *data)
{
	data->connection = NULL;
	data->window = NULL;
	data->image = NULL;
	data->addr = NULL;
	data->bits_per_pixel = 0;
	data->line_length = 0;
	data->endian = 0;
	data->set = NULL_SET;
	data->color = 0;
	data->zoom = 4;
	data->z.re = 0.0;
	data->z.im = 0.0;
	data->c.re = 0.0;
	data->c.im = 0.0;
	data->shift.re = WIDTH / 2.0;
	data->shift.im = HEIGHT / 2.0;
}

static void	init_set(t_data *data, int argc, char **argv)
{
	if (argc == 2)
	{
		if (strcomp(argv[1], "mandelbrot"))
			data->set = MANDELBROT;
		else if (strcomp(argv[1], "julia"))
		{
			data->set = JULIA;
			data->c.im = 0;
			data->c.re = 0;
		}
	}
	if (argc == 4 && (strcomp(argv[1], "julia")))
	{
		data->set = JULIA;
		data->c.re = atod(argv[2]);
		data->c.im = atod(argv[3]);
	}
}

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
	d->addr = mlx_get_data_addr(d->image, &(d->bits_per_pixel), &(d->line_length), &(d->endian));
}

int	main(int argc, char **argv) 
{
	t_data	data;
	
	init_data(&data);
	init_set(&data, argc, argv);
	if (data.set == NULL_SET)
		exit(1); // print usage
	mlx_setup(&data);
	render_image(&data);
	events_setup(&data);
	mlx_loop(data.connection);
	return (0);
}