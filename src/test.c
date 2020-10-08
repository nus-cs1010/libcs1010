#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include "cs1010.h"

#define DOUBLE_COMPARE_THRESHOLD 0.000001

/*
 * Input file contains:
10
-10
abc
1.0
10.0
-10.0
abc
hello Hello
world !
00000000000000000000000000000000000000000000000000000000000000000
1111111111 1111111111
0 1 2 3 4 5 6 7 8 9 10
1.1 2.1 3.1 4.1 5.1 6.1 7.1 8.1 9.1 10.1
abc def ghi  jkl  mno 
pqr stu vwx yz  012
*/
int main() {
 /* Test: cs1010_read_long
  * 10
  * -10
  * abc
  * 1.0
  */
 long x = cs1010_read_long();
 if (x != 10) {
  fprintf(stderr, "test failed: Read 10\n");
 }
 x = cs1010_read_long();
 if (x != -10) {
  fprintf(stderr, "test failed: Read -10\n");
 }
 x = cs1010_read_long();
 if (x != LONG_MAX) {
  fprintf(stderr, "test failed: Didn't return error for abc\n");
 }
 x = cs1010_read_long();
 if (x != LONG_MAX) {
  fprintf(stderr, "test failed: Didn't return error for 1.0\n");
 }

 /* Test: cs1010_read_double
  * 10.0
  * -10.0
  * abc
  */
 double f = cs1010_read_double();
 if (fabs(f - 10.0) > DOUBLE_COMPARE_THRESHOLD) {
  fprintf(stderr, "test failed: Read 10.0\n");
 }
 f = cs1010_read_double();
 if (fabs(f + 10.0) > DOUBLE_COMPARE_THRESHOLD) {
  fprintf(stderr, "test failed: Read -10.0\n");
 }
 f = cs1010_read_double();
 if (f != DBL_MAX) {
  fprintf(stderr, "test failed: Didn't return error for abc\n");
 }

 /* Test: cs1010_read_word
  * hello Hello
  * world !
  */
 char* word = cs1010_read_word();
 if (strcmp(word, "hello") != 0) {
  fprintf(stderr, "test failed: Read hello. Read '%s' instead\n", word);
 }
 word = cs1010_read_word();
 if (strcmp(word, "Hello") != 0) {
  fprintf(stderr, "test failed: Read Hello. Read '%s' instead\n", word);
 }
 word = cs1010_read_word();
 if (strcmp(word, "world") != 0) {
  fprintf(stderr, "test failed: Read world\n");
 }
 word = cs1010_read_word();
 if (strcmp(word, "!") != 0) {
  fprintf(stderr, "test failed: Read !\n");
 }

 /* Test: cs1010_read_line */
 char* line = cs1010_read_line();
 if (strcmp(line, "00000000000000000000000000000000000000000000000000000000000000000\n") != 0) {
  fprintf(stderr, "test failed: Read a line. Read '%s' instead\n", line);
 }

 /* Test: cs1010_read_line */
 line = cs1010_read_line();
 if (strcmp(line, "1111111111 1111111111\n") != 0) {
  fprintf(stderr, "test failed: Read a line. Read '%s' instead\n", line);
 }


 /* Test: cs1010_read_long_array */
 long* longs = cs1010_read_long_array(10);
 for (int i = 0; i < 10; i = i + 1) {
  if (longs[i] != i) {
   fprintf(stderr, "test failed: Read long array (%ld)\n", longs[i]);
  }
 }
 free(longs);

 /* Test: cs1010_read_double_array */
 double* doubles = cs1010_read_double_array(10);
 double d = 1.1;
 for (int i = 0; i < 10; i = i + 1) {
  if (fabs(doubles[i] - d) > DOUBLE_COMPARE_THRESHOLD) {
   fprintf(stderr, "test failed: Read double array (%f) \n", doubles[i]);
  }
  d += 1.1;
 }
 free(doubles);

 /* Test: cs1010_read_word_array */
 char** words = cs1010_read_word_array(10);
 char* ground_truth[10] = {
  "abc", "def", "ghi", "jkl", "mno", "pqr", "stu", "vwx", "yz", "012"
 };
 for (int i = 0; i < 10; i = i + 1) {
  if (strcmp(words[i], ground_truth[i]) != 0) {
   fprintf(stderr, "test failed: Read word array (%s) \n", words[i]);
  }
 }
 free(words);

 /* Test: cs1010_read_line_array */
 words = cs1010_read_line_array(10);
 char* ground_truth2[10] = {
  "abc\n", "def\n", "ghi\n", "jkl\n", "mno\n", "pqr\n", "stu\n", "vwx\n", "yz \n", "012\n"
 };
 for (int i = 0; i < 10; i = i + 1) {
  if (strcmp(words[i], ground_truth2[i]) != 0) {
   fprintf(stderr, "test failed: Read line array. Read '%s' instead\n", words[i]);
  }
 }
 free(words);
}
