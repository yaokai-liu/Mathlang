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
 * Filename: enum.h
 * Creator: Yaokai Liu
 * Create Date: 2026-03-25
 * Copyright (c) 2026 Yaokai Liu. All rights reserved.
 **/

#ifndef MATHLANG_ENUM_H
#define MATHLANG_ENUM_H

#include "stdint.h"

enum MATHLANG_ENTRY_TYPE_ENUM: uint32_t {
  MATHLANG_ENTRY_Definition,
  MATHLANG_ENTRY_Convention,
  MATHLANG_ENTRY_Axiom,
  MATHLANG_ENTRY_Assumption,
  MATHLANG_ENTRY_Theorem,
  MATHLANG_ENTRY_Lemma,
  MATHLANG_ENTRY_Conclusion,
  MATHLANG_ENTRY_Proposition,
};

#endif //MATHLANG_ENUM_H