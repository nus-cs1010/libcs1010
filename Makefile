CC=clang
AR=ar
CFLAGS=-c @compile_flags.txt -Iinclude
LIB=lib/libcs1010.a
$(LIB): src/cs1010.o
	mkdir -p lib
	$(AR) r $(LIB) src/cs1010.o

test:
	$(CC) -o 1010test src/test.c -Iinclude -Llib -lcs1010
# vim:set noexpandtab
