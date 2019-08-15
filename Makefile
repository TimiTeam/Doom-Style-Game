NAME := test

SRCS	:= sdl_worker.c sdl_create.c sdl_exit.c sdl_texture.c img_loader.c ttf_worker.c sector_worker.c test_main.c make_sectors.c texture.c timer.c

DIR_SRC := $(CURDIR)/src
DIR_OBJ := $(CURDIR)/obj

OBJS := $(SRCS:.c=.o)

OBJS := $(addprefix $(DIR_OBJ)/, $(OBJS))
SRCS := $(addprefix $(DIR_SRC)/, $(SRCS))

CC := clang

SDL_INCL =	-I $(CURDIR)/frameworks/SDL2.framework/Headers/ \
			-I $(CURDIR)/frameworks/SDL2_mixer.framework/Headers \
			-I $(CURDIR)/frameworks/SDL2_ttf.framework/Headers/ \
			-I $(CURDIR)/frameworks/SDL2_image.framework/Headers/

FLAG_W = -Wall -Wextra -Werror

FLAG_W = 

FLAG_F = -F frameworks

LFT_INCL = -I libft/

LIBFT_A = libft/libft.a

SDL_RUN_FLAGS = -rpath frameworks -framework SDL2 -framework SDL2_mixer -framework SDL2_image -framework SDL2_ttf

all: $(NAME)

$(LIBFT_A):
	@make -C libft/

$(DIR_OBJ):
	@mkdir -p $(DIR_OBJ)

$(NAME): $(LIBFT_A) $(OBJS)
	$(CC) -g -fsanitize=address $(OBJS) $(FLAG_F) $(SDL_RUN_FLAGS) -L libft -lft -o $(NAME)


$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c | $(DIR_OBJ)
	$(CC) -g -fsanitize=address $(FLAG_W) -pthread  $(FLAG_F) $(SDL_INCL) $(LFT_INCL) -c $< -o $@

clean:
	@make -C libft/ clean
	/bin/rm -rf $(OBJS)
	/bin/rm -rf $(DIR_OBJ)

fclean: clean
	@make -C libft/ fclean
	/bin/rm -rf $(NAME)

re: fclean all

.PHONY: all fclean clean re
