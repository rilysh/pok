FLAGS = -Wall -Wextra
PROG = pok

all: ${CC} ${FLAGS} ${PROG}.c -o ${PROG}
clean: rm -f ${PROG}
