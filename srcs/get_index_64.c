/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_index_64.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 11:09:42 by magouin           #+#    #+#             */
/*   Updated: 2018/02/03 11:09:43 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

int				verif_offset(size_t offset, size_t size_file)
{
	if (offset >= size_file)
	{
		ft_printf("Binary corrupted!\n");
		return (1);
	}
	return (0);
}

static int		get_nb_sec(int ncmds, int end, size_t size_file, void *bin)
{
	size_t						off_set;
	struct load_command			cmd;
	struct segment_command_64	seg;
	int							nb_sec;
	int							n;

	nb_sec = 0;
	off_set = sizeof(struct mach_header_64);
	n = -1;
	cmd = *(struct load_command *)(bin);
	while (++n < ncmds)
	{
		cmd = *(struct load_command *)(bin + off_set);
		cmd.cmd = !end ? cmd.cmd : r_int32(cmd.cmd);
		if (cmd.cmd == LC_SEGMENT_64)
		{
			seg = *(struct segment_command_64 *)(bin + off_set);
			seg.nsects = !end ? seg.nsects : r_int32(seg.nsects);
			nb_sec += seg.nsects;
		}
		cmd.cmdsize = !end ? cmd.cmdsize : r_int32(cmd.cmdsize);
		if (verif_offset(off_set += cmd.cmdsize, size_file))
			return (-1);
	}
	return (nb_sec);
}

static int		write_rez(char *rez, struct s_norm n, struct segment_command_64
	seg, size_t size_file)
{
	uint32_t					nb;
	struct section_64			sec;

	nb = 0;
	while (nb < seg.nsects)
	{
		sec = *(struct section_64 *)(n.bin + *n.off_set);
		if (verif_offset(*n.off_set, size_file))
			return (-1);
		if (ft_strequ(sec.sectname, "__data"))
			rez[n.end] = 'D';
		else if (ft_strequ(sec.sectname, "__text"))
			rez[n.end] = 'T';
		else if (ft_strequ(sec.sectname, "__bss"))
			rez[n.end] = 'B';
		else
			rez[n.end] = 'S';
		n.end++;
		*n.off_set += sizeof(sec);
		nb++;
	}
	return (n.end);
}

static int		segment_64(struct s_norm2 n, size_t size_file)
{
	struct segment_command_64	seg;
	int							tmp;

	seg = *((struct segment_command_64 *)(n.bin + n.off_set));
	seg.nsects = !n.end ? seg.nsects : r_int32(seg.nsects);
	if (verif_offset((*n.off_sec = n.off_set + sizeof(struct segment_command_64)), size_file))
		return (-1);
	if ((tmp = write_rez(n.rez, (struct s_norm){*n.nb_sec, n.off_sec, n.bin},
		seg, n.size_file)) == -1)
		return (1);
	*n.nb_sec = tmp;
	return (0);
}

char			*get_index_64(int ncmds, int end, size_t size_file, void *bin)
{
	size_t						off_set;
	size_t						off_sec;
	struct load_command			cmd;
	char						*rez;
	int							nb_sec;

	nb_sec = 0;
	rez = malloc(get_nb_sec(ncmds, end, size_file, bin));
	if (rez == NULL)
		return (rez);
	off_set = sizeof(struct mach_header_64);
	while (0 < ncmds--)
	{
		cmd = *(struct load_command *)(bin + off_set);
		cmd.cmdsize = !end ? cmd.cmdsize : r_int32(cmd.cmdsize);
		cmd.cmd = !end ? cmd.cmd : r_int32(cmd.cmd);
		if (cmd.cmd == LC_SEGMENT_64)
			if (segment_64((struct s_norm2){bin, off_set, &nb_sec,
				end, &off_sec, rez, size_file}, size_file))
				return (NULL);
		off_set += cmd.cmdsize;
		if (verif_offset(off_set, size_file))
			return (NULL);
	}
	return (rez);
}
