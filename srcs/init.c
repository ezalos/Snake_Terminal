/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 12:01:39 by ezalos            #+#    #+#             */
/*   Updated: 2019/09/08 21:32:34 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

t_snake		*init(int ac, char **av)
{
		t_snake					*snake;
		struct winsize	w;
		int							i;

		snake = ft_memalloc(sizeof(t_snake));
		if (ac == 3)
		{
			snake->rows = ft_atoi(av[1]);
			snake->cols = ft_atoi(av[2]);
		}
		else
		{
		  ioctl(0, TIOCGWINSZ, &w);
			snake->rows = w.ws_row - 0;
			snake->cols = w.ws_col;
		}
		ft_printf ("columns %d\n", snake->cols);
		ft_printf ("rows %d\n", snake->rows);
		snake->board = ft_memalloc(snake->rows + 1);
		i = -1;
		while (++i < snake->rows)
			snake->board[i] = ft_memalloc(snake->cols + 1);
		snake->first.row = ft_rand(snake->rows, 0);
		snake->first.col = ft_rand(snake->cols, 0);
		ft_printf("Snake: [%d][%d]\n", snake->first.row, snake->first.col);
		snake->col_history = ft_memalloc(sizeof(int) * snake->rows * (snake->cols + 1));
		snake->row_history = ft_memalloc(sizeof(int) * snake->rows * (snake->cols + 1));
		snake_grow(snake, snake->first.row, snake->first.col);
		new_food(snake);
		ft_printf("Init complete\n");
		return (snake);
}
