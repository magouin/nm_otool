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

void	get_sec_text(struct segment_command_64 *seg, uint32_t n,
	void *bin, size_t off_sec)
{
	size_t							x;
	struct section_64				section;
	uint32_t						sec;

	sec = 0;
	if (seg[n].nsects)
		while (sec < seg[n].nsects)
		{
			section = *(struct section_64*)(off_sec + bin);
			if (ft_strequ(section.sectname, "__text"))
			{
				x = section.offset - 1;
				printf("%016llx\t", section.addr + x + 1 - section.offset);
				while (++x - section.offset < section.size)
					(x - section.offset) % 16 == 15 && x - section.offset + 1 <
section.size ? printf("%02x \n%016llx\t", *(unsigned char *)(bin + x), section.
addr + x + 1 - section.offset) : printf("%02x ", *(unsigned char *)(bin + x));
				printf("\n");
			}
			off_sec += sizeof(section);
			sec++;
		}
}

void	ft_otool(void *bin, struct mach_header_64 head)
{
	uint32_t						n;
	size_t							off_set;
	size_t							off_sec;
	struct segment_command_64		seg[head.ncmds];

	n = 0;
	off_set = sizeof(struct mach_header_64);
	while (n < head.ncmds)
	{
		if ((*(struct segment_command_64 *)(bin + off_set)).
			cmd == LC_SEGMENT_64)
		{
			seg[n] = *(struct segment_command_64 *)(bin + off_set);
			off_sec = sizeof(struct segment_command_64) + off_set;
			get_sec_text(seg, n, bin, off_sec);
		}
		off_set += (*(struct segment_command_64 *)(bin + off_set)).cmdsize;
		n++;
	}
}

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

	if (ac != 2)
		return (ft_get_error(1));
	if (!(size = ft_open(av[1] ? av[1] : "a.out", av[0], &fd)))
		return (1);
	if ((bin = mmap(0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0)) == 0)
		return (ft_get_error(2));
	head = *(struct mach_header_64 *)bin;
	if (head.magic != MH_MAGIC_64 && head.magic != MH_CIGAM_64)
	{
		printf("%s: is not an object file\n", av[1] ? av[1] : "a.out");
		return (3);
	}
	printf("%s:\nContents of (__TEXT,__text) section\n", av[1]);
	ft_otool(bin, head);
	return (0);
}
