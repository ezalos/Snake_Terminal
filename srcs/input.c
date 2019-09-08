/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 12:15:02 by ezalos            #+#    #+#             */
/*   Updated: 2019/09/08 21:35:51 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"
#include <sys/select.h>
#include <curses.h>
#include <unistd.h>
#include <termios.h>


int 	get_input(t_snake *snake)
{
	char *buffer;
	int	r_v;

	// int nfds = 1;
	// fd_set readfds;
	// // fd_set writefds;
	// // fd_set errorfds;
	// struct timeval timeout;
	// timeout.tv_sec = 1;
	// timeout.tv_usec = REFRESH_TIME;
	// FD_ZERO(&readfds);
	// FD_SET(0, &readfds);



	ft_printf("%s\n", __func__);
	struct termios old = {0};
	if (tcgetattr(0, &old) < 0)
			perror("tcsetattr()");
	old.c_lflag &= ~ICANON;
	old.c_lflag &= ~ECHO;
	old.c_cc[VMIN] = 0;
	old.c_cc[VTIME] = 1;
	if (tcsetattr(0, TCSANOW, &old) < 0)
			perror("tcsetattr ICANON");

	// if (0 <= (r_v = select(nfds, &readfds, NULL, NULL, &timeout)) && ft_printf("%~{?}SELECT: %d\n", r_v))
	// 	return (r_v);
	// ft_printf("%~{?}GOOLECT: %d\n", r_v);
	if ((r_v = get_next_line(0, &buffer)) < 0)
		perror ("read()");

	old.c_lflag |= ICANON;
	old.c_lflag |= ECHO;
	if (tcsetattr(0, TCSADRAIN, &old) < 0)
	perror ("tcsetattr ~ICANON");
	if (r_v <= 0)
		return (r_v);


	if (!ft_strncmp(buffer, S_UP, 3))//UP
	{
		// ft_printf("UP\n");
		if (snake->dir_row != 1 || snake->row_history[0] == 1)
			snake->dir_row = -1;
		snake->dir_col = 0;
	}
	else if (!ft_strncmp(buffer, S_DOWN, 3))//DOWN
	{
		// ft_printf("DOWN\n");
		if (snake->dir_row != -1 || snake->row_history[0] == 1)
			snake->dir_row = 1;
		snake->dir_col = 0;
	}
	else if (!ft_strncmp(buffer, S_RIGHT, 3))//RIGHT
	{
		// ft_printf("RIGHT\n");
		snake->dir_row = 0;
		if (snake->dir_col != -1 || snake->row_history[0] == 1)
			snake->dir_col = 1;
	}
	else if (!ft_strncmp(buffer, S_LEFT, 3))//LEFT
	{
		// ft_printf("LEFT\n");
		snake->dir_row = 0;
		if (snake->dir_col != 1 || snake->row_history[0] == 1)
			snake->dir_col = -1;
	}
	else if (!ft_strncmp(buffer, "0", 1))
	{
		r_v = 5;
		while (r_v--)
		{
			calculate_head_pos(snake);
			snake->board[snake->food.row][snake->food.col] == BODY;
			snake_grow(snake, snake->first.row, snake->first.col);
		}
	}
	else if (!ft_strncmp(buffer, "9", 1))
	{
		print_it(snake);
	}
	return (r_v);
}
