CC=clang
AR=ar
CFLAGS=-c -Iinclude
LIB=lib/libcs1010.a
$(LIB): src/cs1010.o
	$(AR) r $(LIB) src/cs1010.o

#vim:set noexpandtab
