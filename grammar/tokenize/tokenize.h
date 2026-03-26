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
 * Filename: tokenize.h
 * Creator: Yaokai Liu
 * Create Date: 2026-03-21
 * Copyright (c) 2026 Yaokai Liu. All rights reserved.
 **/

#ifndef MATHLANG_TOKENIZE_H
#define MATHLANG_TOKENIZE_H

#include <stdint.h>

#include "mathlang/char_t.h"
#include "mathlang/token.h"

uint32_t mathlang_single_tokenize(const char_t *input, Token *result, const Allocator *allocator);
uint32_t latex_single_tokenize(const char_t *input, Token *result, const Allocator *allocator);
uint32_t arith_single_tokenize(const char_t *input, Token *result, const Allocator *allocator);
uint32_t pass_space(const char *input, uint32_t *lineno, uint32_t *column);


#endif //MATHLANG_TOKENIZE_H