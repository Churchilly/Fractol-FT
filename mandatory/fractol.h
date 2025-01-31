/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 02:13:01 by yusudemi          #+#    #+#             */
/*   Updated: 2025/01/31 03:25:23 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define NULL_SET 0
# define MANDELBROT 1
# define JULIA 2

# define WIDTH 600
# define HEIGHT 600

# define MAX_ITERATIONS 100
# define MIN_ITERATIONS 100

typedef struct	s_complex
{
	double	re;
	double	im;
}		t_complex;
#include <stdio.h>
typedef struct	s_data
{
	void	*connection;
	void	*window;
	void	*image;
	void	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int			set;
	int			color;
	int			max_iter;
	double		zoom;
	t_complex	z;
	t_complex	c;
	t_complex	shift;			
}			t_data;


double atod(char *str);
void	events_setup(t_data *d);
void	render_image(t_data *d);

#endif