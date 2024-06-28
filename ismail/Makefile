# ----------------------------------- PARAMS -----------------------------------

NAME	=	minishell
INC_DIR	=	src
SRC_DIR	=	src
OBJ_DIR	=	obj
INC	  	=	$(addprefix $(INC_DIR)/,	minishell.h)

#SRC	  	=	$(shell find $(SRC_DIR) -name "*.c")
SRC	  	=	$(addprefix $(SRC_DIR)/, \
	debug/debug.c \
	execution/builtin_cd.c \
	execution/builtin_echo.c \
	execution/builtin_env.c \
	execution/builtin_exit.c \
	execution/builtin_export.c \
	execution/builtin_pwd.c \
	execution/builtin_unset.c \
	execution/builtins.c \
	execution/commands.c \
	execution/commands2.c \
	execution/execute.c \
	execution/redirections.c \
	parsing/combine_str_tokens.c \
	parsing/expand_var.c \
	parsing/heredoc.c \
	parsing/parse.c \
	parsing/syntax_errors.c \
	parsing/tokenize.c \
	parsing/tokenize2.c \
	parsing/utils.c \
	system/signals.c \
	utils/cleanup.c \
	utils/env.c \
	utils/error.c \
	utils/exit.c \
	utils/file.c \
	utils/process.c \
	utils/utils.c \
	main.c \
)

OBJ		=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFTA	=	./lib/libft/libft.a

CFLAGS	=	-Wall -Wextra -Werror
CINC	=	-I$(INC_DIR) -I./lib/libft
LFLAGS	=
LLIB	=	-L./lib/libft -lft -lreadline

GDB		=	gdb -tui --args
VG		=	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes

ifeq ($(DEBUG), 1)
CFLAGS	+= -fsanitize=address -g3
LFLAGS	+= -fsanitize=address -g3
endif


# ----------------------------------- RULES ------------------------------------

all: libft $(NAME)

# Note: Libs should be after objs for obscure reasons.
$(NAME): $(OBJ) $(LIBFTA)
	$(CC) $(LFLAGS) $(OBJ) $(LLIB) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC) Makefile
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CINC) -c $< -o $@

libft:
	make -C ./lib/libft

re: fclean all

clean:
	rm -rf $(OBJ_DIR)
	make -C ./lib/libft clean

fclean: clean
	$(RM) $(NAME)
	make -C ./lib/libft fclean

errors:
	make >/dev/null

run:
	@clear
	@make -s re
	@./$(NAME)

debug:
	@clear
	@make -s re DEBUG=1
	@./$(NAME)

vg:
	@make -s re CFLAGS+=-g
	@$(VG) ./$(NAME) $(ARGS)

gdb:
	@make -s re CFLAGS+=-g
	@$(GDB) ./$(NAME) $(ARGS)

gprof:
	@make -s re CFLAGS+=-pg LFLAGS+=-pg
	@./$(NAME) $(ARGS)
	@gprof ./$(NAME) gmon.out

print:
	@echo "\n-------------------- FILES --------------------\n"
	@echo "NAME		$(NAME:%=\n%)\n"
	@echo "INC		$(INC:%=\n%)\n"
	@echo "SRC		$(SRC:%=\n%)\n"
	@echo "OBJ		$(OBJ:%=\n%)\n"
	@echo "\n-------------------- FLAGS --------------------\n"
	@echo "CFLAGS	$(CFLAGS:%=\n%)\n"
	@echo "CINC		$(CINC:%=\n%)\n"
	@echo "LFLAGS	$(LFLAGS:%=\n%)\n"
	@echo "LLIB		$(LLIB:%=\n%)\n"

.PHONY: all libft re clean fclean run vg gdb lldb gprof print
