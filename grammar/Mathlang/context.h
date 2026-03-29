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
 * Filename: context.h
 * Creator: Yaokai Liu
 * Create Date: 2026-03-26
 * Copyright (c) 2026 Yaokai Liu. All rights reserved.
 **/

#ifndef MATHLANG_CONTEXT_H
#define MATHLANG_CONTEXT_H

#include "array.h"
#include "avl-tree.h"
#include "stack.h"
#include "trie.h"
#include "target.h"
#include "Mathlang/error.h"
#include "Mathlang/token.h"

enum CONTEXT_ARRAY_ID_ENUM: uint32_t {
  CONTEXT_ARRAY_NULL,
  CONTEXT_ARRAY_NAME_ARRAY,
  CONTEXT_ARRAY_IDENT_ARRAY,
  CONTEXT_ARRAY_MATH_ENTRY_ARRAY,
};

enum CONTEXT_TOKENIZE_ID_ENUM: uint32_t {
  CONTEXT_TOKENIZE_NULL,
  CONTEXT_TOKENIZE_LATEX,
  CONTEXT_TOKENIZE_MATHLANG,
  CONTEXT_TOKENIZE_NOTATION,
};

typedef struct MathlangContext {
  const Allocator *allocator;
  Array *name_array;    // Array<char_t>
  Array *ident_array;   // Array<Identifier>
  Trie  *ident_trie;    // Trie<char_t, REFER(Identifier)>

  Array *item_array;  // Array<MathEntry>
  AVLTree *item_tree;  // AVLTree<REFER(Identifier), REFER(MathEntry)>

  uint32_t token_env;
  Stack *token_env_stack; // Stack<uint32_t>
} MathlangContext;

MathlangContext *MathlangContext_new(const Allocator *allocator);

uint32_t MathlangContext_set_ident_cat(MathlangContext *context, REFER(Identifier) v_ident, uint32_t category);

void MathlangContext_state_action(MathlangContext * context, uint32_t state, Token * token, const Allocator * allocator);


#endif //MATHLANG_CONTEXT_H