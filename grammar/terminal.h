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
 * Module Name: grammar
 * Filename: terminal.h
 * Creator: Yaokai Liu
 * Create Date: 2026-03-24
 * Copyright (c) 2026 Yaokai Liu. All rights reserved.
 **/

#ifndef MATHLANG_TERMINAL_H
#define MATHLANG_TERMINAL_H

#include "array.h"

typedef Array LatexExpression; // Array<LatexSymbol *>
typedef struct LatexSymbol {
  uint32_t type;
  union {
    struct { uint32_t symid; Array *arguments; } symbol;
    LatexExpression *expr;
  } value;
  Array *superscripts; // Array<LatexSymbol *>
  Array *subscripts; // Array<LatexSymbol *>
} LatexSymbol, BaseLatexSymbol;


#endif //MATHLANG_TERMINAL_H