NAME = libasm.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs

# assembler (use nasm for intel syntax)
ASM = nasm
ASMFLAGS = -f elf64

# mandatory sources
SRCS = ft_strcpy.s \
	ft_strlen.s \
	ft_strcmp.s \
	ft_write.s \
	ft_read.s \
	ft_strdup.s

# bonus sources
BONUS_SRCS = ft_list_size_bonus.s \
	ft_list_push_front_bonus.s \
	ft_list_sort_bonus.s \
	ft_list_remove_if_bonus.s \
	ft_atoi_base_bonus.s

OBJS = $(SRCS:.s=.o)
BONUS_OBJS = $(BONUS_SRCS:.s=.o)

# mandatory test
TEST = test.out
TEST_SRC = main.c

# bonus test
BONUS_TEST = test_bonus.out
BONUS_TEST_SRC = main_bonus.c

all: $(NAME)

# build library with only mandatory objects
$(NAME): $(OBJS)
	$(AR) $(NAME) $^

# build library including bonus objects (recreate archive with bonus objs)
bonus: $(OBJS) $(BONUS_OBJS)
	$(AR) $(NAME) $^

test: $(TEST)

# test linking against current library (mandatory)
$(TEST): $(TEST_SRC) $(NAME)
	$(CC) $(CFLAGS) $(TEST_SRC) $(NAME) -o $(TEST)

test_bonus: $(BONUS_TEST)

# bonus test: ensure bonus archive objects are present first
$(BONUS_TEST): $(BONUS_TEST_SRC) bonus
	$(CC) $(CFLAGS) $(BONUS_TEST_SRC) $(NAME) -o $(BONUS_TEST)

# generic rule to assemble .s to .o using nasm
%.o: %.s
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	@rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	@rm -f $(NAME) $(TEST) $(BONUS_TEST)

re: fclean all

.PHONY: all bonus clean fclean re test test_bonus
