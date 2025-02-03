/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 04:27:40 by yusudemi          #+#    #+#             */
/*   Updated: 2025/02/02 10:09:33 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <unistd.h>
#include <stdlib.h>

void init_data(t_data *data)
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
	data->max_iter = 0;
	data->z.re = 0.0;
	data->z.im = 0.0;
	data->c.re = 0.0;
	data->c.im = 0.0;
	data->min.re = 0.0;
	data->min.im = 0.0;
	data->max.re = 0.0;
	data->max.im = 0.0;
	data->shift.re = 0;
	data->shift.im = 0;
	data->mouse.re = 0.0;
	data->mouse.im = 0.0;
}

static void	init_mandelbrot(t_data *d)
{
	d->set = MANDELBROT;
	d->max_iter = 40;
	d->max.re = 2.0;
	d->min.re = -2.0;
	d->max.im = 2.0;
	d->min.im = -2.0;
	d->shift.re = 0.0;
	d->shift.im = 0.0;
}

static void	init_burningship(t_data *d)
{
	d->set = BURNINGSHIP;
	d->max.re = 1.5;
	d->min.re = -2.5;
	d->max.im = 2.5;
	d->min.im = -1.5;
	d->shift.re = WIDTH / 2.0;
	d->shift.im = HEIGHT / 2.0;
}

static void	init_julia(t_data *d, double julia_re, double julia_im)
{
	d->set = JULIA;
	d->max.re = 2.0;
	d->min.re = -2.0;
	d->max.im = 2.0;
	d->min.im = -2.0;
	d->shift.re = WIDTH / 2.0;
	d->shift.im = HEIGHT / 2.0;
	if (julia_re > d->max.re || julia_re < d->min.re
		|| julia_im > d->max.im || julia_im < d->min.im)
	{
		write(2, "Error: Julia parameters out of range\n", 38);
		exit(1);
	}
	d->c.re = julia_re;
	d->c.im = julia_im;
}

void	init_set(t_data *data, int argc, char **argv)
{
	if (argc == 2)
	{
		if (strcomp(argv[1], "mandelbrot"))
			init_mandelbrot(data);
		else if (strcomp(argv[1], "julia"))
			init_julia(data, 0, 0);
		else if (strcomp(argv[1], "burningship"))
			init_burningship(data);
		return ;
	}
	if (argc == 4 && (strcomp(argv[1], "julia")))
	{	
		init_julia(data, atod(argv[2]), atod(argv[3]));
		return ;
	}
	write(1, "Usage: ./fractol Fractal-Set\n", 30);
	write(1, "                 mandelbrot\n", 29);
	write(1, "                 julia <real> <imaginary>\n", 43);
	exit(1);
}
