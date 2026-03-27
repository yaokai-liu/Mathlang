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
#include "Mathlang/char_t.h"

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

#define startswithLetter(pText)   (('a' <= *(pText) && *(pText) <= 'z') || ('A' <= *(pText) && *(pText) <= 'Z'))
#define isLatexHeader(pText)      ( *(pText) == '\\' || startswithLetter(pText))
#define isIdentChar(pText)        (startswithLetter(pText) || isDecDigital(pText) || (*(pText) == '-'))
#define isHexLetter(pText)        (('a' <= *(pText) && *(pText) <= 'f') || ('A' <= *(pText) && *(pText) <= 'F'))
#define isSign(pText)             ((*(pText) == '-') || (*(pText) == '+'))
#define isBinDigital(pText)       ('0' == *(pText) || *(pText) == '1')
#define isOctDigital(pText)       ('0' <= *(pText) && *(pText) <= '7')
#define isDecDigital(pText)       ('0' <= *(pText) && *(pText) <= '9')
#define isHexDigital(pText)       (isDecDigital(pText) || isHexLetter(pText))

static uint32_t t_INT_DIGITS_adic16(const char_t *input, Number *value, const Allocator *allocator);
static uint32_t t_INT_DIGITS_adic10(const char_t *input, Number *value, const Allocator *allocator);
static uint32_t t_INT_DIGITS_adic8 (const char_t *input, Number *value, const Allocator *allocator);
static uint32_t t_INT_DIGITS_adic2 (const char_t *input, Number *value, const Allocator *allocator);
static uint32_t t_DEC_DIGITS_adic16(const char_t *input, Number *value, const Allocator *allocator);
static uint32_t t_DEC_DIGITS_adic10(const char_t *input, Number *value, const Allocator *allocator);
static uint32_t t_DEC_DIGITS_adic8 (const char_t *input, Number *value, const Allocator *allocator);
static uint32_t t_DEC_DIGITS_adic2 (const char_t *input, Number *value, const Allocator *allocator);

// [a-fA-F0-9]+
inline uint32_t t_INT_DIGITS_adic16(const char_t *const input, Number *value, const Allocator *const) {
  const char_t *pZero = input;
  if (!isHexDigital(pZero)) { return 0; }
  while ('0' == *pZero) { pZero++; }
  const char_t *pText = pZero;
  uint64_t val = 0;
  while (isHexDigital(pText)) { pText ++; }
  for (uint32_t i = 1; i <= pText - pZero; i++) {
    uint32_t j = (i - 1) % 16;
    if ('0' <= pText[-i] && pText[-i] <= '9') {
      val |= ((uint64_t) (pText[-i] - '0')) << (4 * j);
    } else if ('a' <= pText[-i] && pText[-i] <= 'f') {
      val |= ((uint64_t) (pText[-i] - 'a' + 0xa)) << (4 * j);
    } else if ('A' <= pText[-i] && pText[-i] <= 'F') {
      val |= ((uint64_t) (pText[-i] - 'A' + 0xA)) << (4 * j);
    }
    if (j == 15) {
      Array_append(value->bit_array, &val, 1);
      val = 0;
    }
  }
  if ((pText - pZero) % 16 != 0) {
    Array_append(value->bit_array, &val, 1);
  }
  return pText - input;
}
// [0-9]+
inline uint32_t t_INT_DIGITS_adic10(const char_t *const input, Number *value, const Allocator *const) {
  const char_t *pZero = input;
  if (!isDecDigital(pZero)) { return 0; }
  while ('0' == *pZero) { pZero++; }
  const char_t *pText = pZero;
  while (isDecDigital(pText)) {
    uint64_t part_val = 0;
    uint64_t factor = 1;
    int count = 0;
    while (count < 18 && isDecDigital(pText)) {
      part_val = part_val * 10 + (*pText - '0');
      factor *= 10;
      pText++;
      count++;
    }
    if (count > 0) {
      Number_mul_uint64(*value, factor);
      Number_add_uint64(*value, part_val);
    }
  }
  return pText - input;
}
// [0-7]+
inline uint32_t t_INT_DIGITS_adic8(const char_t *const , Number *, const Allocator *const) {
 return 0;
}
// [01]+
inline uint32_t t_INT_DIGITS_adic2(const char_t *const input, Number *value, const Allocator *) {
  const char_t *pZero = input;
  if (!isBinDigital(pZero)) { return 0; }
  while ('0' == *pZero) { pZero++; }
  const char_t *pText = pZero;
  uint64_t val = 0;
  while (isBinDigital(pText)) { pText ++; }
  for (uint32_t i = 1; i <= pText - pZero; i++) {
    uint32_t j = (i - 1) % 64;
    val |= ((uint64_t) (pText[-i] == '1')) << j;
    if (j == 63) {
      Array_append(value->bit_array, &val, 1);
      val = 0;
    }
  }
  if ((pText - pZero) % 64 != 0) {
    Array_append(value->bit_array, &val, 1);
  }
  return pText - input;
}

// (?=\.)[a-fA-F0-9]+
inline uint32_t t_DEC_DIGITS_adic16(const char_t *const , Number *, const Allocator *) {
  return 0;
}
// (?=\.)[0-9]+
inline uint32_t t_DEC_DIGITS_adic10(const char_t *const , Number *, const Allocator *) {
  return 0;
}
// (?=\.)[0-7]+
inline uint32_t t_DEC_DIGITS_adic8(const char_t *const , Number *, const Allocator *) {
  return 0;
}
// (?=\.)[01]+
inline uint32_t t_DEC_DIGITS_adic2(const char_t *const , Number *, const Allocator *) {
  return 0;
}

#define ADIC_TYPE_16   0
#define ADIC_TYPE_10   1
#define ADIC_TYPE_8    2
#define ADIC_TYPE_2    3
#define INT_DIGITAL_FUNC      0
#define DEC_DIGITAL_FUNC     1
/*
typedef uint32_t tokenize_t(const char_t *, Number *, const Allocator *);
static tokenize_t *const DIGITAL_FUNC_TOOLS[4][2] = {
    [ADIC_TYPE_16] = { [INT_DIGITAL_FUNC] = t_INT_DIGITS_adic16, [DEC_DIGITAL_FUNC] = t_DEC_DIGITS_adic16},
    [ADIC_TYPE_10] = { [INT_DIGITAL_FUNC] = t_INT_DIGITS_adic10, [DEC_DIGITAL_FUNC] = t_DEC_DIGITS_adic10},
    [ADIC_TYPE_8 ] = { [INT_DIGITAL_FUNC] = t_INT_DIGITS_adic8 , [DEC_DIGITAL_FUNC] = t_DEC_DIGITS_adic8 },
    [ADIC_TYPE_2 ] = { [INT_DIGITAL_FUNC] = t_INT_DIGITS_adic2 , [DEC_DIGITAL_FUNC] = t_DEC_DIGITS_adic2 },
};
static constexpr uint32_t ADIC_BASE[] = {
    [ADIC_TYPE_16] = 16,
    [ADIC_TYPE_10] = 10,
    [ADIC_TYPE_8 ] = 8,
    [ADIC_TYPE_2 ] = 2,
};
*/
/*
 * if adic
 * is ADIC_TYPE_16:    [a-fA-F0-9]+((\.[a-fA-F0-9]+([pP][+-]?[0-9]+)?)?))
 * is ADIC_TYPE_10:    [0-9]+((\.[0-9]+([pPeE][+-]?[0-9]+)?)?)
 * is ADIC_TYPE_8:     [0-7]+((\.[0-7]+([pPeE][+-]?[0-9]+)?)?)
 * is ADIC_TYPE_2:     [01]+((\.[01]+([pPeE][+-]?[0-9]+)?)?))
 */
uint32_t t_NUMBER(const char_t *const , Number *, const Allocator *const) {
  return 0;
}
