#define extern_
#include "../include/data.h"
#include "../include/defs.h"
#include "../include/lex.h"

#undef extern_

static char *token_str[] = {"+", "-", "*", "/", "INTLIT"};

static void 
scan_file(void) {
  struct token_s t;
  while (lex(&t)) {
    printf("<%d, %d:%d=", t.token, line_count + 1, col_count);
    if (t.token == T_INTLIT) {
      printf("\'%d\',INTLIT", t.int_value);
    } else {
      printf("\'%s\'", token_str[t.token]);
    }
    printf(">\n");
  }
}

int
main(int argc, char *argv[]) {
  infile = fopen(argv[1], "r");
  scan_file();
  return 0;
}