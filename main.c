/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fokrober <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 05:58:04 by fokrober          #+#    #+#             */
/*   Updated: 2019/12/06 05:08:42 by fokrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define SIZE 2048
#include <unistd.h>
#include <stdlib.h>

/*
** To get a good visualization of how bf works
** https://fatiherikli.github.io/brainfuck-visualizer/#
*/

static char	*ft_goto(char *s)
{
	char	*res;

	while (*s && *s != ']')
	{
		if (*s == '[' && (res = ft_goto(s + 1)))
			s = res;
		s++;
	}
	return (s);
}

static char	*ft_goto2(char *start, char *s)
{
	char	*res;

	while (s != start && *s != '[')
	{
		if (*s == ']' && (res = ft_goto2(start, s - 1)))
			s = res;
		s--;
	}
	return (s);
}

static void	run(char *s)
{
	char	*ptr;
	char	*av;
	int		i;

	ptr = malloc(SIZE);
	i = -1;
	while (++i < SIZE)
		ptr[i] = 0;
	av = s;
	while (*av)
	{
		ptr += (*av == '>');
		ptr -= (*av == '<');
		*ptr += (*av == '+');
		*ptr -= (*av == '-');
		if (*av == '.')
			write(1, ptr, 1);
		else if (*av == '[' && !(*ptr))
			av = ft_goto(av + 1);
		if (*av == ']' && *ptr)
			av = ft_goto2(s, av - 1);
		else if (*av)
			av++;
	}
}

int			main(int ac, char **av)
{
	if (ac == 2)
		run(av[1]);
	else
		write(1, "\n", 1);
	return (0);
}
