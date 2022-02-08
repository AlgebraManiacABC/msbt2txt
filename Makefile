CC=gcc
CFLAGS=-Wall -Werror -lm -std=c11

SDIR=src
SRCS:=${wildcard src/*.c}
#All c files in the src/ directory
ODIR=build
OBJS:=${patsubst ${SDIR}/%, ${ODIR}/%, ${SRCS:%.c=%.o}}
#All object files that are named the same as c files, but in obj/
LDIR=lib
LIBS:=${filter-out ${LDIR}/main.h, ${patsubst ${SDIR}/%, ${LDIR}/%, ${SRCS:%.c=%.h}}}
#All header files that are named the same as c files, but in lib/

msbt2txt: ${OBJS}
	${CC} $^ -o $@ -I ${LDIR} ${CFLAGS}

${ODIR}/%.o: ${SDIR}/%.c ${LIBS}
	${CC} -c ${filter-out %.h,$^} -I ${LDIR} -o $@ ${CFLAGS}

clean:
	rm ./build/*.o
	rm ./msbt2txt