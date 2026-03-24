${license}

#ifndef LATEX_ACTION_TABLE_GEN_H
#define LATEX_ACTION_TABLE_GEN_H

#include <stdint.h>

enum LATEX_STATE_ENUM {
  LATEX_BAD_STATE = 0,
  ${state_enum}
};

const struct grammar_action *getParseAction(uint32_t index, uint32_t ahead);

uint32_t parseJumpState(uint32_t index, uint32_t current);

uint32_t getParseStateCurrentTokenType(int32_t state);

#endif  // LATEX_ACTION_TABLE_GEN_H