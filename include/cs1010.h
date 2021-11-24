#ifndef CS1010_H
#define CS1010_H

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

long cs1010_read_long(void);
double cs1010_read_double(void);
char* cs1010_read_line(void);
char* cs1010_read_word(void);
size_t cs1010_read_size_t(void);

long* cs1010_read_long_array(size_t how_many);
double* cs1010_read_double_array(size_t how_many);
char** cs1010_read_line_array(size_t how_many);
char** cs1010_read_word_array(size_t how_many);

void cs1010_println_double(double d);
void cs1010_println_long(long d);
void cs1010_println_string(char *s);
void cs1010_println_pointer(void *p);
void cs1010_println_size_t(size_t d);

void cs1010_print_double(double d);
void cs1010_print_long(long d);
void cs1010_print_string(char *s);
void cs1010_print_pointer(void *p);
void cs1010_print_size_t(size_t d);

void cs1010_clear_screen(void);

#endif 
