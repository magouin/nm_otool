/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_32.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 14:08:32 by magouin           #+#    #+#             */
/*   Updated: 2018/02/04 14:08:33 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

void	print_32(size_t *x, struct section section, void *bin, int end)
{
	if (!end)
	{
		(*x - section.offset) % 16 == 15 && *x - section.offset < section.size ?
printf("%02x \n%08x\t", *(unsigned char *)(bin + *x), (uint)(section.addr +
*x + 1 - section.offset)) : printf("%02x ", *(unsigned char *)(bin + *x));
		(*x)++;
	}
	else
	{
		(*x - section.offset) / 4 % 4 == 3 && *x - section.offset < section.
size ? printf("%08x \n%08x\t", r_int32(*(uint *)(bin + *x)), (uint)(section.
addr + *x + 4 - section.offset)) : printf("%08x ", r_int32(*(uint *)(bin +
	*x)));
		*x += 4;
	}
}

int		get_sec_text_32(struct segment_command seg,
	void *bin, size_t off_sec, int end)
{
	size_t			x;
	struct section	section;
	uint32_t		sec;

	sec = 0;
	while (sec < seg.nsects)
	{
		section = *(struct section*)(off_sec + bin);
		section.size = !end ? section.size : (size_t)r_int32(section.size);
		section.addr = !end ? section.addr : (size_t)r_int32(section.addr);
		section.offset = !end ? section.offset : (size_t)r_int32(section.
offset);
		if (ft_strequ(section.sectname, "__text"))
		{
			x = section.offset;
			printf("%08x\t", (uint)(section.addr + x - section.offset));
			while (x - section.offset < section.size)
				print_32(&x, section, bin, end);
			printf("\n");
		}
		off_sec += sizeof(struct section);
		sec++;
	}
	return (0);
}

int		ft_otool_32(void *bin, struct mach_header head, size_t size, int end)
{
	uint32_t						n;
	size_t							off_set;
	size_t							off_sec;
	struct segment_command			seg;

	n = 0;
	off_set = sizeof(struct mach_header);
	head.ncmds = !end ? head.ncmds : (size_t)r_int32(head.ncmds);
	size = !end ? size : (size_t)r_int32(size);
	while (n < head.ncmds)
	{
		seg = *(struct segment_command *)(bin + off_set);
		seg.nsects = !end ? seg.nsects : r_int32(seg.nsects);
		seg.cmd = !end ? seg.cmd : r_int32(seg.cmd);
		seg.cmdsize = !end ? seg.cmdsize : r_int32(seg.cmdsize);
		if (LC_SEGMENT == seg.cmd)
		{
			off_sec = sizeof(struct segment_command) + off_set;
			get_sec_text_32(seg, bin, off_sec, end);
		}
		off_set += seg.cmdsize;
		n++;
	}
	return (0);
}
