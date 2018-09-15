/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho_64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 10:25:00 by magouin           #+#    #+#             */
/*   Updated: 2018/02/03 10:25:02 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

static int		get_table(struct symtab_command *table, struct s_norm n,
	size_t size_file)
{
	*table = *(struct symtab_command *)(n.bin + *n.off_set);
	table->nsyms = !n.end ? table->nsyms : (size_t)r_int32(table->nsyms);
	table->symoff = !n.end ? table->symoff : (size_t)r_int32(table->symoff);
	table->stroff = !n.end ? table->stroff : (size_t)r_int32(table->stroff);
	if (verif_offset(table->symoff, size_file) ||
		verif_offset(table->stroff, size_file))
		return (1);
	return (0);
}

static int		symtab_sec(struct symtab_command *table, struct s_norm n,
	struct nlist_64 **lst, size_t size_file)
{
	uint32_t						x;

	if (get_table(table, n, size_file))
		return (1);
	x = 0;
	(*lst) = malloc(sizeof(struct nlist_64) * table->nsyms);
	while (x < table->nsyms)
	{
		(*lst)[x] = *(struct nlist_64 *)((n.bin + table->symoff) + x *
			sizeof(struct nlist_64));
		(*lst)[x].n_un.n_strx = !n.end ? (*lst)[x].n_un.n_strx :
		(size_t)r_int32((*lst)[x].n_un.n_strx);
		(*lst)[x].n_sect = !n.end ? (*lst)[x].n_sect :
		(size_t)r_int32((*lst)[x].n_sect);
		x++;
	}
	return (0);
}

static int		get_info_cmd(struct s_norm n, struct symtab_command *table,
	struct nlist_64 **lst, size_t size_file)
{
	struct load_command				cmd;

	if (verif_offset(*n.off_set, size_file))
		return (1);
	cmd = *(struct load_command *)(n.bin + *n.off_set);
	cmd.cmd = !n.end ? cmd.cmd : r_int32(cmd.cmd);
	if (cmd.cmd == LC_SYMTAB)
		if (symtab_sec(table, n, lst, size_file))
			return (1);
	cmd.cmdsize = !n.end ? cmd.cmdsize : r_int32(cmd.cmdsize);
	*n.off_set += cmd.cmdsize;
	if (verif_offset(*n.off_set, size_file))
		return (1);
	return (0);
}

int				macho_64(void *bin, struct mach_header_64 head,
	size_t size_file, int end)
{
	size_t							off;
	uint32_t						n;
	struct symtab_command			table;
	struct nlist_64					*lst;
	char							*rez;

	n = 0;
	head.ncmds = !end ? head.ncmds : (size_t)r_int32(head.ncmds);
	size_file = !end ? size_file : (size_t)r_int32(size_file);
	off = sizeof(struct mach_header_64);
	rez = get_index_64(head.ncmds, end, size_file, bin);
	if (!rez)
		return (1);
	while (n < head.ncmds)
	{
		if (get_info_cmd((struct s_norm){end, &off, bin}, &table,
			&lst, size_file))
			return (1);
		if (verif_offset(off, size_file))
			return (1);
		n++;
	}
	print_rez_64(lst, table, rez, (struct s_bin){bin, size_file});
	return (0);
}
