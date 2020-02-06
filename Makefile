ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
LINK = libft_malloc.so
CC = gcc
RM = rm -rf

INC_PATH += ./incs

INC_NAME += align.h
INC_NAME += arena.h
INC_NAME += chunk.h
INC_NAME += config.h
INC_NAME += debug.h
INC_NAME += heap.h
INC_NAME += malloc.h
INC_NAME += memory.h

CFLAGS = -Wall -Werror -Wextra
INC = $(addprefix $(INC_PATH)/,$(INC_NAME))

CPPFLAGS = $(addprefix -I,$(INC_PATH))

SRC_PATH = srcs

SRC_SUB += malloc
SRC_NAME += malloc.c
SRC_NAME += free.c
SRC_NAME += calloc.c
SRC_NAME += valloc.c
SRC_NAME += realloc.c
SRC_NAME += reallocf.c
SRC_NAME += show_alloc_mem.c

SRC_SUB += shared
SRC_NAME += align.c
SRC_NAME += arena.c
SRC_NAME += chunk.c
SRC_NAME += config.c
SRC_NAME += heap.c
SRC_NAME += memory.c

SRC_SUB += debug
SRC_NAME += print_number.c
SRC_NAME += print_string.c
SRC_NAME += print_heap.c

SRC_SUB += libc
SRC_NAME += ft_bzero.c
SRC_NAME += ft_memcpy.c
SRC_NAME += ft_memmove.c
SRC_NAME += ft_memset.c

vpath %.c $(addprefix $(SRC_PATH)/, $(SRC_SUB))

OBJ_PATH = obj
OBJ_NAME = $(SRC_NAME:%.c=%.o)
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME)) 

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	REPLACE := ./run.sh ./test
else 
	REPLACE := LD_PRELOAD=./libft_malloc.so LD_LIBRARY_PATH=. ./test
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
	$(REPLACE)

.PHONY: all clean fclean re test