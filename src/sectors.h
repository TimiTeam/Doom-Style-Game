/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabala <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 14:06:18 by atabala           #+#    #+#             */
/*   Updated: 2019/10/16 14:22:26 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SECTORS_H
# define __SECTORS_H
# include "sector_worker.h"
# define MAX_MAPS 5

typedef struct		s_read_holder
{
	SDL_Surface		**textures;
	t_wall			**walls;
	t_light			**light_source;
	t_sector		*all;
	t_item			*all_items;
	Mix_Chunk		*hit_sound;
	Mix_Chunk		*roar_sound;
	char			*maps_path[MAX_MAPS];
	SDL_Surface		*skyboxes[MAX_MAPS];
	t_gun			**all_guns;
	uint8_t			curr_map;
	uint8_t			maps_count;
	int				light_count;
	int				text_count;
	int				vect_count;
	int				wall_count;
	t_vector		player_start;
	t_vector		player_end;
	unsigned		player_end_sect;
	unsigned		player_sector_id;
	char			f;
}					t_read_holder;

int					read_game_config_file(t_read_holder *holder,
						char *info_file_path);
t_sector			*read_map(char *pth, t_read_holder *holder);
SDL_Surface			**load_img_array_from_file(int fd, unsigned size);
char				*skip_line_with_word(char *line, char *word);
enum e_gun_type		get_gun_type(char *type);
int					get_num_from_str(char *str);
char				*skip_row_number(char *line);
int					get_count_struct_arrays(int fd, int *vect_count,
						int *wall_count);
unsigned			get_numbers(float *one, float *two,
						char delimiter, char *line);
char				*clip_n_str(char *s1, char *s2, char *s3);
int					get_wall_count(char *str);
t_item				*make_item_ftom_str(char *line, char *directory_pth);
int					player_start_and_end(int fd, t_read_holder *holder);
t_sector			*get_player_sector(t_sector *sectors, int sec_num);
t_vector			*get_vectors(int fd, int vec_size);
t_wall				**get_walls(int fd, t_read_holder *holder,
						t_vector *vectors);
t_sector			*make_sectors_list(int fd, t_read_holder *holder);
t_item				*make_items(char *data, t_item *all_items,
						t_read_holder *holder);
void				*print_error_message_null(char *mess, char *error_obj);
int					print_error_message(char *mess, char *error_obj);
void				*error_free_array_surf(SDL_Surface **array, unsigned size,
											char *message);
t_wall				**create_sector_walls(t_sector *sector,
						t_read_holder *holder, char *data, int wall_size);
t_light				**create_all_light_source(t_sector *sec,
						unsigned light_count);
void				fill_sectors_light_source(t_sector *sec,
						t_light **light, unsigned array_size);
void				delete_light_source(t_light **light, unsigned array_size);
float				len_between_points(t_vector a, t_vector b);
int					find_dot_radius_intersect(t_vector light_pos, float radius,
						t_vector start, t_vector end);
void				swap(int *a, int *b);
char				*get_path(int fd);
unsigned short		dot_inside_sector(t_vector dot,
									t_wall **walls, unsigned arr_size);
int					check_sectors(t_sector *sector);
void				mark_all_neighbors(t_sector *sec, t_wall **all);

#endif
