/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 05:23:08 by yusudemi          #+#    #+#             */
/*   Updated: 2025/02/03 19:31:07 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <math.h>

static t_complex	square_complex(t_complex c) // helper 
{
	// (a + bi)^2 = a^2 - b^2 + 2abi
	t_complex	res;
	res.re = pow(c.re, 2) - pow(c.im, 2);
	res.im = 2 * c.re * c.im;
	return (res);
}

static t_complex	sum_complex(t_complex c1, t_complex c2) //helper
{
	t_complex	res;

	res.im = c1.im + c2.im;
	res.re = c1.re + c2.re;
	return (res);
}

int render_mandelbrot(int x, int y, t_data *d)
{
	int	i;
	int	t;
	int sqrt_mag;
	
	d->z.re = 0.0;
	d->z.im = 0.0;
	d->c.re = (d->min.re + (x * (d->max.re - d->min.re) / WIDTH) + d->shift.re);
	d->c.im = (d->min.im + (y * (d->max.im - d->min.im) / HEIGHT)  + d->shift.im);
	sqrt_mag = 0;
	i = -1;
	while (sqrt_mag < (4.0) && ++i < d->max_iter)
	{
		d->z = sum_complex(square_complex(d->z), d->c);
		sqrt_mag = (pow(d->z.re, 2) + pow(d->z.im, 2));
	}
	if (i < d->max_iter)
	{
		t = log(log(sqrt_mag) / 2.0) / log(2.0) / log(2.0);
		i = i + 1 - t;
	}
	return (i);
}

int	render_julia(int x, int y, t_data *d)
{
	int i;
	double	t;
	double	sqrt_mag;
	
	d->c.re = d->min.re + (x * (d->max.re - d->min.re) / WIDTH);
	d->c.im = d->min.im + (y * (d->max.im - d->min.im) / HEIGHT);
	i = -1;
	while (sqrt_mag < (d->max.re * d->max.im) && ++i < d->max_iter)
	{
		d->z = sum_complex(square_complex(d->z), d->c);
		sqrt_mag = (pow(d->z.re, 2) + pow(d->z.im, 2));
	}
	if (i < d->max_iter)
	{
		t = log(log(sqrt_mag) / (log(2.0) * log(2.0)));
		i = (double)i + 1 - t;
	}
	return (i);
}

int render_burningship(int x, int y, t_data *d)
{
	(void)x;
	(void)y;
	(void)d;
	return (0);
}
