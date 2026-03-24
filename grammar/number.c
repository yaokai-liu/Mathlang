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
 * Filename: number.c
 * Creator: Yaokai Liu
 * Create Date: 2026-03-24
 * Copyright (c) 2026 Yaokai Liu. All rights reserved.
 **/

#include "number.h"

uint32_t Number_add_uint64(Number addend, const uint64_t addon) {
  if (addon == 0) { return MATHLANG_COMPUTE_SUCCESS; }

  const uint32_t n_parts = Array_length(addend.bit_array);
  if (!n_parts) {
    Array_append(addend.bit_array, &addon, 1);
    return MATHLANG_COMPUTE_SUCCESS;
  }
  uint64_t * parts = Array_first_real(addend.bit_array);

  uint64_t carry = addon;
  for (uint32_t i = 0; i < n_parts; i++) {
    const uint64_t old_val = parts[i];
    parts[i] += carry;
    if (parts[i] >= old_val) {
      carry = 0; break;
    }
    carry = 1;
  }
  if (carry) {
    Array_append(addend.bit_array, &carry, 1);
  }

  return MATHLANG_COMPUTE_SUCCESS;
}

uint32_t Number_mul_uint64(Number multiplicand, const uint64_t multiplier) {
  if (multiplier == 1) { return MATHLANG_COMPUTE_SUCCESS; }
  if (multiplier == 0) {
    Array_clear(multiplicand.bit_array, nullptr);
    return MATHLANG_COMPUTE_SUCCESS;
  }

  const uint32_t n_parts = Array_length(multiplicand.bit_array);
  if (!n_parts) { return MATHLANG_COMPUTE_SUCCESS; }
  uint64_t * parts = Array_first_real(multiplicand.bit_array);

  uint64_t carry = 0;
  for (uint32_t i = 0; i < n_parts; i++) {
    const unsigned _BitInt(128) product = ((unsigned _BitInt(128))parts[i]) * multiplier + carry;
    parts[i] = (uint64_t) product;
    carry = (uint64_t) (product >> 64);
  }
  if (carry) {
    Array_append(multiplicand.bit_array, &carry, 1);
  }

  return MATHLANG_COMPUTE_SUCCESS;
}

uint32_t Number_sub_uint64(Number minuend, uint64_t subtrahend) {
  if (subtrahend == 0) { return MATHLANG_COMPUTE_SUCCESS; }

  const uint32_t n_parts = Array_length(minuend.bit_array);
  if (!n_parts) { return MATHLANG_COMPUTE_FAILED; }
  uint64_t * parts = Array_first_real(minuend.bit_array);
  if (n_parts == 1 && parts[0] < subtrahend) { return MATHLANG_COMPUTE_FAILED; }

  uint64_t borrow = subtrahend;
  for (uint32_t i = 0; i < n_parts; i++) {
    const uint64_t old_val = parts[i];
    parts[i] -= borrow;
    if (parts[i] > old_val) {
      borrow = 1;
    } else {
      // borrow = 0;
      break;
    }
  }

  uint32_t n_zeros = 0, new_n_parts = n_parts;
  while (new_n_parts > 0) {
    const uint64_t *last = (uint64_t*)Array_real_addr(minuend.bit_array, new_n_parts - 1);
    if (*last == 0) { n_zeros ++; } else { break; }
    new_n_parts --;
  }
  Array_delete(minuend.bit_array, new_n_parts, n_zeros);

  return MATHLANG_COMPUTE_SUCCESS;
}

uint32_t Number_bit_length(const Number a) {
  const uint32_t n_parts = Array_length(a.bit_array);
  if (n_parts == 0) { return 0; }
  const uint64_t * parts = Array_first_real(a.bit_array);
  uint64_t highest_part = parts[n_parts - 1];
  uint32_t n_bits = 0;
  while (highest_part) { highest_part >>= 1; n_bits ++; }
  n_bits += (n_parts - 1) * 64;
  return n_bits;
}

int32_t Number_cmp(const Number a, const Number b) {
  const uint32_t n_parts_a = Array_length(a.bit_array);
  const uint32_t n_parts_b = Array_length(b.bit_array);

  if (n_parts_a > n_parts_b) { return  1; }
  if (n_parts_a < n_parts_b) { return -1; }

  if (n_parts_a == 0) { return 0; }

  const uint64_t * a_parts = Array_first_real(a.bit_array);
  const uint64_t * b_parts = Array_first_real(b.bit_array);
  for (uint32_t i = n_parts_a - 1; i < n_parts_a; i--) {
    if (a_parts[i] > b_parts[i]) { return  1; }
    if (a_parts[i] < b_parts[i]) { return -1; }
  }

  return 0;
}

uint32_t Number_shift(Number a, uint32_t count) {
  uint32_t n_parts = Array_length(a.bit_array);
  if (n_parts == 0 || count == 0) { return 0; }

  uint32_t n_add_parts = count / 64;
  uint32_t bits_count = count % 64;

  if (bits_count != 0) {
    uint64_t * parts = Array_first_real(a.bit_array);
    uint64_t carry = 0;
    for (uint32_t i = 0; i < n_parts; i++) {
      const uint64_t old_val = parts[i];
      parts[i] = (old_val << bits_count) + carry;
      carry = old_val >> (64 - bits_count);
    }
    if (carry) {
      Array_append(a.bit_array, &carry, 1);
    }
  }
  constexpr uint64_t zero = 0;
  Array *zeros = Array_clear_new(a.bit_array, &zero, n_add_parts);
  Array_insert_array(a.bit_array, 0, zeros);
  releasePrimeArray(zeros);

  return count;
}

uint32_t Number_clear(Number a) {
  Array_clear(a.bit_array, nullptr);
  return 0;
}
