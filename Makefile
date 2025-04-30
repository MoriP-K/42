NAME := minishell

CC := cc -fsanitize=address

CPPFLAGS := -I./includes -I./src/libft

CFLAGS := -Wall -Wextra -Werror

LDFLAGS := -L./src/libft

LDLIBS := -lft

LIBFTDIR := ./src/libft

LIBFT := $(LIBFTDIR)/libft.a

RLFLAGS := -lreadline

SRC := main.c \
	lexer.c lexer_utils.c expander.c expander_utils.c culling_space.c \
	split_meta.c integrate_quotes.c combine_quotes.c quotes_checker.c \
	parser.c allocate_parse.c allocate_parse_2.c parser_utils.c \
	pipe.c pipe_2.c fd.c close_fd.c cmd_path.c cmd_path_2.c \
	free.c free2.c utils.c ms.c ms_2.c\
	heredoc.c heredoc_signal.c \
	init.c init_2.c \
	pwd.c envi.c export.c export_utils.c unset.c echo.c cd.c exit.c \
	export_sort.c cd_pwd_changer.c \
	env.c syntax_error_handler.c signal_handler.c \

OBJDIR := ./obj

OBJ := $(SRC:%.c=$(OBJDIR)/%.o)

vpath %.c ./src: \
./src/env: \
./src/executer: \
./src/lexer: \
./src/parser: \
./src/executer: \
./src/executer/heredoc: \
./src/executer/fd: \
./src/free: \
./src/initialize: \
./src/builtins: \
./src/utils: \
./lexer: \
./parser: \

ifeq ($(DEBUG), true)
	CFLAGS += -g3
endif

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $^ -o $@ $(RLFLAGS) $(LDFLAGS) $(LDLIBS)

$(OBJDIR)/%.o:%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $< -c -o $@ $(CPPFLAGS)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(warning obj=$(OBJDIR))

clean:
	$(RM) -r $(OBJ) $(OBJDIR)
	$(MAKE) -C $(LIBFTDIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean

re: fclean
	$(MAKE) all

rr:
	$(MAKE) re && $(MAKE) clean

d: clean
	$(MAKE) DEBUG=true

.PHONY: all clean fclean re rr d 