CC				= cc
CFLAGS			= -Wall -Wextra -Werror -I$(INC_DIR) -I$(MLX_DIR)

NAME			= fractol
BONUS_NAME		= fractol_bonus

MLX_DIR			= minilibx
MLX				= $(MLX_DIR)/libmlx.a
MLXFLAGS		= -lmlx -lXext -lX11 -lm -lz

MANDATORY_DIR	= mandatory
BONUS_DIR		= bonus

SRC				= $(wildcard $(MANDATORY_DIR)/*.c)
OBJ				= $(SRC:.c=.o)

SRC_BONUS		= $(wildcard $(BONUS_DIR)/*.c)
OBJ_BONUS		= $(SRC_BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(MLX)
	$(CC) $(CFLAGS) $(OBJ) -L$(MLX_DIR) $(MLXFLAGS) -o $(NAME)

bonus: $(OBJ_BONUS) $(MLX)
	$(CC) $(CFLAGS) $(OBJ_BONUS) -L$(MLX_DIR) $(MLXFLAGS) -o $(BONUS_NAME)

$(MLX):
	@make -C $(MLX_DIR)

clean:
	rm -rf $(OBJ)
	rm -rf $(OBJ_BONUS)
	@make -C $(MLX_DIR) clean

fclean: clean
	rm -rf $(NAME)
	rm -rf $(BONUS_NAME)

re:	fclean all

.PHONY: all clean fclean re