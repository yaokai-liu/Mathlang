/* License
 *
 * Mathlang - A Practical Language for Mathematics
 * Copyright (C) 2026 Yaokai Liu
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 *
 * Project Name: Mathlang
 * Module Name: grammar/tokenize
 * Filename: tokenize.c
 * Creator: Yaokai Liu
 * Create Date: 2026-03-21
 * Copyright (c) 2026 Yaokai Liu. All rights reserved.
 **/

#include "tokenize.h"
#include "generated/tokens.gen.h"
#include "number.h"
#include "string_t.h"
#include "enum.h"

#define lenof(str_literal) ((sizeof str_literal) - 1)
#define max(a, b)          ((a) > (b) ? (a) : (b))
#define min(a, b)          ((a) < (b) ? (a) : (b))

#define startswithLetter(pText)   (('a' <= *(pText) && *(pText) <= 'z') || ('A' <= *(pText) && *(pText) <= 'Z'))

#define isLatexHeader(pText)      ( *(pText) == '\\' || startswithLetter(pText))
#define isIdentChar(pText)        (startswithLetter(pText) || isDecDigital(pText) || (*(pText) == '-'))
#define isHexLetter(pText)        (('a' <= *(pText) && *(pText) <= 'f') || ('A' <= *(pText) && *(pText) <= 'F'))
#define isSign(pText)             ((*(pText) == '-') || (*(pText) == '+'))
#define isBinDigital(pText)       ('0' == *(pText) || *(pText) == '1')
#define isOctDigital(pText)       ('0' <= *(pText) && *(pText) <= '7')
#define isDecDigital(pText)       ('0' <= *(pText) && *(pText) <= '9')
#define isHexDigital(pText)       (isDecDigital(pText) || isHexLetter(pText))

static uint32_t t_IDENTIFIER(const char_t *input, Token *result, const Allocator *allocator);
static uint32_t t_NUMBER(const char_t *input, Token *result, const Allocator *allocator);

static uint32_t try_keyword_Axiom(const char_t *input, uint32_t offs, Token *result, const Allocator *allocator);
static uint32_t try_keyword_Assumption(const char_t *input, uint32_t offs, Token *result, const Allocator *allocator);
static uint32_t try_keyword_Convention(const char_t *input, uint32_t offs, Token *result, const Allocator *allocator);
static uint32_t try_keyword_Definition(const char_t *input, uint32_t offs, Token *result, const Allocator *allocator);
static uint32_t try_keyword_Conclusion(const char_t *input, uint32_t offs, Token *result, const Allocator *allocator);
static uint32_t try_keyword_Lemma(const char_t *input, uint32_t offs, Token *result, const Allocator *allocator);
static uint32_t try_keyword_Theorem(const char_t *input, uint32_t offs, Token *result, const Allocator *allocator);
static uint32_t try_keyword_Proposition(const char_t *input, uint32_t offs, Token *result, const Allocator *allocator);
static uint32_t try_keyword_Proof(const char_t *input, uint32_t offs, Token *result, const Allocator *allocator);
static uint32_t try_keyword_Procedure(const char_t *input, uint32_t offs, Token *result, const Allocator *allocator);
static uint32_t try_keyword_denoteas(const char_t *input, uint32_t offs, Token *result, const Allocator *allocator);
static uint32_t try_keyword_latex(const char_t *input, uint32_t offs, Token *result, const Allocator *allocator);

static uint32_t try_symbol_DOUBLE_LEFT_SQUARE_BRACKET(const char_t * input, Token * result, const Allocator * allocator);
static uint32_t try_symbol_DOUBLE_RIGHT_SQUARE_BRACKET(const char_t * input, Token * result, const Allocator * allocator);
static uint32_t try_startswith_letter_A(const char_t * input, Token * result, const Allocator * allocator);
static uint32_t try_startswith_letter_C(const char_t * input, Token * result, const Allocator * allocator);
static uint32_t try_startswith_letter_D(const char_t * input, Token * result, const Allocator * allocator);
static uint32_t try_startswith_letter_L(const char_t * input, Token * result, const Allocator * allocator);
static uint32_t try_startswith_letter_P(const char_t * input, Token * result, const Allocator * allocator);
static uint32_t try_startswith_letter_T(const char_t * input, Token * result, const Allocator * allocator);
static uint32_t try_startswith_letter_d(const char_t * input, Token * result, const Allocator * allocator);
static uint32_t try_startswith_letter_l(const char_t * input, Token * result, const Allocator * allocator);


static uint32_t try_pass_comment(const char *input, uint32_t *lineno, uint32_t *column);

uint32_t t_IDENTIFIER(const char_t * const input, Token * const result, const Allocator * const allocator) {
  const char_t *pText = input;
  if (startswithLetter(pText)) {
    pText++;
  } else {
    result->length = pText - input;
    return 0;
  }
  while (isIdentChar(pText)) { pText ++; }
  const uint32_t len = pText - input;
  result->type = MATHLANG_TOKEN_IDENTIFIER;
  result->value = allocator->calloc(len + 1, sizeof(char_t));
  allocator->memcpy(result->value, input, len);
  ((char_t *) result->value)[len] = '\0';
  result->length = pText - input;
  return result->length;
}

// [0-9]+((\.[0-9]+?)
static uint32_t t_NUMBER(const char_t *input, Token *result, const Allocator *allocator) {
  const char_t *pText = input;
  bool is_fraction = false;
  while (true) {
    if (isDecDigital(pText)) {
      pText++;
    } else if (!is_fraction && *pText == '.' && isDecDigital((pText + 1))) {
      is_fraction = true;
      pText++;
    } else { break; }
  }
  const uint32_t len = pText - input;
  result->type = MATHLANG_TOKEN_NUMBER;
  result->value = allocator->calloc(len + 1, sizeof(char_t));
  allocator->memcpy(result->value, input, len);
  ((char_t *) result->value)[len] = '\0';
  result->length = pText - input;
  return result->length;
}


#define fn_try_keyword(_kw, _type)                                                      \
  inline uint32_t try_keyword_##_kw(const char_t * const input, uint32_t const offs,    \
                             Token * const result, const Allocator * const allocator) { \
    const char_t pattern[] = string_t(#_kw);                                            \
    for (uint32_t i = offs; i < sizeof(pattern) - 1; i++) {                             \
      if (input[i - offs] != pattern[i]) { goto __failed_kw_##_kw; }                    \
    }                                                                                   \
    const char_t * const tail = &input[sizeof(pattern) - 1 - offs];                     \
    if (startswithLetter(tail) || *tail == '_') { goto __failed_kw_##_kw; }             \
    result->type = MATHLANG_TOKEN_##_type;                                              \
    result->value = nullptr;                                                            \
    result->length = lenof(#_kw);                                                       \
    return lenof(#_kw);                                                                 \
    __failed_kw_##_kw : return t_IDENTIFIER(input - offs, result, allocator);           \
  }
#define fn_try_keyword_val(_kw, _type, val)                                             \
  inline uint32_t try_keyword_##_kw(const char_t * const input, uint32_t const offs,    \
                             Token * const result, const Allocator * const allocator) { \
    const char_t pattern[] = string_t(#_kw);                                            \
    for (uint32_t i = offs; i < sizeof(pattern) - 1; i++) {                             \
      if (input[i - offs] != pattern[i]) { goto __failed_kw_##_kw; }                    \
    }                                                                                   \
    const char_t * const tail = &input[sizeof(pattern) - 1 - offs];                     \
    if (startswithLetter(tail) || *tail == '_') { goto __failed_kw_##_kw; }             \
    result->type = MATHLANG_TOKEN_##_type;                                              \
    result->value = (void *) val;                                                       \
    result->length = lenof(#_kw);                                                       \
    return lenof(#_kw);                                                                 \
    __failed_kw_##_kw : return t_IDENTIFIER(input - offs, result, allocator);           \
  }

fn_try_keyword(Procedure, PROCEDURE)
fn_try_keyword(denoteas,  DENOTEAS)
fn_try_keyword(Proof,     PROOF)
fn_try_keyword(latex,     LATEX)
fn_try_keyword_val(Definition,  DEFINITION_TYPE,  MATHLANG_ENTRY_Definition)
fn_try_keyword_val(Convention,  DEFINITION_TYPE,  MATHLANG_ENTRY_Convention)
fn_try_keyword_val(Axiom,       AXIOM_TYPE,       MATHLANG_ENTRY_Axiom)
fn_try_keyword_val(Assumption,  AXIOM_TYPE,       MATHLANG_ENTRY_Assumption)
fn_try_keyword_val(Theorem,     THEOREM_TYPE,     MATHLANG_ENTRY_Theorem)
fn_try_keyword_val(Lemma,       THEOREM_TYPE,     MATHLANG_ENTRY_Lemma)
fn_try_keyword_val(Conclusion,  THEOREM_TYPE,     MATHLANG_ENTRY_Conclusion)
fn_try_keyword_val(Proposition, THEOREM_TYPE,     MATHLANG_ENTRY_Proposition)


#define fn_fall_through(len)                                      \
  do {                                                            \
    uint32_t length = t_IDENTIFIER(input - 1, result, allocator); \
    if (length == 0) {                                            \
      result->type = MATHLANG_TOKEN_IDENTIFIER;                   \
      result->value = allocator->calloc(len + 1, sizeof(char_t)); \
      allocator->memcpy(result->value, input, 1);                 \
      ((char_t *) result->value)[1] = '\0';                       \
      result->length = 1;                                         \
      return 1;                                                   \
    }                                                             \
    return length;                                                \
  } while (0)

inline uint32_t try_symbol_DOUBLE_LEFT_SQUARE_BRACKET(const char_t * input, Token * result, const Allocator *) {
  if (*input == '[') {
    result->type = MATHLANG_TOKEN_DOUBLE_LEFT_SQUARE_BRACKET;
    result->value = nullptr;
    result->length = 2;
    return 2;
  }
  result->type = MATHLANG_TOKEN_LEFT_SQUARE_BRACKET;
  result->value = nullptr;
  result->length = 1;
  return 1;
}

inline uint32_t try_symbol_DOUBLE_RIGHT_SQUARE_BRACKET(const char_t * input, Token * result, const Allocator *) {
  if (*input == ']') {
    result->type = MATHLANG_TOKEN_DOUBLE_RIGHT_SQUARE_BRACKET;
    result->value = nullptr;
    result->length = 2;
    return 2;
  }
  result->type = MATHLANG_TOKEN_RIGHT_SQUARE_BRACKET;
  result->value = nullptr;
  result->length = 1;
  return 1;
}

inline uint32_t try_startswith_letter_A(const char_t * input, Token * result, const Allocator * allocator) {
  switch (*input) {
    case 'x': { return try_keyword_Axiom(input + 1, 2, result, allocator); }
    case 's': { return try_keyword_Assumption(input + 1, 2, result, allocator); }
    default: fn_fall_through(1);
  }
}

inline uint32_t try_startswith_letter_C(const char_t * input, Token * result, const Allocator * allocator) {
  if (strcmp_o(input, "on") != 2) { fn_fall_through(1); }
  const char_t * pText = input + 2;
  switch (*pText) {
    case 'c': { return try_keyword_Conclusion(pText + 1, 4, result, allocator); }
    case 'v': { return try_keyword_Convention(pText + 1, 4, result, allocator); }
    default: fn_fall_through(1);
  }
}

inline uint32_t try_startswith_letter_D(const char_t * input, Token * result, const Allocator * allocator) {
  return try_keyword_Definition(input, 1, result, allocator);
}

inline uint32_t try_startswith_letter_L(const char_t * input, Token * result, const Allocator * allocator) {
  return try_keyword_Lemma(input, 1, result, allocator);
}

inline uint32_t try_startswith_letter_P(const char_t * input, Token * result, const Allocator * allocator) {
  if (strcmp_o(input, "ro") != 2) { fn_fall_through(1); }
  const char_t * pText = input + 2;
  switch (*pText) {
    case 'c': { return try_keyword_Procedure(pText + 1, 4, result, allocator); }
    case 'o': { return try_keyword_Proof(pText + 1, 4, result, allocator); }
    case 'p': { return try_keyword_Proposition(pText + 1, 4, result, allocator); }
    default: fn_fall_through(1);
  }
}

inline uint32_t try_startswith_letter_T(const char_t * input, Token * result, const Allocator * allocator) {
  return try_keyword_Theorem(input, 1, result, allocator);
}

inline uint32_t try_startswith_letter_d(const char_t * input, Token * result, const Allocator * allocator) {
  return try_keyword_denoteas(input, 1, result, allocator);
}

inline uint32_t try_startswith_letter_l(const char_t * input, Token * result, const Allocator * allocator) {
  return try_keyword_latex(input, 1, result, allocator);
}

uint32_t mathlang_tokenize_single_char(const char_t *const input, Token *const result, const Allocator *) {
  const char_t *pText = input;
  if (!*pText) { return 0; }
  constexpr char SINGLE_CHARS[] = ".,;${}()<>";
  constexpr uint32_t SINGLE_CHAR_TYPES[] = {
    MATHLANG_TOKEN_DOT, MATHLANG_TOKEN_COMMA,
    MATHLANG_TOKEN_SEMICOLON, MATHLANG_TOKEN_LATEX_DELIMITER,
    MATHLANG_TOKEN_LEFT_BRACKET, MATHLANG_TOKEN_RIGHT_BRACKET,
    MATHLANG_TOKEN_LEFT_PARENTHESIS, MATHLANG_TOKEN_RIGHT_PARENTHESIS,
    MATHLANG_TOKEN_LEFT_ANGLE_BRACKET, MATHLANG_TOKEN_RIGHT_ANGLE_BRACKET,
  };
  const uint32_t index = stridx_o(*pText, SINGLE_CHARS);
  if (index < lenof(SINGLE_CHARS)) {
    result->type = SINGLE_CHAR_TYPES[index];
    result->value = nullptr;
    result->length = 1;
    return result->length;
  }
  return 0;
}

uint32_t mathlang_single_tokenize(const char_t * const input, Token * const result, const Allocator * const allocator) {
  if (!*input) {
    result->type = MATHLANG_TOKEN_TERMINATOR;
    result->value = nullptr;
    result->length = 0;
    return 0;
  }
  switch (*input) {
    case '[': { return try_symbol_DOUBLE_LEFT_SQUARE_BRACKET(input + 1, result, allocator); }
    case ']': { return try_symbol_DOUBLE_RIGHT_SQUARE_BRACKET(input + 1, result, allocator); }
    case 'A': { return try_startswith_letter_A(input + 1, result, allocator); }
    case 'C': { return try_startswith_letter_C(input + 1, result, allocator); }
    case 'D': { return try_startswith_letter_D(input + 1, result, allocator); }
    case 'L': { return try_startswith_letter_L(input + 1, result, allocator); }
    case 'P': { return try_startswith_letter_P(input + 1, result, allocator); }
    case 'T': { return try_startswith_letter_T(input + 1, result, allocator); }
    case 'd': { return try_startswith_letter_d(input + 1, result, allocator); }
    case 'l': { return try_startswith_letter_l(input + 1, result, allocator); }
    default: {}
  }
  uint32_t length = 0;
  if (isDecDigital(input)) {
    length = t_NUMBER(input, result, allocator);
    return length;
  }
  length = mathlang_tokenize_single_char(input, result, allocator);
  if (length > 0) { return length; }
  length = t_IDENTIFIER(input, result, allocator);
  if (length > 0) { return length; }
  result->type = MATHLANG_TOKEN_BAD_TOKEN;
  result->value = nullptr;
  result->length = 0;
  return 0;
}

uint32_t latex_tokenize_single_char(const char_t *const input, Token *const result, const Allocator *) {
  const char_t *pText = input;
  if (!*pText) { return 0; }
  constexpr char SINGLE_CHARS[] = "^_{}[]#";
  constexpr uint32_t SINGLE_CHAR_TYPES[] = {
    MATHLANG_TOKEN_CIRCUMFLEX, MATHLANG_TOKEN_UNDERSCORE,
    MATHLANG_TOKEN_LEFT_BRACKET, MATHLANG_TOKEN_RIGHT_BRACKET,
    MATHLANG_TOKEN_LEFT_SQUARE_BRACKET, MATHLANG_TOKEN_RIGHT_SQUARE_BRACKET,
    MATHLANG_TOKEN_HASHTAG
  };
  const uint32_t index = stridx_o(*pText, SINGLE_CHARS);
  if (index < lenof(SINGLE_CHARS)) {
    result->type = SINGLE_CHAR_TYPES[index];
    result->value = nullptr;
    result->length = 1;
    return result->length;
  }
  return 0;
}

uint32_t t_LATEX_COMMAND(const char_t *const input, Token *const result, const Allocator *allocator) {
  const char_t *pText = input;
  if (!*pText) { return 0; }

  // \\[a-zA-Z]+
  if (startswithLetter(pText)) {
    do { pText ++; } while (startswithLetter(pText));
  } else {
    // other converted symbols
    constexpr char SINGLE_CHARS[] = ".,:;!\\%$#@&^_{}[]~ ";
    const uint32_t index = stridx_o(*pText, SINGLE_CHARS);
    if (index < lenof(SINGLE_CHARS)) {
      pText++;
    } else {
      return 0;
    }
  }

  const uint32_t len = pText - input + 1;
  result->type = MATHLANG_TOKEN_LATEX_SYMBOL;
  result->value = allocator->calloc(len + 1, sizeof(char_t));
  allocator->memcpy(result->value, input - 1, len);
  ((char_t *) result->value)[len] = '\0';
  result->length = pText - input + 1;
  return result->length;
}

uint32_t latex_single_tokenize(const char_t *, Token *, const Allocator *) {
  return 0;
}

uint32_t try_pass_comment(const char * const input, uint32_t * const lineno, uint32_t * const column) {
  const char *pText = input + 1;
  if (*pText == '/') {
    do { pText++; } while (*pText != '\n' && *pText != '\0');
    *column += pText - input;
  } else if (*pText == '*') {
    pText++; (*column) ++;
    do {
      while (*pText != '*') {
        if (*pText == '\n') { (*lineno)++, *column = 0; }
        if (*pText == '\0') { goto __end_of_block_comment; }
        pText++; (*column) ++;
      }
      pText++; (*column) ++;
    } while (*pText != '/');
    __end_of_block_comment:
  } else {
    return 0;
  }
  return pText - input;
}

uint32_t pass_space(const char * const input, uint32_t * const lineno, uint32_t * const column) {
  uint32_t l = lineno ? *lineno : 0;
  uint32_t c = column ? *column : 0;
  const char *pText = input;
  while (*pText) {
    switch (*pText) {
      case '\v':
      case '\n': {
        l++;
        c = 1;
        break;
      }
      case '\f':
      case '\r':
      case ' ':
      case '\t': {
        c++;
        break;
      }
      case '/': {
        const uint32_t passed = try_pass_comment(pText, &l, &c);
        if (passed) {
          pText += passed;
          continue;
        }
      }
      default: {
        goto __return;
      }
    }
    pText++;
  }
  __return:
  lineno ? *lineno = l : 0;
  column ? *column = c : 0;
  return pText - input;
}
