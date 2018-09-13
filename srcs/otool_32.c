/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 14:08:39 by magouin           #+#    #+#             */
/*   Updated: 2018/02/04 14:08:43 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

void	print_32(size_t *x, struct section section, void *bin, int end)
{
	if (!end)
	{
		if ((*x - section.offset) % 16 == 15 && *x - section.offset <
			section.size)
		{
			printfx(*(unsigned char *)(bin + *x), 2, " \n");
			printfx((section.addr + *x + 1 - section.offset), 8, "\t");
		}
		else if (*x - section.offset < section.size)
			printfx(*(unsigned char *)(bin + *x), 2, " ");
		(*x)++;
	}
	else
	{
		if ((*x - section.offset) / 4 % 4 == 3 && *x - section.offset <
			section.size)
		{
			printfx(r_int32(*(uint *)(bin + *x)), 8, " \n");
			printfx((section.addr + *x + 4 - section.offset), 8, "\t");
		}
		else if (*x - section.offset < section.size)
			printfx(r_int32(*(uint *)(bin + *x)), 8, " ");
		*x += 4;
	}
}

int		get_sec_text_32(struct s_bin file, struct segment_command seg,
	size_t off_sec, int end)
{
	size_t			x;
	struct section	section;
	uint32_t		sec;

	sec = 0;
	while (sec < seg.nsects)
	{
		section = *(struct section*)(off_sec + file.bin);
		section.size = !end ? section.size : (size_t)r_int32(section.size);
		section.addr = !end ? section.addr : (size_t)r_int32(section.addr);
		section.offset = !end ? section.offset :
		(size_t)r_int32(section.offset);
		if (ft_strequ(section.sectname, "__text"))
		{
			x = section.offset;
			printfx((section.addr + x - section.offset), 8, "\t");
			while (x < file.size && x - section.offset < section.size)
				print_32(&x, section, file.bin, end);
			write(1, "\n", 1);
		}
		if ((off_sec += sizeof(struct section)) >= file.size)
			return (1);
		sec++;
	}
	return (0);
}

int		ft_otool_32(void *bin, struct mach_header head, size_t size, int end)
{
	uint32_t				n;
	size_t					off_set;
	size_t					off_sec;
	struct segment_command	seg;

	n = 1;
	if ((off_set = sizeof(struct mach_header)) >= size)
		return (1);
	head.ncmds = !end ? head.ncmds : (size_t)r_int32(head.ncmds);
	size = !end ? size : (size_t)r_int32(size);
	while (++n < head.ncmds)
	{
		seg = *(struct segment_command *)(bin + off_set);
		seg.nsects = !end ? seg.nsects : r_int32(seg.nsects);
		seg.cmd = !end ? seg.cmd : r_int32(seg.cmd);
		seg.cmdsize = !end ? seg.cmdsize : r_int32(seg.cmdsize);
		if (LC_SEGMENT == seg.cmd)
		{
			off_sec = sizeof(struct segment_command) + off_set;
			get_sec_text_32((struct s_bin){bin, size}, seg, off_sec, end);
		}
		if ((off_set += seg.cmdsize) >= size)
			return (1);
	}
	return (0);
}
