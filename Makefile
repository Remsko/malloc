ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
LINK = libft_malloc.so
CC = gcc
RM = rm -rf

INC_PATH += ./incs

INC_NAME += malloc.h
INC_NAME += arena.h
INC_NAME += heap.h
INC_NAME += chunk.h

CFLAGS = -Wall -Werror -Wextra
INC = $(addprefix $(INC_PATH)/,$(INC_NAME))

CPPFLAGS = $(addprefix -I,$(INC_PATH))

SRC_PATH = srcs/

SRC_SUB += malloc
SRC_NAME += malloc.c
SRC_NAME += free.c

SRC_SUB += shared
SRC_NAME += align.c
SRC_NAME += arena.c
SRC_NAME += chunk.c
SRC_NAME += config.c
SRC_NAME += heap.c


vpath %.c $(addprefix $(SRC_PATH)/, $(SRC_SUB))

OBJ_PATH = obj
OBJ_NAME = $(SRC_NAME:%.c=%.o)
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME)) 

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	REPLACE := ./run.sh ./test
else 
	REPLACE := LD_PRELOAD=./$(LINK) ./test
endif

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $^ -shared  -o $@
	ln -sf $(NAME) $(LINK)

$(OBJ): $(INC) | $(OBJ_PATH)
$(OBJ): $(OBJ_PATH)/%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c -fPIC $<

$(OBJ_PATH):
	mkdir -p $@

clean:
	$(RM) $(OBJ_PATH)

fclean: clean
	make fclean -C tests
	$(RM) $(NAME) $(LINK)

re: fclean all

test: $(NAME)
	make re -C tests
	mv ./tests/test .
	LD_PRELOAD=./$(LINK) ./test

.PHONY: all clean fclean re test