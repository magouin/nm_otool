/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_index_32.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 11:09:36 by magouin           #+#    #+#             */
/*   Updated: 2018/02/03 11:09:38 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

static int		get_nb_sec(int ncmds, int end, size_t size_file, void *bin)
{
	size_t					off_set;
	int						nb_sec;
	struct load_command		cmd;
	struct segment_command	seg;

	nb_sec = 0;
	off_set = sizeof(struct mach_header);
	cmd = *(struct load_command *)(bin);
	while (ncmds--)
	{
		cmd = *(struct load_command *)(bin + off_set);
		cmd.cmd = !end ? cmd.cmd : r_int32(cmd.cmd);
		if (cmd.cmd == LC_SEGMENT)
		{
			seg = *(struct segment_command *)(bin + off_set);
			seg.nsects = !end ? seg.nsects : r_int32(seg.nsects);
			nb_sec += seg.nsects;
		}
		cmd.cmdsize = !end ? cmd.cmdsize : r_int32(cmd.cmdsize);
		if (verif_offset(off_set += cmd.cmdsize, size_file))
			return (-1);
	}
	return (nb_sec);
}

static int		write_rez(char *rez, struct s_norm n, struct segment_command
	seg, size_t size_file)
{
	uint32_t				nb;
	struct section			sec;

	nb = 0;
	while (nb < seg.nsects)
	{
		sec = *(struct section *)(n.bin + *n.off_set);
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

static int		segment_32(struct s_norm2 n, size_t size_file)
{
	struct segment_command	seg;
	int						tmp;

	seg = *((struct segment_command *)(n.bin + n.off_set));
	seg.nsects = !n.end ? seg.nsects : r_int32(seg.nsects);
	if (verif_offset((*n.off_sec = n.off_set + sizeof(struct segment_command)), size_file))
		return (1);
	if ((tmp = write_rez(n.rez, (struct s_norm){*n.nb_sec, n.off_sec, n.bin},
		seg, n.size_file)) == -1)
		return (1);
	*n.nb_sec = tmp;
	return (0);
}

char			*get_index_32(int ncmds, int end, size_t size_file, void *bin)
{
	size_t					off_set;
	size_t					off_sec;
	int						nb_sec;
	struct load_command		cmd;
	char					*rez;

	nb_sec = 0;
	rez = malloc(get_nb_sec(ncmds, end, size_file, bin));
	if (rez == NULL)
		return (rez);
	off_set = sizeof(struct mach_header);
	while (ncmds--)
	{
		cmd = *(struct load_command *)(bin + off_set);
		cmd.cmdsize = !end ? cmd.cmdsize : r_int32(cmd.cmdsize);
		cmd.cmd = !end ? cmd.cmd : r_int32(cmd.cmd);
		if (cmd.cmd == LC_SEGMENT)
			if (segment_32((struct s_norm2){bin, off_set, &nb_sec,
				end, &off_sec, rez, size_file}, size_file))
				return (NULL);
		off_set += cmd.cmdsize;
		if (verif_offset(off_set, size_file))
			return (NULL);
	}
	return (rez);
}
