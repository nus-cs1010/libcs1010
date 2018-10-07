#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 32
static
int skip_space() {
  int c;
  do {
    c = fgetc(stdin);
  } while (isspace(c) && c != EOF);
  return c;
}

static
int fill_buffer(char *buf, int len) {
  int c;
  int i = 0;
  while (1) {
    c = fgetc(stdin);
    if (c == EOF || isspace(c)) {
      buf[i] = 0;
      return i + 1;
    }
    buf[i] = c;
    i = i + 1;

    if (i == len) {
      return i;
    }
  }
}

/**
 * @brief Read and return a string from standard input (until
 * we reach a spa
 *
 * @return The string read if successful.  The caller is
 * responsible for freeing the memory allocated to the string.
 * Return NULL if an error is encountered when reading.
 *
 * @note Based on FIO20-C. Avoid unintentional truncation when
 * using fgets() or fgetws()
 * https://wiki.sei.cmu.edu/
 */
char* cs1010_read_word()
{
  char buf[BUF_SIZE];
  char *ret = malloc(1);
  size_t total_len = 1;
  int len;

  int c = skip_space();
  if (c == EOF) {
    free(ret);
    printf("EOF encountered.  return NULL\n");
    return NULL;
  }
  *ret = c;

  do {
    len = fill_buffer(buf, BUF_SIZE);
    char *temp = realloc(ret, total_len + len + 1);
    if (temp == NULL) {
      free(ret);
      return NULL;
    }
    ret = temp;
    memcpy(ret + total_len, buf, len); // concat the string
    total_len += len;
  } while (len == BUF_SIZE && buf[len-1] != 0);
  return ret;
}

/**
 * @brief Read and return a long int from standard input.
 *
 * @details Based on INT05-C from SEI CERT C Coding Standard
 * https://wiki.sei.cmu.edu/
 *
 * @return the value read if successful.  Return LONG_MAX
 * with an error message printed if an error occured.
 */

long cs1010_read_long()
{
  char *buff;
  char *end_ptr;
  long number;

  buff = cs1010_read_word();
  if (buff == NULL) {
    fprintf(stderr, "cs1010_read_long: EOF or read error\n");
    return LONG_MAX;
  }
  errno = 0;

  number = strtol(buff, &end_ptr, 10);

  if (ERANGE == errno) {
    fprintf(stderr, "cs1010_read_long: number '%s' out of range\n", buff);
    free(buff);
    return LONG_MAX;
  }
  if (end_ptr == buff) {
    fprintf(stderr, "cs1010_read_long: '%s' is not a valid numeric input\n", buff);
    free(buff);
    return LONG_MAX;
  }
  if ('\n' != *end_ptr && '\0' != *end_ptr) {
    fprintf(stderr, "cs1010_read_long: reach the end without null/newline. '%s' remains\n", end_ptr);
    free(buff);
    return LONG_MAX;
  }
  free(buff);
  return number;
}

/**
 * @brief Read and return a string from standard input (until
 * we reach the new line.)
 *
 * @return the string read if successful.  The caller is
 * responsible for freeing the memory allocated to the string.
 * Return NULL if an error is encountered when reading.
 *
 * @note See FIO20-C. Avoid unintentional truncation when using fgets() or fgetws()
 * https://wiki.sei.cmu.edu/
 */
char* cs1010_read_line()
{
  char* buf = NULL;
  size_t dummy = 0;
  if (getline(&buf, &dummy, stdin) == -1) {
    fprintf(stderr, "cs1010_read_line: unable to read line into buffer\n");
    return NULL;
  }
  return buf;
}

/**
 * @brief Read and return a double from standard input.
 *
 * @return the value read if successful.  Return DOUBLE_MAX
 * with an error message printed if an error occured.
 */
double cs1010_read_double()
{
  char *buff;
  char *end_ptr;
  double number;

  buff = cs1010_read_word();
  if (buff == NULL) {
    fprintf(stderr, "cs1010_read_double: EOF or read error\n");
    return DBL_MAX;
  }
  errno = 0;

  number = strtod(buff, &end_ptr);

  if (ERANGE == errno) {
    fprintf(stderr, "cs1010_read_double: number '%s' out of range\n", buff);
    return DBL_MAX;
  }
  if (end_ptr == buff) {
    fprintf(stderr, "cs1010_read_double: '%s' is not a valid numeric input\n", buff);
    return DBL_MAX;
  }
  if ('\n' != *end_ptr && '\0' != *end_ptr) {
    fprintf(stderr, "cs1010_read_double: reach the end without null/newline. '%s' remains\n", buff);
    return DBL_MAX;
  }
  return number;
}

/**
 * @brief Read and return multiple long int from standard
 * input into an array.
 *
 * @return The array read if successful.  The caller is responsible
 * for freeing the array.  Return NULL if an error occured.
 */

long* cs1010_read_long_array(int how_many)
{
  long *buffer = calloc(how_many, sizeof(long));
  if (buffer == NULL) {
    return NULL;
  }

  for (int i = 0; i < how_many; i = i + 1) {
    buffer[i] = cs1010_read_long();
  }

  return buffer;
}

/**
 * @brief Read and return multiple double from standard
 * input into an array.
 *
 * @return The array read if successful.  The caller is responsible
 * for freeing the array.  Return NULL if an error occured.
 */
double* cs1010_read_double_array(int how_many)
{
  double *buffer = calloc(how_many, sizeof(double));
  if (buffer == NULL) {
    return NULL;
  }

  for (int i = 0; i < how_many; i = i + 1) {
    buffer[i] = cs1010_read_double();
  }

  return buffer;
}

/**
 * @brief Read and return multiple lines from standard
 * input into an array.
 *
 * @return The array read if successful.  The caller is responsible
 * for freeing the array and each string in the array.  Return NULL
 * if an error occured.
 */
char** cs1010_read_line_array(int how_many)
{
  char **buffer = calloc(how_many, sizeof(char*));
  if (buffer == NULL) {
    return NULL;
  }

  for (int i = 0; i < how_many; i = i + 1) {
    buffer[i] = cs1010_read_line();
  }

  return buffer;
}

/**
 * @brief Read and return multiple space-delimited words
 * from standard input into an array.
 *
 * @return The array read if successful.  The caller is
 * responsible for freeing the array and each string in
 * the array.  Return NULL if an error occured.
 */
char** cs1010_read_word_array(int how_many)
{
  char **buffer = calloc(how_many, sizeof(char*));
  if (buffer == NULL) {
    return NULL;
  }

  for (int i = 0; i < how_many; i = i + 1) {
    buffer[i] = cs1010_read_word();
  }

  return buffer;
}

/**
 * @brief Print a double to standard output with format %.4f.
 *
 * @return None
 */
void cs1010_print_double(double d)
{
  printf("%.4f", d);
}

/**
 * @brief Print a long to standard output with format %.4f.
 *
 * @return None
 */
void cs1010_print_long(long d)
{
  printf("%ld", d);
}

/**
 * @brief Print a double to standard output with format %.4f,
 * followed by a newline.
 *
 * @return None
 */
void cs1010_println_double(double d)
{
  cs1010_print_double(d);
  printf("\n");
}

/**
 * @brief Print a long to standard output with format %.4f, followed by a newline.
 *
 * @return None
 */
void cs1010_println_long(long d)
{
  cs1010_print_long(d);
  printf("\n");
}

/**
 * @brief Print a string to standard output.
 *
 * @return None
 */
void cs1010_print_string(char *s)
{
  printf("%s", s);
}

/**
 * @brief Print a string to standard output, followed by a newline.
 *
 * @return None
 */
void cs1010_println_string(char *s)
{
  printf("%s\n", s);
}
