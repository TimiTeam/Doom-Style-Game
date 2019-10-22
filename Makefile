# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/25 15:29:39 by mshpakov          #+#    #+#              #
#    Updated: 2019/10/16 20:01:00 by tbujalo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compilation
CFLAGS =            -Wall -Wextra -Werror -g
O_FLAG =		-O2
OTHER_FLAGS = 
#OTHER_FLAGS =      -fsanitize=address

# Default rule
DEFRULE =           all

# Binaries
BUILDER_NAME =      builder
DOOM_NAME =         doom-nukem

# Directories

BUILDER_SRCDIR =    ./builder_src
BUILDER_OBJDIR =    ./builder_obj
DOOM_SRCDIR =       ./doom_src
DOOM_OBJDIR =       ./doom_obj
UNAME_S :=          $(shell uname -s)
FTDIR =             libft/
FT_INC =            -I libft/

ifeq ($(UNAME_S),Darwin)

	CC :=			clang
	SDL2_INC =      -I $(CURDIR)/frameworks/SDL2.framework/Headers/ \
                    -I $(CURDIR)/frameworks/SDL2_mixer.framework/Headers \
                    -I $(CURDIR)/frameworks/SDL2_ttf.framework/Headers/ \
                    -I $(CURDIR)/frameworks/SDL2_image.framework/Headers/
	SDL2_FLAGS =
	FLAG_F =        -F frameworks
	SDL2_LINK =     -rpath frameworks -framework SDL2 -framework SDL2_mixer -framework SDL2_image -framework SDL2_ttf

endif

ifeq ($(UNAME_S),Linux)
	CC :=           gcc
    SDL2_INC =
    SDL2_FLAGS =   `sdl2-config --cflags`
    FLAG_F =
    SDL2_LINK =     `sdl2-config --libs` -lSDL2_ttf -lSDL2_image -lSDL2_mixer
    OTHER_FLAGS =       -pthread
endif

# Sources

BUILDER_SRC = sdl_fun.c \
					main_menu.c \
					main.c \
					levels.c \
					get_assets.c \
					render.c \
					modes.c \
					math.c \
					rewrite.c \
					render_grid.c \
					fill_polygon.c \
					editor.c \
					prog.c \
					add_to_media.c \
					zoom.c \
					textures.c \
					useful.c \
					move.c \
					edit_menu.c \
					values.c \
					init_editor_buttons.c \
					edit_walls.c \
					items.c \
					sel_item.c \
					fill_grid.c \
					grid_main.c \
					find_in_media.c \
					sector_logic.c \
					delete_world.c \
					delete_sector.c \
					validate_media.c \
					file_fun.c \
					memory_fun.c \
					line_math.c \
					vec_ops.c \
					render_btn.c \
					manage_btn.c \
					delete_vector.c \
					add_door.c \
					sort.c \
					get_input.c \
					drawing.c \
					states.c \
					get_sec_v.c \
					get_sec_items.c \
					select_lit.c \
					char_ops.c \
					add_sector.c \
					texture_edit.c \
					edit_world.c \
					editor_render.c \
					editor_update.c \
					render_items.c \
					move_item.c \
					render_elements.c \
					move_player.c \
					move_vector.c \
					update_sec.c \
					render_grid_iso.c \
					render_grid_elems.c \
					delete_useless.c \
					replace.c \
					validate_clockwise.c \
					write_section.c \
					write_level.c \
					identify.c \
					read_assets_help.c \
					get_map.c \
					section.c \
					free_media.c \
					update_media_sect.c \
					read_levels.c \
					get_map_elems.c \
					init_world.c \
					read_line.c \
					drawing_help.c \
					edit_walls_help.c \
					grid_ops.c \
					btn_press.c \
					distribute_btns.c \
					levels_btn.c \
					mode_btn.c \
					math_ops.c \
					btn_main.c \
					clip_line.c \
					check_for_light.c \
					draw_line.c \
					settings.c \
					add_door_help.c \
					texture_name.c \
					btn_press_settings.c \
					get_boxes.c \
					break_wall.c \
					map_useful.c \
					settings_help.c \
					light_sec_type.c

DOOM_SRC =			sdl_worker.c \
                    sdl_create.c \
                    sdl_exit.c \
                    sdl_texture.c \
                    img_loader.c \
           			sector_worker.c \
           			main.c \
           			make_sectors.c \
           			texture.c \
           			additiona_reader_data.c \
           			pixel_worker.c \
           			item_worker.c \
           			sprite_worker.c \
           			player_worker.c \
           			sort_items.c \
           			additional_functions.c \
           			data_reader.c \
           			item_loader.c \
           			wall_reader.c \
           			sector_items_loader.c \
           			projectiles.c \
           			sector_wall_maker.c \
           			skybox.c \
           			menu_main.c \
           			keyactions.c \
           			additional_read_functions.c \
           			error_exit_and_message.c \
           			light_source_worker.c \
           			menu_worker.c \
           			hud.c \
           			drawing_image.c \
           			math.c \
           			sort_sector_elements.c \
           			delete_projectiles.c \
           			enemy_movement.c \
           			items_deletion.c \
           			ceil_and_floor.c \
           			player_movement.c \
           			math2.c \
           			interactions.c \
           			gun_worker.c \
           			proj_render.c \
           			draw_world.c \
           			fill_super_data.c \
           			thread_drawing_help.c \
           			events.c \
           			draw_items.c \
           			game_loop.c \
           			draw_sectors.c \
           			check_enemy_state.c \
           			change_player_state.c \
           			fps_counter.c \
           			run_drawig_sectors.c \
           			free_and_exit.c \
           			calc_wall_helper.c \
           			gun_animations.c \
           			run_drawing_thread.c \
           			create_game.c \
           			player_update_helper.c \
           			interactions_helper.c \
                    define_player_pos.c \
                    wall_read_helper.c

BUILDER_OBJ =       $(BUILDER_SRC:.c=.o)
DOOM_OBJ =          $(DOOM_SRC:.c=.o)

MATH_LINK =		    -lm
FT_LINK =		    -L libft/ -lft

# Paths foreach
BUILDER_OBJP =		    $(addprefix $(BUILDER_OBJDIR)/, $(BUILDER_SRC:.c=.o))
DOOM_OBJP =             $(addprefix $(DOOM_OBJDIR)/, $(DOOM_SRC:.c=.o))

# **************************************************************************** #
# SPECIAL CHARS

LOG_CLEAR		=   \033[2K
LOG_UP			=   \033[A
LOG_NOCOLOR		=   \033[0m
LOG_BOLD		=   \033[1m
LOG_UNDERLINE	=   \033[4m
LOG_BLINKING	=   \033[5m
LOG_BLACK		=   \033[1;30m
LOG_RED			=   \033[1;31m
LOG_GREEN		=   \033[1;32m
LOG_YELLOW		=   \033[1;33m
LOG_BLUE		=   \033[1;34m
LOG_VIOLET		=   \033[1;35m
LOG_CYAN		=   \033[1;36m
LOG_WHITE		=   \033[1;37m

# **************************************************************************** #
# RULES
.SILENT:

.PHONY: fclean clean re ft default doom_builder doom

# Main rules
default:
	@echo -e "$(LOG_BOLD)Default execution: rule $(DEFRULE)$(LOG_NOCOLOR)"
	@make $(DEFRULE)
	@echo -e "$(LOG_BOLD)Execution finished     $(LOG_NOCOLOR)ヽ(ヅ)ノ"

all: ft $(BUILDER_OBJDIR) $(BUILDER_NAME) $(DOOM_OBJDIR) $(DOOM_NAME)

doom_builder: ft $(BUILDER_OBJDIR) $(BUILDER_NAME)

doom: ft $(DOOM_OBJDIR) $(DOOM_NAME)

# Compilation rules
ft:
	@make all -C libft/

$(BUILDER_OBJDIR)/%.o: $(BUILDER_SRCDIR)/%.c
	echo -e "--$(LOG_CLEAR)$(LOG_VIOLET)$(BUILDER_NAME)$(LOG_NOCOLOR)........................... $(LOG_YELLOW)$<$(LOG_NOCOLOR)$(LOG_UP)"
	$(CC) $(CFLAGS) $(O_FLAG) $(OTHER_FLAGS) -c -o $@ $^ $(FLAG_F) $(FT_INC) $(SDL2_INC) $(SDL2_FLAGS)

$(DOOM_OBJDIR)/%.o: $(DOOM_SRCDIR)/%.c
	echo -e "--$(LOG_CLEAR)$(LOG_VIOLET)$(DOOM_NAME)$(LOG_NOCOLOR)........................... $(LOG_YELLOW)$<$(LOG_NOCOLOR)$(LOG_UP)"
	$(CC) $(CFLAGS) $(O_FLAG) $(OTHER_FLAGS) -c -o $@ $^ $(FLAG_F) $(FT_INC) $(SDL2_INC) $(SDL2_FLAGS)

$(BUILDER_OBJDIR):
	@echo -e "$(LOG_CLEAR)$(LOG_BLUE)build $(LOG_YELLOW)$(BUILDER_NAME)$(LOG_NOCOLOR)"
	mkdir -p $(BUILDER_OBJDIR)

$(DOOM_OBJDIR):
	@echo -e "$(LOG_CLEAR)$(LOG_BLUE)build $(LOG_YELLOW)$(DOOM_NAME)$(LOG_NOCOLOR)"
	mkdir -p $(DOOM_OBJDIR)

$(BUILDER_NAME): $(BUILDER_OBJP)
	@echo -e "--$(LOG_CLEAR)$(LOG_VIOLET)$(BUILDER_NAME)$(LOG_NOCOLOR)......................... $(LOG_YELLOW)assembling$(LOG_NOCOLOR)$(LOG_UP)"
	@$(CC) $(CFLAGS) $(O_FLAG) $(OTHER_FLAGS) -o $@ $^ $(FLAG_F) $(SDL2_LINK) $(FT_LINK) $(MATH_LINK) $(SDL2_INC)
	@echo -e "--$(LOG_CLEAR)$(LOG_VIOLET)$(BUILDER_NAME)$(LOG_NOCOLOR) compiled.................. $(LOG_GREEN)✓$(LOG_NOCOLOR)"

$(DOOM_NAME): $(DOOM_OBJP)
	echo -e "--$(LOG_CLEAR)$(LOG_VIOLET)$(DOOM_NAME)$(LOG_NOCOLOR)......................... $(LOG_YELLOW)assembling$(LOG_NOCOLOR)$(LOG_UP)"
	$(CC) $(CFLAGS) $(O_FLAG) $(OTHER_FLAGS) -o $@ $^ $(FLAG_F) $(SDL2_LINK) $(FT_LINK) $(MATH_LINK) $(SDL2_INC)
	echo -e "--$(LOG_CLEAR)$(LOG_VIOLET)$(DOOM_NAME)$(LOG_NOCOLOR) compiled.................. $(LOG_GREEN)✓$(LOG_NOCOLOR)"

clean:
	@echo -e "$(LOG_CLEAR)$(LOG_BLUE)clean $(LOG_YELLOW)$(BUILDER_NAME)$(LOG_NOCOLOR)"
	@echo -e "$(LOG_CLEAR)$(LOG_BLUE)clean $(LOG_YELLOW)$(DOOM_NAME)$(LOG_NOCOLOR)"
	@echo -e "--$(LOG_CLEAR)$(LOG_YELLOW)Objects$(LOG_NOCOLOR) deletion............. $(LOG_RED)×$(LOG_NOCOLOR)"
	@rm -rf $(BUILDER_OBJDIR)
	@rm -rf $(DOOM_OBJDIR)
	@echo -e "$(LOG_CLEAR)$(LOG_BLUE)clean $(LOG_YELLOW)libft$(LOG_NOCOLOR)"
	@make clean -C libft/


fclean:
	@echo -e "$(LOG_CLEAR)$(LOG_BLUE)fclean $(LOG_YELLOW)libft$(LOG_NOCOLOR)"
	@make fclean -C libft/
	@echo -e "$(LOG_CLEAR)$(LOG_BLUE)fclean $(LOG_YELLOW)$(BUILDER_NAME) and $(DOOM_NAME)$(LOG_NOCOLOR)"
	@echo -e "--$(LOG_CLEAR)$(LOG_YELLOW)Objects$(LOG_NOCOLOR) deletion............. $(LOG_RED)×$(LOG_NOCOLOR)"
	@rm -rf $(BUILDER_OBJDIR)
	@rm -rf $(DOOM_OBJDIR)
	@echo -e "--$(LOG_CLEAR)$(LOG_YELLOW)Binary$(LOG_NOCOLOR) deletion.............. $(LOG_RED)×$(LOG_NOCOLOR)"
	@rm -f $(BUILDER_NAME)
	@rm -f $(DOOM_NAME)

re: fclean all
