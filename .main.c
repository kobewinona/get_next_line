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
	// char *res_str;

    // printf("Please enter a line:\n");
    // res_str = get_next_line(0); // Reading from stdin

    // if (res_str)
    // {
    //     printf("You entered: |>%s<|\n\n", res_str);
    //     free(res_str);
    // }
    // else
    // {
    //     printf("No line was read or an error occurred.\n\n");
    // }
	
	
	char	short_lines_file[] = "short_lines_file.txt";
	// char	*no_file;
	char	*res_str;
	char	empty_file[] = "empty_file.txt";
	int		fd;
	
	// no_file = NULL;

	fd = open(short_lines_file, O_RDONLY);
	res_str = get_next_line(fd);
	printf("returned: |>%s<|\n\n", res_str);
	free(res_str);
	close(fd);
	
	res_str = get_next_line(fd);
	printf("returned: |>%s<|\n\n", res_str);
	free(res_str);
	
	fd = open(short_lines_file, O_RDONLY);
	res_str = get_next_line(fd);
	printf("returned: |>%s<|\n\n", res_str);
	free(res_str);
	
	res_str = get_next_line(fd);
	printf("returned: |>%s<|\n\n", res_str);
	free(res_str);
	
	res_str = get_next_line(-1);
	printf("returned: |>%s<|\n\n", res_str);
	free(res_str);
	
	res_str = get_next_line(-1);
	printf("returned: |>%s<|\n\n", res_str);
	free(res_str);
	
	res_str = get_next_line(fd);
	printf("returned: |>%s<|\n\n", res_str);
	free(res_str);
	
	res_str = get_next_line(fd);
	printf("returned: |>%s<|\n\n", res_str);
	free(res_str);
	
	res_str = get_next_line(fd);
	printf("returned: |>%s<|\n\n", res_str);
	free(res_str);
	
	res_str = get_next_line(fd);
	printf("returned: |>%s<|\n\n", res_str);
	free(res_str);
	
	res_str = get_next_line(fd);
	printf("returned: |>%s<|\n\n", res_str);
	free(res_str);
	
	res_str = get_next_line(fd);
	printf("returned: |>%s<|\n\n", res_str);
	free(res_str);
	
	res_str = get_next_line(fd);
	printf("returned: |>%s<|\n\n", res_str);
	free(res_str);
	
	res_str = get_next_line(fd);
	printf("returned: |>%s<|\n\n", res_str);
	free(res_str);
	
	return (1);
}
