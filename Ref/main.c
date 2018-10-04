/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncollie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 20:22:03 by ncollie           #+#    #+#             */
/*   Updated: 2018/09/22 15:42:43 by ncollie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pheader.h"
#include "lheader.h"

void zeroflags(int *flag)
{
	flag[0] = 0; //l
	flag[1] = 0; //a
	flag[2] = 0; //t
	flag[3] = 0; //r
	flag[4] = 1; //finished flags
	flag[5] = 0; //for space in run
	flag[6] = 0; //for /n in run
}

void flags(int *flag, char *s)
{
	while (*s)
	{
		if (*s == 'l')
			flag[0] = 1;
		else if (*s == 'a')
			flag[1] = 1;
		else if (*s == 't')
			flag[2] = 1;
		else if (*s == 'r')
			flag[3] = 1;
		s++;
	}
}

void fillstat(char *path, struct dirent current, struct stat *stats)
{

	int count;
	char *temp;

	count = ft_strlen(path) + 1 + current.d_namlen;
	if ((temp = malloc(sizeof(char) * count)) == NULL)
		return;
	temp = ft_strcpy(temp, path);
	temp[ft_strlen(path)] = '/';
	ft_strcpy((temp + (ft_strlen(path) + 1)), current.d_name);
	lstat(temp, stats);
	free(temp);
	temp = NULL;
}

void walk(char *s, int *flag)
{
	DIR *dir;
	struct dirent *current;
	struct stat stats;
	t_data **nodes;
	long long total;

	total = 0;
	nodes = t_datamaker();
	if (!(dir = opendir(s)))
		return;
	while ((current = readdir(dir)) != 0)
	{
		fillstat(s, *current, &stats);
		nodes[1] = create_dir_node(current->d_name, &stats);
		if (flag[1])
			link_me(&(nodes[0]), nodes[1], &(nodes[2]), flag[2]) && (total += stats.st_blocks);
		else if (!(((current->d_name)[0]) == '.'))
			link_me(&(nodes[0]), nodes[1], &(nodes[2]), flag[2]) && (total += stats.st_blocks);
	}
	print_me(nodes[0], nodes[2], flag, total);
	closedir(dir);
}

int main(int argc, char **argv)
{
	int flag[7];
	struct stat stats;
	t_data ***big_papa;
	t_data *new_node;

	big_papa = t_datafinal();
	zeroflags(flag);
	if (argc == 1)
		walk(".", flag);
	else
	{
		while (--argc > 0)
		{
			if (**++argv == '-' && flag[4])
				flags(flag, *argv);
			else //everything after this point should be a file or directory
			{
				(flag[4]) ? flag[4] = 0 : flag[4];
				new_node = create_dir_node(*argv, (lstat(*argv, &stats) == -1) ? 0 : &stats);
				if (lstat(*argv, &stats) == -1)
					link_me(&(big_papa[0][0]), new_node, &(big_papa[0][1]), 0);
				else if (!S_ISDIR(stats.st_mode))
					link_me(&(big_papa[1][0]), new_node, &(big_papa[1][1]), flag[2]); //return pointer array -- all file/nonfile will be handled before. remove those files after done ... then pass linked list wtih only real dirs in it to walk
				else
					link_me(&(big_papa[2][0]), new_node, &(big_papa[2][1]), flag[2]);
			}
		}
		print_junk(big_papa[0][0], flag);				   //HAVE TO SET HEAD TO NULL FIRST
		print_me(big_papa[1][0], big_papa[1][1], flag, 0); //, nodes_dir[0]);
		run(big_papa[2], flag);
		if (flag[4])
			walk(".", flag);
	}
	return (0);
}