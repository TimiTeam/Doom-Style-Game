#ifndef __SECTORS_H
#define __SECTORS_H
#include "sector_worker.h"

typedef struct 		s_read_holder
{
	SDL_Surface		**textures;
	t_wall			**walls;
	t_light			**light_source;
	t_sector		*all;
	t_item			*all_items;
	char			*maps_path[5];
	uint8_t			curr_map;
	uint8_t			maps_count;
	int 			player_sector_id;
	int 			light_count;
	int				text_count;
	int				vect_count;
	int				wall_count;
}					t_read_holder;

int 				read_game_config_file(t_read_holder *holder, char *info_file_path);
t_sector			*read_map(char *pth, t_read_holder *holder, t_vector *player_pos);
int					get_num_from_str(char *str);
char				*skip_row_number(char *line);
int					get_count_struct_arrays(int fd, int *vect_count, int *wall_count);
unsigned			get_numbers(float *one, float *two, char delimiter, char *line);
char 				*clip_n_str(char *s1, char *s2, char *s3);
int					get_wall_count(char *str);
t_item				*make_item_ftom_str(char *line, char *directory_pth);
int 				get_player_pos(int fd, t_vector *player_pos, int *player_sec_id);
t_sector			*get_player_sector(t_sector *sectors, int sec_num);
t_vector			*get_vectors(int fd, int vec_size);
t_wall				**get_walls(int fd, t_read_holder *holder, t_vector *vectors);
t_sector			*make_sectors_list(int fd, t_read_holder *holder);
t_item				*make_items(char *data, t_item *all_items, t_read_holder *holder);
void				*print_error_message_null(char *mess, char *error_obj);
int					print_error_message(char *mess, char *error_obj);
void				*free_array_surfcae_(SDL_Surface **array, unsigned size);
t_wall				**create_sector_walls(t_sector *sector, t_read_holder *holder, char *data, int wall_size);
t_light				**create_all_light_source(t_sector *sec, unsigned light_count);
void 				fill_sectors_light_source(t_sector *sec, t_light **light, unsigned array_size);
void 				delete_light_source(t_light **light, unsigned array_size);
float            	len_between_points(t_vector a, t_vector b);
int 				find_dot_radius_intersect(t_vector light_pos, float radius, t_vector start, t_vector end);
void				swap(int *a, int *b);
char				*get_path(int fd);
int 				check_sectors(t_sector *sector);
void				mark_all_neighbors(t_sector *sec, t_wall **all);
#endif