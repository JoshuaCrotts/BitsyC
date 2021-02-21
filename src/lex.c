#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/data.h"
#include "../include/defs.h"

int32_t lex(struct token_s *t);
static int32_t skip(void);
static int32_t next(void);
static int32_t parse_int(int32_t);
static int32_t digit_char_pos(char *s, int32_t ch);
static void putback_char(int32_t ch);

/**
 * Scan and return the next token found in input.
 * Returns 1 for a valid token, 0 if no tokens are left.
 * 
 * @param struct token_s * pointer to token.
 * 
 * @return 1 for valid token, 0 for no tokens left.
 */
int32_t 
lex(struct token_s *t) {
  int32_t ch;

  // Skip whitespace chars.
  ch = skip();

  // Determine token type based on input char.
  switch(ch) {
    case EOF: return 0;
    case '+':
      t->token = T_PLUS;
      break;
    case '-':
      t->token = T_MINUS;
      break;
    case '*':
      t->token = T_STAR;
    case '/':
      t->token = T_SLASH;
      break;
    default:
      // If it's a digit, then we need to scan
      // the literal integer value.
      if (isdigit(ch)) {
        t->int_value = parse_int(ch);
        t->token = T_INTLIT;
        break;
      }

      printf("Unrecognized character %c on line %d.\n", ch, line_count);
      exit(EXIT_FAILURE);
  }

  return 1;
}

/**
 * Scans and returns an integer literal 
 * value from the input file. 
 *
 * @param int32_t first digit in the number.
 */
static int32_t
parse_int(int32_t d) {
  int32_t kpos;
  int32_t value = 0;

  while ((kpos = digit_char_pos("0123456789", d)) >= 0) {
    value = value * 10 + kpos;
    d = next();
  }
  
  // Once we're out, we run into a non-integer char
  // so we need to put it back into the input stream.
  putback_char(d);
  return value;
}

/**
 * Checks to see if the int32_t char is inside 
 * the passed string.
 * 
 * @param char * string to check.
 * @param int32_t character to search for.
 * 
 * @return int32_t location of char in string, or -1 if not found.
 */
static int32_t 
digit_char_pos( char *s, int32_t ch) {
  char *p;
  p = strchr(s, ch);
  return p ? p - s : -1;
}

/**
 * Skips whitespace characters that we do not need to tokenize.
 * 
 * @param void.
 * 
 * @return next non-whitespace token.
 */
static int32_t 
skip(void) {
  int32_t ch;

  ch = next();

  while (' ' == ch || '\t' == ch || '\n' == ch || '\r' == ch || '\f' == ch) {
    ch = next();
  }

  return ch;

}

/**
 * Stores a character back in the input stream.
 * 
 * @param int32_t character to store.
 * 
 * @return void.
 */
static void 
putback_char(int32_t ch) {
  putback = ch;
}

/**
 * Reads the next character from the input file.
 * 
 * @param void.
 * 
 * @return int32_t character.
 */
static int32_t 
next(void) {
  int32_t ch;

  // Use the character putback
  // if one exists.
  if (putback) {
    ch = putback;
    putback = 0;
    return ch;
  }

  // Read from input file.
  ch = fgetc(infile);
  if ('\n' == ch) {
    line_count++;
  }

  col_count++;
  return ch;
}