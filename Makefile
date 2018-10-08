# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbeckert <mbeckert@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/16 15:19:49 by mbeckert          #+#    #+#              #
#    Updated: 2018/09/03 16:15:41 by yokartou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


## Name of Project

NAME = RT

## Color for compilating (pink)

COLOR = \0033[1;35m

## List of Directories

INC_DIR = includes
OBJ_DIR = objs
SRC_DIR = srcs
LIB_DIR = libft
FRMWK_DIR = frameworks

PARSER_DIR = parserino

## Compilating Utilities

FAST = -Ofast
#DEBUG = -g3 -fsanitize=address
FLAGS = -Wall -Wextra -Werror $(FAST) $(DEBUG) -D_REENTRANT

# INC = $(INC_DIR:%=-I./$(LIB_DIR)/%) $(INC_DIR:%=-I./%)
INC = $(INC_DIR:%=-I./$(LIB_DIR)/%) $(INC_DIR:%=-I./%) -I./libpng/include -I ./libxml2/include/libxml2
# LIB = -L$(LIB_DIR) -lft
LIB = -L$(LIB_DIR) -lft -Llibxml2/lib -lxml2 -Llibpng/lib -lpng
INC_FRMWK = -D_THREAD_SAFE -F ./$(FRMWK_DIR)

HOME =  $(shell pwd)/Frameworks
FRMWK = -framework SDL2 -framework SDL2_image -framework SDL2_ttf -F ./$(FRMWK_DIR) -rpath $(HOME)

CC = clang $(FLAGS) $(INC)

## List of Functions

INCLUDE_H = rt \
			define \
			struct \
			filter \
			parsing \
			events \
			interface \
			texture \

SRC_FT = init_rt \
		init_sdl \
		init_sdl2 \
		rtv1 \
		shape \
		init_all \
		quaternion \
		quaternion2 \
		init_origin \
		init_projection \
		init_buffer \
		scene_cam \
		scene_pixel \
		perlin3d \
		recurse_pixel \
		visual_effect \
		visual_effect2 \
		visual_effect3 \
		visual_effect4 \
		display_interface1 \
		display_interface2 \
		display_interface3 \
		display_interface4 \
		error \
		event \
		event_bis \
		etc \
		etc2 \
		etc3 \
		recurse \
		recurse2 \
		recurse3 \
		maths \
		vector \
		vector2 \
		limit \
		option \
		get_tex_value \
		atof_extreme \
		screenshooter \
		get_checker \
		collider_normal \

PARSER_FT = parser \
		parser2 \
		parser3 \
		parser4 \
		parser5 \
		parser6 \
		parser7 \
		parser8 \
		parser9 \
		savexml \

## List of Utilities

SRC = $(SRC_FT:%=$(SRC_DIR)/%.c) \
	$(PARSER_FT:%=$(SRC_DIR)/$(PARSER_DIR)/%.c) \

OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

OBJ_DIRS = $(PARSER_DIR:%=$(OBJ_DIR)/%) \

INCLUDES = $(INCLUDE_H:%=./$(INC_DIR)/%.h)
## Rules of Makefile

all: $(NAME)
	@echo "$(COLOR)$(NAME)\t\t\0033[1;30m[All OK]\0033[1;37m"

$(OBJ_DIRS):
	@mkdir -p $@
	@echo "$(COLOR)Creating :\t\0033[0;32m$@\0033[1;37m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDES)
	@$(CC) $(INC_FRMWK) -c $< -o $@
	@echo "$(COLOR)Compiled :\t\0033[0;32m$(@:$(OBJ_DIR)/%=%)\0033[1;37m"

$(NAME): $(OBJ_DIRS) $(SRC) $(INCLUDES)
	@$(MAKE) -j $(OBJ)
	@echo "$(COLOR)Objects\t\t\0033[0;32m[Created]\0033[1;37m"
	@make -j -C $(LIB_DIR)
	@$(CC) $(LIB) $(FRMWK) $(OBJ) -o $@
	@echo "$(COLOR)$(NAME)\t\t\0033[0;32m[Created]\0033[1;37m"

clean:
	@rm -rf $(OBJ_DIR)
	@make fclean -C $(LIB_DIR)
	@echo "$(COLOR)Objects\t\t\0033[0;31m[Deleted]\0033[1;37m"

fclean: clean
	@rm -f $(NAME)
	@echo "$(COLOR)$(NAME)\t\t\0033[0;31m[Deleted]\0033[1;37m"

re: fclean all

norme:
	@norminette $(SRC) $(INC_DIR)/
	@make norme -C $(LIB_DIR)

frameworks_clean:
	@rm -rf ./$(FRMWK_DIR)

frameworks: frameworks_clean
	@mkdir ./$(FRMWK_DIR)
	curl -o SDL2 https://www.libsdl.org/release/SDL2-2.0.8.dmg
	curl -o SDL2_image https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.3.dmg
	curl -o SDL2_ttf https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.14.dmg
	hdiutil attach SDL2
	hdiutil attach SDL2_image
	hdiutil attach SDL2_ttf
	cp -rf /Volumes/SDL2/SDL2.framework ./$(FRMWK_DIR)
	cp -rf /Volumes/SDL2_image/SDL2_image.framework ./$(FRMWK_DIR)
	cp -rf /Volumes/SDL2_ttf/SDL2_ttf.framework ./$(FRMWK_DIR)
	hdiutil detach /Volumes/SDL2
	hdiutil detach /Volumes/SDL2_image
	hdiutil detach /Volumes/SDL2_ttf
	rm -rf SDL2
	rm -rf SDL2_image
	rm -rf SDL2_ttf

coffee: libs frameworks all

coffee_clean: frameworks_clean libs_clean fclean

libs_clean:
	@rm -rf ./libxml2
	@rm -rf ./libpng

libs: libs_clean
	curl -o XML2 ftp://xmlsoft.org/libxml2/libxml2-2.9.8.tar.gz
	curl -o PNG ftp://ftp-osl.osuosl.org/pub/libpng/src/libpng16/libpng-1.6.34.tar.gz
	gunzip -c XML2 | tar xopf -
	gunzip -c PNG | tar xopf -
	rm -rf XML2
	rm -rf PNG
	mkdir ./libxml2
	mkdir ./libpng
	(cd ./libxml2 && ../libxml2-2.9.8/configure --prefix=$$PWD --with-python-install-dir=$$PWD/python)
	(cd ./libpng && ../libpng-1.6.34/configure --prefix=$$PWD)
	(cd ./libxml2 && make && make install)
	(cd ./libpng && make && make install)
	rm -r ./libxml2-2.9.8
	rm -r ./libpng-1.6.34

.PHONY: all clean fclean re norme frameworks frameworks_clean libs libs_clean coffee coffee_clean
