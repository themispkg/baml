CC=gcc
CFLAGS=-Wall -Wextra -Werror
INC_PATH=include
SRC_PATH=src
OBJ_PATH=obj
SRCS=baml.c arg_checks.c read_file.c prints.c errors.c \
	 contain_check.c find_index.c
OBJS=$(SRCS:.c=.o)
OBJ_FILE=$(foreach item, $(OBJS), $(addprefix $(OBJ_PATH)/, $(item)))
NAME=baml

all: $(NAME)

$(NAME): $(OBJ_PATH) $(OBJ_FILE)
	$(CC) $(CFLAGS) -o $@ $(OBJ_FILE)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	$(CC) $(CFLAGS) -I $(INC_PATH) -c -o $@ $^

re: fclean all
fclean: clean
	rm -rf $(OBJ_PATH)
clean:
	rm -rf $(NAME)
.PHONY: all clean fclean re
