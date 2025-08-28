.PHONY: clean all benchmark

R ?= "8192"
C ?= "8192"

CFLAGS=-std=c99 -O3 -Wall -Werror $(O4_FLAGS) -pedantic -DR=${R} -DC=${C}
CC ?= gcc

TARGETS=transpose co-transpose

all: ${TARGETS}

clean:
	rm -f ${TARGETS}

benchmark: ${TARGETS}
	hyperfine -i $(addprefix ./, $^)

${TARGETS}:
	${CC} $@.c ${CFLAGS} -o $@

