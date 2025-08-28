.PHONY: clean all benchmark

BITS ?= "24"
SEARCH ?= "25000000"

CFLAGS=-std=c99 -O3 -Wall -Werror $(O4_FLAGS) -pedantic -DBITS=${BITS} -DSEARCH=${SEARCH}
CC ?= gcc

TARGETS=bin-tree vebl-tree

all: ${TARGETS}

clean:
	rm -f ${TARGETS}

benchmark: ${TARGETS}
	hyperfine -i $(addprefix ./, $^)

${TARGETS}:
	${CC} $@.c ${CFLAGS} -o $@


