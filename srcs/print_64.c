/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 16:51:41 by magouin           #+#    #+#             */
/*   Updated: 2018/02/03 16:51:42 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

static int	get_tabi(struct s_tab **tab, struct symtab_command table,
	struct nlist_64 *lst, void *bin)
{
	uint32_t		n;
	int				mal;

	*tab = malloc(sizeof(struct s_tab) * (table.nsyms + 1));
	n = -1;
	mal = -1;
	while (++n < table.nsyms)
		if (!(lst[n].n_type & N_STAB))
		{
			(*tab)[++mal].nb = n;
			(*tab)[mal].str = bin + table.stroff + lst[n].n_un.n_strx;
			(*tab)[mal].value = lst[n].n_value;
		}
	(*tab)[mal + 1].str = NULL;
	(*tab)[mal + 1].nb = 0;
	return (mal);
}

static void	get_letter(struct nlist_64 *lst, char *seg,
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
		if (tmp.value)
		{
			printfllx(*(uint *)n.bin == 0xcefaedfe ? r_int64(tmp.value) : tmp.value, 16, " ");
			write(1, &c, 1);
			write(1, " ", 1);
			write(1, tmp.str, ft_strlen(tmp.str));
			write(1, "\n", 1);
		}
		else
			ft_printf("                 %c %s\n", c, tmp.str);
	}
}

void		print_rez_64(struct nlist_64 *lst, struct symtab_command table,
	void *bin, char *seg)
{
	struct s_tab	*tab;
	uint32_t		n;
	uint32_t		d;
	int				*tabi;
	struct s_tab	tmp;

	n = -1;
	d = get_tabi(&tab, table, lst, bin);
	tabi = malloc(4 * d + 4);
	tabi = ft_memset(tabi, 0, 4 * d + 4);
	while (tab[++n].str)
	{
		tmp = get_smallest(tab, tabi);
		d = -1;
		while (++d < table.nsyms)
			get_letter(lst, seg, tmp, (struct s_norm){d, NULL, bin});
	}
	free(tabi);
}
