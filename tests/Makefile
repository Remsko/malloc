NAME = test
CC = gcc
RM = rm -rf

INC_PATH += ./incs
INC_NAME += test.h

INC = $(addprefix $(INC_PATH)/,$(INC_NAME))

CFLAGS = -Wall -Werror -Wextra
CPPFLAGS = $(addprefix -I,$(INC_PATH))

SRC_PATH = srcs
SRC_NAME += main.c
SRC_NAME += putstr.c

SRC_SUB += case
SRC_NAME += null.c
SRC_NAME += oversized.c
SRC_NAME += simple.c
SRC_NAME += write.c
SRC_NAME += zero.c

SRC_SUB += unit
SRC_NAME += search_chunk.c
SRC_NAME += split_chunk.c
SRC_NAME += search_heap.c

vpath %.c $(SRC_PATH) $(addprefix $(SRC_PATH)/, $(SRC_SUB))

OBJ_PATH = obj
OBJ_NAME = $(SRC_NAME:%.c=%.o)
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME)) 

LIB_PATH = ../
LIB = $(LIB_PATH)libft_malloc.so
CFLAGS += -I$(LIB_PATH)incs
LDFLAGS += -L./$(LIB_PATH) -lft_malloc

all: $(NAME)


$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS) 

$(OBJ): $(INC) | $(OBJ_PATH)
$(OBJ): $(OBJ_PATH)/%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

$(OBJ_PATH):
	@mkdir -p $@

clean:
	@$(RM) $(OBJ_PATH)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re