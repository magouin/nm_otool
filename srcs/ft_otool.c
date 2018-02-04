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

size_t	ft_open(char *name, char *exec, int *fd)
{
	struct stat	buff;
	size_t		size;

	size = 0;
	*fd = open(name, O_RDONLY);
	if (*fd == -1)
		printf("%s: '%s': No such file or directory\n", exec, name);
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

int		ft_get_error(int error)
{
	if (error == 1)
		printf("Need a file\n");
	if (error == 2)
		printf("Failed to alloc size memory\n");
	return (1);
}

int		main(int ac, char **av)
{
	size_t					size;
	void					*bin;
	struct mach_header_64	head;
	int						fd;

	(void)ac;
	if (!(size = ft_open(av[1] ? av[1] : "a.out", av[0], &fd)))
		return (ft_get_error(1));
	if ((bin = mmap(0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0)) == 0)
		return (ft_get_error(2));
	head = *(struct mach_header_64 *)bin;
	if (head.magic == FAT_MAGIC_64 || head.magic == FAT_MAGIC || head.magic ==
		FAT_CIGAM || head.magic == FAT_CIGAM_64)
		return (fat_bin(bin, size, r_int32(((struct fat_header *)bin)->
			nfat_arch), av));
	else if ((head.magic == MH_MAGIC_64 || head.magic == MH_CIGAM_64) &&
		(printf("%s:\nContents of (__TEXT,__text) section\n", av[1]) || 1))
		return (ft_otool_64(bin, head, size, head.magic == MH_MAGIC_64 ?
			0 : 1));
	else if ((head.magic == MH_MAGIC || head.magic == MH_CIGAM) &&
		(printf("%s:\nContents of (__TEXT,__text) section\n", av[1]) || 1))
		return (ft_otool_32(bin, *(struct mach_header *)bin, size, head.
			magic == MH_MAGIC ? 0 : 1));
		printf("%s: is not an object file\n", av[1] ? av[1] : "a.out");
	return (1);
}
