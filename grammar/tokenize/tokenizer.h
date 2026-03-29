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
 * Filename: tokenizer.h
 * Creator: Yaokai Liu
 * Create Date: 2026-03-27
 * Copyright (c) 2026 Yaokai Liu. All rights reserved.
 **/

#ifndef MATHLANG_TOKENIZER_H
#define MATHLANG_TOKENIZER_H

#include "Mathlang/token.h"
#include "Mathlang/error.h"
#include "Mathlang/context.h"

typedef struct Tokenizer Tokenizer;

Tokenizer *MathlangTokenizer_new(const char_t *src, const MathlangContext *context, const Allocator *allocator);

uint32_t MathlangTokenizer_next(Tokenizer *tokenizer, Token *token, ErrInfo *errInfo, const Allocator *allocator);

void MathlangTokenizer_destroy(Tokenizer *tokenizer);


#endif //MATHLANG_TOKENIZER_H