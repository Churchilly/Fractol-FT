/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sets_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 05:23:08 by yusudemi          #+#    #+#             */
/*   Updated: 2025/02/06 00:29:54 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"
#include <math.h>

static t_complex	square_complex(t_complex c)
{
	t_complex	res;

	res.re = pow(c.re, 2) - pow(c.im, 2);
	res.im = 2 * c.re * c.im;
	return (res);
}

static t_complex	sum_complex(t_complex c1, t_complex c2)
{
	t_complex	res;

	res.im = c1.im + c2.im;
	res.re = c1.re + c2.re;
	return (res);
}

double	render_mandelbrot(int x, int y, t_data *d)
{
	int		i;
	double	mu;
	double	sqrt_mag;

	d->z.re = 0.0;
	d->z.im = 0.0;
	d->c.re = d->min.re + (x * (d->max.re - d->min.re) / WIDTH) + d->shift.re;
	d->c.im = d->min.im + (y * (d->max.im - d->min.im) / HEIGHT) + d->shift.im;
	sqrt_mag = 0;
	i = -1;
	while (sqrt_mag < (4.0) && ++i < d->max_iter)
	{
		d->z = sum_complex(square_complex(d->z), d->c);
		sqrt_mag = (pow(d->z.re, 2) + pow(d->z.im, 2));
	}
	if (i < d->max_iter)
	{
		mu = log(log(fabs(sqrt_mag))) / log(4.0);
		mu = i + 1 - mu;
	}
	return (mu);
}

double	render_julia(int x, int y, t_data *d)
{
	int		i;
	double	mu;
	double	sqrt_mag;

	d->z.re = d->min.re + (x * (d->max.re - d->min.re) / WIDTH) + d->shift.re;
	d->z.im = d->min.im + (y * (d->max.im - d->min.im) / HEIGHT) + d->shift.im;
	sqrt_mag = 0;
	i = -1;
	while (sqrt_mag < (4.0) && ++i < d->max_iter)
	{
		d->z = sum_complex(square_complex(d->z), d->c);
		sqrt_mag = (pow(d->z.re, 2) + pow(d->z.im, 2));
	}
	if (i < d->max_iter)
	{
		mu = log(log(fabs(sqrt_mag)) / 2.0) / log(2.0);
		mu = (double)i + 1 - mu;
	}
	return (mu);
}

double	render_tricorn(int x, int y, t_data *d)
{
	int		i;
	double	sqrt_mag;
	double	mu;

	d->c.re = d->min.re + (x * (d->max.re - d->min.re) / WIDTH) + d->shift.re;
	d->c.im = d->min.im + (y * (d->max.im - d->min.im) / HEIGHT) + d->shift.im;
	d->z.re = 0;
	d->z.im = 0;
	i = -1;
	sqrt_mag = 0;
	while (sqrt_mag < 4.0 && ++i < d->max_iter)
	{
		d->z.re = d->z.re;
		d->z.im = d->z.im * -1.0;
		d->z = sum_complex(square_complex(d->z), d->c);
		sqrt_mag = pow(d->z.re, 2) + pow(d->z.im, 2);
	}
	if (i < d->max_iter)
	{
		mu = log(log(fabs(sqrt_mag)) / 2.0) / log(2.0);
		mu = (double)i + 1 - mu;
	}
	return (mu);
}
