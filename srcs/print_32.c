/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_32.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 16:51:34 by magouin           #+#    #+#             */
/*   Updated: 2018/02/03 16:51:35 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

static int	get_tabi(struct s_tab **tab, struct symtab_command table,
	struct nlist *lst, void *bin)
{
	uint32_t		n;
	int				mal;

	*tab = malloc(sizeof(struct s_tab) * (table.nsyms + 1));
	n = -1;
	mal = -1;
	while (++n < table.nsyms)
		if (!(lst[n].n_type & N_STAB))
		{
			(*tab)[++mal].str = bin + table.stroff + lst[n].n_un.n_strx;
			(*tab)[mal].nb = n;
		}
	(*tab)[mal + 1].str = NULL;
	(*tab)[mal + 1].nb = -1;
	return (mal);
}

static void	get_letter(struct nlist *lst, char *seg,
	struct s_tab tmp, struct s_norm n)
{
	char			c;

	if (lst[n.end].n_type == N_PEXT || lst[n.end].n_type == N_EXT)
		c = 'U';
	else if ((lst[n.end].n_type & N_SECT) == N_SECT)
		c = seg[lst[n.end].n_sect - 1];
	else if (lst[n.end].n_type & N_ABS)
		c = 'A';
	else
		c = 'Z';
	if ((lst[n.end].n_type & N_EXT) == 0)
		c += 32;
	if (tmp.nb == n.end)
	{
		if (lst[n.end].n_value)
			printf("%08x %c %s\n", *(uint *)n.bin == 0xcefaedfe ?
		r_int32(lst[n.end].n_value) : lst[n.end].n_value, c, tmp.str);
		else
			printf("         %c %s\n", c, tmp.str);
	}
}

void		print_rez_32(struct nlist *lst, struct symtab_command table,
	void *bin, char *seg)
{
	struct s_tab	*tab;
	uint32_t		n;
	uint32_t		d;
	int				*tabi;
	struct s_tab	tmp;

	d = get_tabi(&tab, table, lst, bin);
	tabi = malloc(4 * d + 4);
	tabi = ft_memset(tabi, 0, 4 * d + 4);
	n = -1;
	while (tab[++n].str)
	{
		tmp = get_smallest(tab, tabi);
		d = -1;
		while (++d < table.nsyms)
			get_letter(lst, seg, tmp, (struct s_norm){d, NULL, bin});
	}
	free(tabi);
}
