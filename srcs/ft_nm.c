/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 14:05:47 by magouin           #+#    #+#             */
/*   Updated: 2018/01/29 14:06:07 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

struct s_tab	get_smallest(struct s_tab *tab, int *tabi)
{
	int					x;
	struct s_tab		rez;
	int					index;

	rez = (struct s_tab){0, NULL, 0};
	x = 0;
	index = 0;
	while (tab[x].str)
	{
		if (!tabi[x] && (!rez.str || ft_strcmp(rez.str, tab[x].str) > 0 ||
			(!ft_strcmp(rez.str, tab[x].str) && tab[x].value < rez.value)))
		{
			rez = tab[x];
			index = x;
		}
		x++;
	}
	tabi[index] = 1;
	return (rez);
}

size_t			ft_open(char *name, char *exec, int *fd)
{
	struct stat	buff;
	size_t		size;

	size = 0;
	*fd = open(name, O_RDONLY);
	if (*fd == -1)
		printf("%s: %s: No such file or directory\n", exec, name);
	if (fstat(*fd, &buff) != -1)
	{
		size = buff.st_size;
		if (buff.st_mode & S_IFDIR)
		{
			printf("%s: %s: Is a directory.\n", exec, name);
			size = 0;
		}
	}
	return (size);
}

int				main(int ac, char **av)
{
	size_t					size;
	void					*bin;
	struct mach_header_64	head;
	int						fd;

	(void)ac;
	if (!(size = ft_open(av[1] ? av[1] : "a.out", av[0], &fd)))
		return (1);
	if ((bin = mmap(0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0)) == 0)
		return (2);
	head = *(struct mach_header_64 *)bin;
	if (head.magic == FAT_MAGIC_64 || head.magic == FAT_MAGIC || head.magic ==
		FAT_CIGAM || head.magic == FAT_CIGAM_64)
		return (fat_bin(bin, size, r_int32(((struct fat_header *)bin)->
			nfat_arch), av));
	else if (head.magic == MH_MAGIC_64 || head.magic == MH_CIGAM_64)
		return (macho_64(bin, head, size, head.magic == MH_MAGIC_64 ? 0 : 1));
	else if (head.magic == MH_MAGIC || head.magic == MH_CIGAM)
		return (macho_32(bin, *(struct mach_header *)bin, size, head.
			magic == MH_MAGIC ? 0 : 1));
		printf("%s: %s The file was not recognized as a valid objec\
		t file\n", av[1] ? av[1] : "a.out", av[0]);
	return (3);
}
