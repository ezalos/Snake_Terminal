/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 12:27:19 by root              #+#    #+#             */
/*   Updated: 2019/07/14 21:56:10 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

void 		new_food(t_snake *snake)
{
	// snake->board[snake->food.row][snake->food.col] = FOOD;
	snake->food.row = ft_rand(snake->rows, 0);
	snake->food.col = ft_rand(snake->cols, 0);
	snake->board[snake->food.row][snake->food.col] = FOOD;
}

void		add_move(t_snake *snake, int row, int col)
{
	snake->col_history[++snake->col_history[0]] = col;
	snake->row_history[++snake->row_history[0]] = row;
}
void		new_move(t_snake *snake, int row, int col)
{
	int i;

	i = 0;
	while (++i < snake->col_history[0] - 1)
		snake->col_history[i] = snake->col_history[i + 1];
	snake->col_history[i] = col;
	i = 0;
	while (++i < snake->row_history[0] - 1)
		snake->row_history[i] = snake->row_history[i + 1];
	snake->row_history[i] = col;
}

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
			snake->rows = w.ws_row;
			snake->cols = w.ws_col;
		}
		ft_printf ("columns %d\n", snake->cols);
		ft_printf ("rows %d\n", snake->rows);
		snake->board = ft_memalloc(snake->rows);
		i = -1;
		while (++i < snake->rows)
			snake->board[i] = ft_memalloc(snake->cols);
		snake->first.row = ft_rand(snake->rows, 0);
		snake->first.col = ft_rand(snake->cols, 0);
		ft_printf("Snake: [%d][%d]\n", snake->first.row, snake->first.col);
		snake->board[snake->first.row][snake->first.col] = BODY;
		snake->col_history = ft_memalloc(sizeof(int) * snake->rows * snake->cols);
		snake->row_history = ft_memalloc(sizeof(int) * snake->rows * snake->cols);
		add_move(snake, snake->first.row, snake->first.col);
		new_food(snake);
		ft_printf("Init complete\n");
		return (snake);
}

void 	print_it(t_snake *snake)
{
	int		last_color;
	int		row;
	int		col;

	_C_RESET;
	last_color = EMPTY;
	row = -1;
	while (++row < snake->rows)
	{
		col = -1;
		while (++col < snake->cols)
		{
			if (snake->board[row][col] == BODY && last_color != BODY)
				ft_rgb_bcolor(255, 255, 255);
			else if (snake->board[row][col] == FOOD && last_color != FOOD)
				ft_rgb_bcolor(0, 255, 0);
			else if (snake->board[row][col] == EMPTY && last_color != EMPTY)
				_C_RESET;
			write(1, " ", 1);
			last_color = snake->board[row][col];
		}
		write(1, "\n", 1);
	}
	_C_RESET;
	ft_printf("print complete\n");
}

int 	big_loop(t_snake *snake)
{
	int end;
	char buffer[7];
	int	r_v;

	snake->dir_row = 1;
	end = 0;
	while (!end)
	{
		ft_bzero(buffer, 4);
		r_v = read(0, buffer, 4);
		ft_printf("%.r%s", buffer);
		ft_printf("\n");
		ft_printf("%.r%s", S_UP);
		ft_printf("\nBuf_len: %d\n", r_v);
		if (!ft_strncmp(buffer, S_UP, 3))//UP
		{
			ft_printf("UP\n");
			snake->dir_row = -1;
			snake->dir_col = 0;
		}
		else if (!ft_strncmp(buffer, S_DOWN, 3))//DOWN
		{
			ft_printf("DOWN\n");
			snake->dir_row = 1;
			snake->dir_col = 0;
		}
		else if (!ft_strncmp(buffer, S_RIGHT, 3))//RIGHT
		{
			ft_printf("RIGHT\n");
			snake->dir_row = 0;
			snake->dir_col = 1;
		}
		else if (!ft_strncmp(buffer, S_LEFT, 3))//LEFT
		{
			ft_printf("LEFT\n");
			snake->dir_row = 0;
			snake->dir_col = -1;
		}
		snake->first.col += snake->dir_col;
		snake->first.row += snake->dir_row;
		if (snake->board[snake->first.row][snake->first.col] == BODY)
			end = 1;
		if ( (snake->first.col != snake->food.col
		&&    snake->first.row != snake->food.row))
		{
			snake->board[snake->row_history[1]][snake->col_history[1]] == EMPTY;
			new_move(snake, snake->first.row, snake->first.col);
		}
		else
		{
			snake->board[snake->food.row][snake->food.col] == BODY;
			add_move(snake, snake->first.row, snake->first.col);
			new_food(snake);
		}
		snake->board[snake->first.row][snake->first.col] = BODY;
		print_it(snake);
		ft_wait_pls(0);
	}
}

int		main(int ac, char **av)
{
	t_snake					*snake;

	snake = init(ac, av);
	(void)snake;
	print_it(snake);
	big_loop(snake);
	// ft_clean_garbage();
	return (0);
}
