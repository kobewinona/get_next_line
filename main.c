/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 13:13:34 by dklimkin          #+#    #+#             */
/*   Updated: 2023/09/26 13:13:35 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	main(void)
{
	int	fd;

	fd = open("test_file.txt", O_RDONLY);
	if (fd < 0)
		printf("error\n");
	printf("returned: |>%s<|\n\n", get_next_line(fd));
	printf("returned: |>%s<|\n\n", get_next_line(fd));
	printf("returned: |>%s<|\n\n", get_next_line(fd));
	printf("returned: |>%s<|\n\n", get_next_line(fd));
	printf("returned: |>%s<|\n\n", get_next_line(fd));
	printf("returned: |>%s<|\n\n", get_next_line(fd));
	printf("returned: |>%s<|\n\n", get_next_line(fd));
	printf("returned: |>%s<|\n\n", get_next_line(fd));
	printf("returned: |>%s<|\n\n", get_next_line(fd));
	printf("returned: |>%s<|\n\n", get_next_line(fd));
	printf("returned: |>%s<|\n\n", get_next_line(fd));
	printf("returned: |>%s<|\n\n", get_next_line(fd));
	printf("returned: |>%s<|\n\n", get_next_line(fd));
	return (1);
}
