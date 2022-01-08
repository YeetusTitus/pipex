SRCS = cat_utils.c cat.c complete.c core.c error.c parse_utils.c parse.c split.c utils.c utils2.c

MAIN = main.c

DIRECTORYS = srcrs/

SRCSD =	$(addprefix ${DIRECTORYS}, $(SRCS))

EFLAGS = -Wall -Wextra -Werror

OBJS =	${SRCSD:.c=.o}

BONUS = parse_bonus.c utils_bonus.c

BONUSMAIN = main_bonus.c

BONUSDIRECTORY = bonus/

BONUSD = $(addprefix ${BONUSDIRECTORY}, $(BONUS))

BONUSOBJS =	${BONUSD:.c=.o}

HEADER = bonus/pipex_bonus.h

OFLAGS = -c

NAME   = pipex

%.o: %.c ${HEADER}
	gcc ${OFLAGS} ${EFLAGS} -o $@ $<

${NAME}: ${OBJS}
	gcc $(EFLAGS) -o $(NAME) $(MAIN) ${SRCSD}
			
all:	${NAME}

clean:
		rm  -f ${OBJS}

fclean:	clean
		rm  -f ${NAME}

re:		fclean all

bonus: ${OBJS} ${BONUSOBJS}
		gcc $(EFLAGS) -o $(NAME) ${SRCSD} ${BONUSD} $(BONUSMAIN)

cleanbonus:
			rm -f ${OBJS} ${BONUSOBJS}

.PHONY:	all clean fclean re bonus cleanbonus