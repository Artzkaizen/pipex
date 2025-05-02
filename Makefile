# Project name
NAME            := pipex

# Directories
INC_DIR         := includes
SRC_DIR         := src
OBJ_DIR         := obj
TEST_DIR        := test
TEST_OBJ_DIR    := test/obj

# Source files
SRCS            := rethink.c \
				   utils.c \
				   ft_split.c \
				   ft_lst.c \
				   pipex.c \
				   find_path.c

SRCS		:= $(SRCS:%=$(SRC_DIR)/%)
OBJS		:= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Compiler and flags
CC              := cc
CFLAGS          := -Wall -Wextra -Werror -I $(INC_DIR)
DEBUG           := -g3


# Clean command
RM              := rm -f

all: $(NAME)

algo: $(NAME)
	./$(NAME) $(ARGS)
# Run tests
test: $(TARGET)
	./$(TARGET)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(DEBUG) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

# Full clean (remove object files and static library)
fclean: clean
	$(RM) $(NAME)

# Rebuild the project
re: fclean all

# Phony targets
.PHONY: clean fclean re
