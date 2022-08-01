CC=clang
AR=ar
CFLAGS=-c @compile_flags.txt -Iinclude
LIB=lib/libcs1010.a
INCLUDE=include/cs1010.h
DESTDIR?=/usr/local
$(LIB): src/cs1010.o
	mkdir -p lib
	$(AR) r $(LIB) src/cs1010.o

install: $(LIB) $(INCLUDE)
	install -d $(DESTDIR)/lib/
	install -m 644 $(LIB) $(DESTDIR)/lib/
	install -d $(DESTDIR)/include/
	install -m 644 $(INCLUDE) $(DESTDIR)/include/

clean:
	rm -f $(LIB) src/cs1010.o

test:
	$(CC) -o test/1010test src/test.c -Iinclude -Llib -lcs1010
	! { test/1010test < test/input 2>&1 | grep "test failed"; } || { echo "One or more test(s) failed"; false; }

.PHONY: install clean test

# vim:set noexpandtab
