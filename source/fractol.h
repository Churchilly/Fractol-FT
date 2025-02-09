/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 02:13:01 by yusudemi          #+#    #+#             */
/*   Updated: 2025/02/10 02:28:35 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_BONUS_H
# define FRACTOL_BONUS_H

# define NULL_SET 0
# define MANDELBROT 1
# define JULIA 2
# define TRICORN 3

# define WIDTH 800
# define HEIGHT 800

# define DEFAULT_ITERATIONS 35
# define DEFAULT_THREADS 8
# include <stdio.h>
# include <unistd.h>
typedef struct s_complex
{
	double	re;
	double	im;
}		t_complex;

typedef struct s_data
{
	void		*connection;
	void		*window;
	void		*image;
	void		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			set;
	int			max_iter;
	double		zoom;
	t_complex	z;
	t_complex	c;
	t_complex	min;
	t_complex	max;
	t_complex	shift;
}			t_data;

typedef struct s_threads_data
{
	int	start_y;
	int	end_y;
	t_data	d;
}		t_threads_data;

void		init_data(t_data *data);
void		init_set(t_data *data, int argc, char **argv);
int			strcomp(char *str1, char *str2);
double		atod(char *str);
void		events_setup(t_data *d);
void		render_image(t_data *d);
double		render_mandelbrot(int x, int y, t_data *d);
double		render_julia(int x, int y, t_data *d);
double		render_tricorn(int x, int y, t_data *d);

#endif