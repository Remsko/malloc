NAME = test
CC = gcc
RM = rm -rf

INC_PATH += ./incs

INC = $(addprefix $(INC_PATH)/,$(INC_NAME))

CFLAGS = -Wall -Werror -Wextra -Wconversion -g3
CPPFLAGS = $(addprefix -I,$(INC_PATH))

SRC_PATH = srcs
SRC_NAME += main.c

SRC_SUB += 
SRC_NAME += 

vpath %.c $(SRC_PATH) $(addprefix $(SRC_PATH)/, $(SRC_SUB))

OBJ_PATH = obj
OBJ_NAME = $(SRC_NAME:%.c=%.o)
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME)) 

LIB_PATH = ../
LIB = $(LIB_PATH)libft_malloc.so
CFLAGS += -I$(LIB_PATH)/incs
LDFLAGS += -L $(LIB_PATH)


all: $(NAME)


$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJ): $(INC) | $(OBJ_PATH)
$(OBJ): $(OBJ_PATH)/%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

$(OBJ_PATH):
	mkdir -p $@

$(LIB):
	make -C $(LIB_PATH)

clean:
	$(RM) $(OBJ_PATH)
	make -C $(LIB_PATH) clean

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re