/* License
 *
 * Mathlang - A Practical Language for Mathematics
 * Copyright (C) 2025 Yaokai Liu
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
 * Module Name:
 * Filename: token.h
 * Creator: Yaokai Liu
 * Create Date: 2025-05-29
 * Copyright (c) 2025 Yaokai Liu. All rights reserved.
 **/

#ifndef MATHLANG_TOKEN_H
#define MATHLANG_TOKEN_H


#include "allocator.h"
#include "char_t.h"
#include <stdint.h>

/// location of a Token in a file
typedef struct Location {
  /// Offset in src string
  uint32_t offset;
  /// line number in src file
  uint32_t lineno;
  /// column offset in the line in src file
  uint32_t column;
} Location;

typedef struct Token {
  /// start of the token
  Location start;
  /// end of the token
  Location end;
  /// length of the token (size in bytes)
  uint32_t length;
  /// Token Type
  uint32_t type;
  /// value of the token
  void *value;
} Token;

const char_t *get_name(uint16_t type);
void releaseToken(Token *token, const Allocator *allocator);

#endif //MATHLANG_TOKEN_H
