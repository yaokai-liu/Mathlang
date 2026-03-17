${license}

#ifndef MATHLANG_TOKENS_H
#define MATHLANG_TOKENS_H

#include "Mathlang/char_t.h"
#include <stdint.h>

enum TOKEN_TYPE_ENUM: uint32_t {
  ${enums},
  MATHLANG_TOKEN_PLACE_HOLDER,
  MATHLANG_MAX_TOTAL_TOKEN,
  MATHLANG_TOKEN_BAD_TOKEN = UINT32_MAX
};
extern const char_t *TOKEN_NAMES[];
#endif  // MATHLANG_TOKENS_H
