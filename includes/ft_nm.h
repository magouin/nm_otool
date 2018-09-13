/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 14:22:32 by magouin           #+#    #+#             */
/*   Updated: 2018/01/29 14:22:34 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H
# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <mach-o/loader.h>
# include <sys/mman.h>
# include <libft.h>
# include <ar.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>

struct						s_norm
{
	uint					end;
	size_t					*off_set;
	void					*bin;
}							;

struct						s_norm2
{
	void					*bin;
	size_t					off_set;
	int						*nb_sec;
	int						end;
	size_t					*off_sec;
	char					*rez;
	size_t					size_file;
}							;

struct						s_tab
{
	uint					nb;
	char					*str;
	uint64_t				value;
}							;

struct						s_bin 
{
	void					*bin;
	size_t					size;
}							;

struct s_tab				get_smallest(struct s_tab *tab, int *tabi);
int							verif_offset(size_t offset, size_t size_file);
int							fat_bin(void *bin, size_t size, int nb_arch,
	char **av);
int							macho_64(void *bin, struct mach_header_64 head,
	size_t size_file, int end);
int							macho_32(void *bin, struct mach_header head,
	size_t size_file, int end);
int							r_int32(int data);
int64_t						r_int64(int64_t data);
char						*get_index_32(int ncmds, int end, size_t size_file,
	void *bin);
char						*get_index_64(int ncmds, int end, size_t size_file,
	void *bin);
void						print_rez_32(struct nlist *lst, struct
	symtab_command table, void *bin, char *seg);
void						print_rez_64(struct nlist_64 *lst,
	struct symtab_command table, void *bin, char *seg);
int							ft_otool_32(void *bin, struct mach_header head,
	size_t size, int end);
int							ft_otool_64(void *bin, struct mach_header_64 head,
	size_t size, int end);
void						printfllx(unsigned long long nb, int z, char *str);
void						printfx(uint nb, int z, char *str);

#endif
