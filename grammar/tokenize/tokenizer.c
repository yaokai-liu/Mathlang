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
 * Filename: tokenizer.c
 * Creator: Yaokai Liu
 * Create Date: 2026-03-27
 * Copyright (c) 2026 Yaokai Liu. All rights reserved.
 **/

#include "tokenizer.h"

#include "enum.h"
#include "tokenize.h"
#include "trie.h"
#include "generated/tokens.gen.h"
#include "Mathlang/target.h"


typedef struct Tokenizer {
  const Allocator *allocator;
  const char_t *src;
  uint32_t offset;
  uint32_t lineno;
  uint32_t column;
  MathlangContext *context;
} Tokenizer;

Tokenizer *XLRTokenizer_new(const char_t *src, MathlangContext *context, const Allocator *allocator) {
  Tokenizer *tokenizer = allocator->calloc(1, sizeof(Tokenizer));
  tokenizer->allocator = allocator;
  tokenizer->context = context;
  tokenizer->lineno = 1;
  tokenizer->column = 1;
  tokenizer->src = src;
  tokenizer->offset = 0;
  return tokenizer;
}

void XLRTokenizer_destroy(Tokenizer *tokenizer) {
  tokenizer->allocator->free(tokenizer);
}

#define pText (tokenizer->src + tokenizer->offset)
#define CONTEXT (tokenizer->context)
uint32_t XLRTokenizer_next(Tokenizer *tokenizer, Token *token, ErrInfo *errInfo,
                           const Allocator *allocator) {
  tokenizer->offset += pass_space(pText, &tokenizer->lineno, &tokenizer->column);
  token->type = MATHLANG_TOKEN_BAD_TOKEN;
  token->start.lineno = tokenizer->lineno;
  token->start.column = tokenizer->column;
  token->start.offset = tokenizer->offset;
  const uint32_t length = (CONTEXT->in_latex)
                        ? mathlang_single_tokenize(pText, token, allocator)
                        : latex_single_tokenize(pText, token, allocator);
  if (token->type == MATHLANG_TOKEN_BAD_TOKEN) {
    errInfo->start.lineno = tokenizer->lineno;
    errInfo->start.column = tokenizer->column;
    errInfo->start.offset = tokenizer->offset;
    errInfo->end = errInfo->start;
    errInfo->code = MATHLANG_ERROR_UNRECOGNIZED_SYMBOL;
    return errInfo->code;
  }
  if (token->type == MATHLANG_TOKEN_IDENTIFIER || token->type == MATHLANG_TOKEN_LATEX_SYMBOL) {
    REFER(Identifier) v_ident = Trie_get(CONTEXT->ident_trie, token->value);
    if (!v_ident) {
      REFER(char_t) v_name = Array_last_virt(CONTEXT->name_array) + 1;
      Array_append(CONTEXT->name_array, token->value, token->length + 1);
      const Identifier ident = {.type = MATHLANG_IDENT_CATEGORY_NULL, .name = v_name};
      Array_append(CONTEXT->ident_array, &ident, 1);
      v_ident = Array_last_virt(CONTEXT->ident_array);
      Trie_set(CONTEXT->ident_trie, token->value, v_ident);
    } else if (CONTEXT->in_latex) {
      const Identifier *ident = Array_virt2real(CONTEXT->ident_array, v_ident);
      token->type = (ident->type == MATHLANG_IDENT_CATEGORY_LATEX_COMMAND)
                  ? MATHLANG_TOKEN_LATEX_COMMAND : MATHLANG_TOKEN_LATEX_SYMBOL;
    } else {
      const Identifier *ident = Array_virt2real(CONTEXT->ident_array, v_ident);
      switch (ident->type) {
        case MATHLANG_IDENT_CATEGORY_NOUN:          { token->type = MATHLANG_TOKEN_NOUN; break; }
        case MATHLANG_IDENT_CATEGORY_VERB:          { token->type = MATHLANG_TOKEN_VERB; break; }
        case MATHLANG_IDENT_CATEGORY_PREP:          { token->type = MATHLANG_TOKEN_PREP; break; }
        case MATHLANG_IDENT_CATEGORY_CLAUSE:        { token->type = MATHLANG_TOKEN_CLAUSE; break; }
        case MATHLANG_IDENT_CATEGORY_NUMBER:        { token->type = MATHLANG_TOKEN_NUMBER; break; }
        case MATHLANG_IDENT_CATEGORY_ADVERB:        { token->type = MATHLANG_TOKEN_ADVERB; break; }
        case MATHLANG_IDENT_CATEGORY_PRONOUN:       { token->type = MATHLANG_TOKEN_PRONOUN; break; }
        case MATHLANG_IDENT_CATEGORY_ARTICLE:       { token->type = MATHLANG_TOKEN_ARTICLE; break; }
        case MATHLANG_IDENT_CATEGORY_ADJECTIVE:     { token->type = MATHLANG_TOKEN_ADJECTIVE; break; }
        case MATHLANG_IDENT_CATEGORY_CONJUNCTION:   { token->type = MATHLANG_TOKEN_CONJUNCTION; break; }
        default:;
      }
    }

    allocator->free(token->value);
    token->value = v_ident;
  }
  token->end.column = token->start.column + token->length;
  token->end.offset = token->start.offset + token->length;
  tokenizer->offset += length;
  tokenizer->column += length;
  return MATHLANG_SUCCESS;
}
