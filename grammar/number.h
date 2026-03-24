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
 * Filename: number.h
 * Creator: Yaokai Liu
 * Create Date: 2026-03-23
 * Copyright (c) 2026 Yaokai Liu. All rights reserved.
 **/

#ifndef MATHLANG_NUMBER_H
#define MATHLANG_NUMBER_H

#include <stdint.h>
#include "array.h"

enum MATHLANG_NUMBER_TYPE_ENUM: uint32_t {
  MATHLANG_INTEGER_REAL,
  MATHLANG_INTEGER_IMAGINARY,
};

typedef struct Number {
  uint32_t type;
  Array *  bit_array; // Array<uint64_t>, big endian
} Number;

enum MATHLANG_NUMBER_COMPUTE_RESULT_ENUM: uint32_t {
  MATHLANG_COMPUTE_SUCCESS,
  MATHLANG_COMPUTE_FAILED,
};

uint32_t Number_add_uint64(Number addend, uint64_t addon);
uint32_t Number_mul_uint64(Number multiplicand, uint64_t multiplier);
uint32_t Number_sub_uint64(Number minuend, uint64_t subtrahend);

uint32_t Number_bit_length(Number a);
 int32_t Number_cmp(Number a, Number b);
uint32_t Number_shift(Number a, uint32_t count);
uint32_t Number_gcd(Number a, Number b);
uint32_t Number_div(Number a, Number b);
uint32_t Number_clear(Number a);

#endif //MATHLANG_NUMBER_H