${license}

#include "Latex/token.h"
#include "generated/tokens.gen.h"
const char_t LATEX_TERMINALS[] = {
  ${terminals}
};

const char_t * LATEX_TERMINAL_STRINGS[] = {
  ${strings}
};

const uint32_t LATEX_TERMINAL_STRING_LENS[] = {
  ${string_lens}
};

const int32_t N_LATEX_TERMINAL = sizeof(LATEX_TERMINALS);
