/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat_bin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 08:44:39 by magouin           #+#    #+#             */
/*   Updated: 2018/02/03 08:44:41 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

int	call_macho_64(void *bin, size_t off_set2, size_t s, char **av)
{
	if (*(uint *)(bin + off_set2) == MH_MAGIC_64 || *(uint *)
		(bin + off_set2) == MH_CIGAM_64)
	{
		(*(struct mach_header_64 *)(bin + off_set2)).magic == MH_CIGAM_64 ?
		ft_printf("x86):\n") : ft_printf("x86_64):\n");
		macho_64(bin + off_set2, *(struct mach_header_64 *)(bin + off_set2),
			s, *(uint *)(bin + off_set2) == MH_MAGIC_64 ? 0 : 1);
	}
	else if (*(uint *)(bin + off_set2) == MH_MAGIC || *(uint *)(bin +
		off_set2) == MH_CIGAM)
	{
		(*(struct mach_header *)(bin + off_set2)).magic == MH_CIGAM ?
		ft_printf("ppc):\n") : ft_printf("i386):\n");
		macho_32(bin + off_set2, *(struct mach_header *)(bin + off_set2),
			s, *(uint *)(bin + off_set2) == MH_MAGIC ? 0 : 1);
	}
	else
	{
		ft_printf("%s: %s The file was not recognized as a valid ob\
ject file\n", av[1] ? av[1] : "a.out", av[0]);
		return (1);
	}
	return (0);
}

int	fat_64(void *bin, void *arch, size_t size, char **av)
{
	size_t				off_set2;
	struct fat_header	*head;
	size_t				s;

	head = bin;
	off_set2 = head->magic == FAT_CIGAM_64 ? r_int64((*(struct
fat_arch_64 *)arch).offset) : (*(struct fat_arch_64 *)arch).offset;
	if (off_set2 >= size)
	{
		ft_printf("Binary corrupted!\n");
		return (1);
	}
	s = head->magic == FAT_CIGAM ? r_int32((*(struct fat_arch *)arch).size)
	: (*(struct fat_arch *)arch).size;
	if (call_macho_64(bin, off_set2, s, av))
		return (1);
	return (0);
}

int	call_macho_32(void *bin, size_t off_set2, size_t s, char **av)
{
	if (*(uint *)(bin + off_set2) == MH_MAGIC_64 || *(uint *)(bin +
		off_set2) == MH_CIGAM_64)
	{
		(*(struct mach_header_64 *)(bin + off_set2)).magic ==
		MH_CIGAM_64 ? ft_printf("x86):\n") : ft_printf("x86_64):\n");
		if (macho_64(bin + off_set2, *(struct mach_header_64 *)(bin +
	off_set2), s, *(uint *)(bin + off_set2) == MH_MAGIC_64 ? 0 : 1))
			return (1);
	}
	else if (*(uint *)(bin + off_set2) == MH_MAGIC || *(uint *)(bin +
		off_set2) == MH_CIGAM)
	{
		(*(struct mach_header *)(bin + off_set2)).magic == MH_CIGAM ?
		ft_printf("ppc):\n") : ft_printf("i386):\n");
		if (macho_32(bin + off_set2, *(struct mach_header *)(bin +
	off_set2), s, *(uint *)(bin + off_set2) == MH_MAGIC ? 0 : 1))
			return (2);
	}
	else
	{
		ft_printf("%s: %s The file was not recognized as a valid objec\
t file\n", av[1] ? av[1] : "a.out", av[0]);
		return (3);
	}
	return (0);
}

int	fat_32(void *bin, void *arch, size_t size, char **av)
{
	size_t				off_set2;
	struct fat_header	*head;
	size_t				s;

	head = bin;
	off_set2 = head->magic == FAT_CIGAM ? r_int32((*(struct fat_arch *)
		arch).offset) : (*(struct fat_arch *)arch).offset;
	if (off_set2 >= size)
	{
		ft_printf("Binary corrupted!\n");
		return (1);
	}
	s = head->magic == FAT_CIGAM ? r_int32((*(struct fat_arch *)
		arch).size) : (*(struct fat_arch *)arch).size;
	if (call_macho_32(bin, off_set2, s, av))
		return (2);
	return (0);
}

int	fat_bin(void *bin, size_t size, int nb_arch, char **av)
{
	void				*arch;
	int					x;
	size_t				off_set;

	x = -1;
	off_set = sizeof(struct fat_header);
	while (++x < nb_arch)
	{
		ft_printf("\n%s (for architecture ", av[1]);
		arch = bin + off_set;
		if (*(uint *)bin == FAT_MAGIC_64 || *(uint *)bin == FAT_CIGAM_64)
		{
			if (fat_64(bin, arch, size, av))
				return (1);
		}
		else if (*(uint *)bin == FAT_MAGIC || *(uint *)bin == FAT_CIGAM)
			if (fat_32(bin, arch, size, av))
				return (1);
		off_set += *(uint *)bin == FAT_MAGIC_64 || *(uint *)bin == FAT_CIGAM_64
		? sizeof(struct fat_arch_64) : sizeof(struct fat_arch);
		off_set >= size ? ft_printf("Binary corrupted!\n") : 0;
		if (off_set >= size)
			return (1);
	}
	return (0);
}
