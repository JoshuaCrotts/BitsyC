#ifndef DEFS_H
#define DEFS_H

#include <stdint.h>

// Token structure.
struct token_s {
  int32_t token;
  int32_t int_value;
};

// Token types.
enum {
  T_PLUS, T_MINUS, T_STAR, T_SLASH, T_INTLIT
} TOKEN_TYPE;

#endif // DEFS_H