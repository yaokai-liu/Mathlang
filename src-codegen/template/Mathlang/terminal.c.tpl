${license}

#include "Mathlang/token.h"
#include "generated/tokens.gen.h"
const char_t MATHLANG_TERMINALS[] = {
  ${terminals}
};

const char_t * MATHLANG_TERMINAL_STRINGS[] = {
  ${strings}
};

const uint32_t MATHLANG_TERMINAL_STRING_LENS[] = {
  ${string_lens}
};

const int32_t N_MATHLANG_TERMINAL = sizeof(MATHLANG_TERMINALS);
