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
#include "time.h"

int	main(void)
{
	clock_t	start, end;
	double	cpu_time_used;
	char	short_lines_file[] = "short_lines_file.txt";
	char	*res_str;
	int		fd;

	start = clock();
	
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
	
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("\n\nTime taken: %f seconds\n\n\n", cpu_time_used);
	
	return (1);
}
