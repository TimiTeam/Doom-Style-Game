#ifndef __SECTORS_H
#define __SECTORS_H
#include "sector_worker.h"

typedef struct 		s_read_holder
{
	SDL_Surface		**textures;
	t_wall			**walls;
	t_item			*all_items;
	char			*maps_path[5];
	t_light			**light_source;
	int 			player_sector_id;
	t_vector 		player_pos;
	int 			light_count;
	int				text_count;
	int				vect_count;
	int				wall_count;
}					t_read_holder;

int 				read_game_config_file(t_read_holder *holder, char *info_file_path);
t_sector			*read_map(char *pth, t_read_holder *holder, t_vector *player_pos);
int					get_num_from_str(char *str);
char				*skip_row_number(char *line);
void				get_count_struct_arrays(int fd, int *vect_count, int *wall_count);
unsigned			get_numbers(float *one, float *two, char delimiter, char *line);
char 				*clip_n_str(char *s1, char *s2, char *s3);
int					get_wall_count(char *str);
t_item				*make_item_ftom_str(char *line, char *directory_pth);

t_vector			*get_vectors(int fd, int vec_size);
t_wall				**get_walls(int fd, int wall_size, t_vector *vectors, SDL_Surface **textures);
t_sector			*make_sectors_list(int fd, t_read_holder *holder);
t_item				*make_items(char *data, t_item *all_items, t_read_holder *holder);

t_wall				**create_sector_walls(t_sector *sector, t_read_holder *holder, char *data, int wall_size);
void 				delete_light_source(t_light **light, unsigned array_size);
int 				find_dot_radius_intersect(t_vector light_pos, float radius, t_vector start, t_vector end);
#endif