#ifndef DATA_H
#define DATA_H

#include <stdint.h>
#include <stdio.h>

#ifndef extern_
  #define extern_ extern
#endif 

extern_ int32_t line_count;
extern_ int32_t col_count;
extern_ int32_t putback;
extern_ FILE    *infile;

#endif // DATA_H