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

long* cs1010_read_long_array(long how_many);
double* cs1010_read_double_array(long how_many);
char** cs1010_read_line_array(long how_many);
char** cs1010_read_word_array(long how_many);

void cs1010_println_double(double d);
void cs1010_println_long(long d);
void cs1010_println_string(char *s);

void cs1010_print_double(double d);
void cs1010_print_long(long d);
void cs1010_print_string(char *s);

void cs1010_clear_screen();

#endif 
