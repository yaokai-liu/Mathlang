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
 * Module Name: grammar/Mathlang
 * Filename: context.c
 * Creator: Yaokai Liu
 * Create Date: 2026-03-26
 * Copyright (c) 2026 Yaokai Liu. All rights reserved.
 **/

#include "context.h"

#include "meman-utils.h"
#include "generated/Mathlang/action-table.gen.h"


MathlangContext *MathlangContext_new(const Allocator *allocator) {
  MathlangContext *context = allocator->calloc(1, sizeof(MathlangContext));
  context->allocator = allocator;

  context->ident_trie = Trie_new(sizeof(char_t), (key_t *) char2u64, allocator);
  context->name_array = Array_new(sizeof(char_t), CONTEXT_ARRAY_NAME_ARRAY, allocator);
  context->ident_array = Array_new(sizeof(Identifier), CONTEXT_ARRAY_IDENT_ARRAY, allocator);
  Array_append(context->name_array, "\0", 1);

  context->item_array = Array_new(sizeof(MathEntry), CONTEXT_ARRAY_MATH_ENTRY_ARRAY, allocator);
  context->item_tree = AVLTree_new(allocator, nullptr);

  context->token_env_stack = Stack_new(allocator);
  context->token_env = CONTEXT_TOKENIZE_MATHLANG;

  return context;
}

uint32_t MathlangContext_set_ident_cat(MathlangContext *context, REFER(Identifier) v_ident, uint32_t category) {
  Identifier *ident = Array_virt2real(context->ident_array, v_ident);
  if (!ident) { return MATHLANG_ERROR_TARGET_MISMATCH; }
  ident->category = category;
  return MATHLANG_SUCCESS;
}
#define ENTER_NOTATION Mathlang_state_AXIOM_TYPE_ThmHeader_LEFT_BRACKET_VERB_CLAUSE_LEFT_BRACKET
#define EXIT_NOTATION Mathlang_state_AXIOM_TYPE_ThmHeader_LEFT_BRACKET_VERB_CLAUSE_LEFT_BRACKET_Notations_RIGHT_BRACKET
#define IN_NOTATION_DEFINITION_(a) Mathlang_state_DEFINITION_TYPE_DefHeader_TextBlock_DENOTE_LEFT_BRACKET_##a
#define _BEFORE_ENTER_LATEX_(a) IN_NOTATION_DEFINITION_(LEFT_SQUARE_BRACKET_NounPhrase_RIGHT_SQUARE_BRACKET_LEFT_PARENTHESIS_Notations_RIGHT_PARENTHESIS_AS_##a)
#define ENTER_LATEX _BEFORE_ENTER_LATEX_(LATEX_DELIMITER)
#define EXIT_LATEX _BEFORE_ENTER_LATEX_(LATEX_DELIMITER_LatexExpression_LATEX_DELIMITER)


void MathlangContext_state_action(MathlangContext *context, uint32_t state, Token *, const Allocator *) {
  switch (state) {
    case ENTER_LATEX: {
      Stack_push(context->token_env_stack, &context->token_env, sizeof(uint32_t));
      context->token_env = CONTEXT_TOKENIZE_LATEX;
      break;
    }
    case ENTER_NOTATION: {
      Stack_push(context->token_env_stack, &context->token_env, sizeof(uint32_t));
      context->token_env = CONTEXT_TOKENIZE_NOTATION;
      break;
    }
    case EXIT_NOTATION:
    case EXIT_LATEX: {
      Stack_pop(context->token_env_stack, &context->token_env, sizeof(uint32_t));
      break;
    }
    default: {
#ifdef MATHLANG_ENABLE_DEBUG
      printf("nothing context need to do at this state: %d.\n", state);
#endif
    }
  }
}
