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

int	get_sec_text_64(struct segment_command_64 seg,
	void *bin, size_t off_sec, int end)
{
	size_t							x;
	struct section_64				section;
	uint32_t						sec;

	sec = 0;
	while (sec < seg.nsects)
	{
		section = *(struct section_64*)(off_sec + bin);
		section.size = !end ? section.size : (size_t)r_int32(section.size);
		section.addr = !end ? section.addr : (size_t)r_int32(section.addr);
		section.offset = !end ? section.offset : (size_t)r_int32(section.offset);
		if (ft_strequ(section.sectname, "__text"))
		{
			x = section.offset;
			printf("%016llx\t", (section.addr + x - section.offset));
			while (x - section.offset < section.size)
			{
				if (!end)
				{
					(x - section.offset) % 16 == 15 && x - section.offset <
section.size ? printf("%02x \n%016llx\t", *(unsigned char *)(bin + x), (section.
addr + x + 1 - section.offset)) : printf("%02x ", *(unsigned char *)(bin + x));
					x++;
				}
				else
				{
					(x - section.offset) / 4 % 4 == 3 && x - section.offset <
section.size ? printf("%08x \n%016llx\t", r_int32(*(uint *)(bin + x)), (section.
addr + x + 4 - section.offset)) : printf("%08x ", r_int32(*(uint *)(bin + x)));
					x += 4;
				}
			}
			printf("\n");
		}
		off_sec += sizeof(struct section_64);
		sec++;
	}
	return (0);
}

int	ft_otool_64(void *bin, struct mach_header_64 head, size_t size, int end)
{
	uint32_t						n;
	size_t							off_set;
	size_t							off_sec;
	struct segment_command_64		seg;

	n = 0;
	(void)end;
	(void)size;
	off_set = sizeof(struct mach_header_64);
	head.ncmds = !end ? head.ncmds : (size_t)r_int32(head.ncmds);
	size = !end ? size : (size_t)r_int32(size);
	while (n < head.ncmds)
	{
		seg = *(struct segment_command_64 *)(bin + off_set);
		seg.nsects = !end ? seg.nsects : r_int32(seg.nsects);
		seg.cmd = !end ? seg.cmd : r_int32(seg.cmd);
		seg.cmdsize = !end ? seg.cmdsize : r_int32(seg.cmdsize);
		if (LC_SEGMENT_64 == seg.cmd)
		{
			off_sec = sizeof(struct segment_command_64) + off_set;
			get_sec_text_64(seg, bin, off_sec, end);
		}
		off_set += seg.cmdsize;
		n++;
	}
	return (0);
}
