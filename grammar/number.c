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
#include "mathlang/char_t.h"

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
  uint64_t val = 0;
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
inline uint32_t t_DEC_DIGITS_adic16(const char_t *const input, Number *value, const Allocator *) {
  const char_t *pText = input;
  if (!isHexDigital(pText)) { return 0; }
  uint32_t trialing_zeros = 0;
  uint32_t eff_length = 0;
  while (*pText) {
    if (*pText == '\'') {
      if (!isHexDigital(pText + 1)) { break; }
      pText ++; continue;
    }
    if ('0' == *pText) { trialing_zeros ++; continue; }
    const uint32_t shift_count = 4 * (1 + trialing_zeros);
    if ('1' <= *pText && *pText <= '9') {
      *value = (*value << shift_count) + (*pText - '0');
    } else if ('a' <= *pText && *pText <= 'f') {
      *value = (*value << shift_count) + (*pText - 'a' + 0xa);
    } else if ('A' <= *pText && *pText <= 'F') {
      *value = (*value << shift_count) + (*pText - 'A' + 0xA);
    } else { break; }
    trialing_zeros = 0;
    pText ++; eff_length ++;
  }
  uint32_t length = pText - input;
  if (effective_length) { *effective_length = eff_length - trialing_zeros; }
  return length;
}
// (?=\.)[0-9]+
inline uint32_t t_DEC_DIGITS_adic10(const char_t *const input, Number *value, const Allocator *) {
  const char_t *pText = input;
  if (!isDecDigital(pText)) { return 0; }
  uint32_t trialing_zeros = 0;
  uint32_t eff_length = 0;
  while (*pText) {
    if (*pText == '\'') {
      if (!isDecDigital(pText + 1)) { break; }
      pText ++; continue;
    }
    if ('0' == *pText) { trialing_zeros ++; continue; }
    uint32_t rate = 10 * (1 + trialing_zeros);
    if ('1' <= *pText && *pText <= '9') {
      *value = ((*value) * rate) + (*pText - '0');
    } else { break; }
    trialing_zeros = 0;
    pText ++; eff_length ++;
  }
  uint32_t length = pText - input;
  if (effective_length) { *effective_length = eff_length - trialing_zeros; }
  return length;
}
// (?=\.)[0-7]+
inline uint32_t t_DEC_DIGITS_adic8(const char_t *const input, Number *value, const Allocator *) {
  const char_t *pText = input;
  if (!isOctDigital(pText)) { return 0; }
  uint32_t trialing_zeros = 0;
  uint32_t eff_length = 0;
  while (*pText) {
    if (*pText == '\'') {
      if (!isOctDigital(pText + 1)) { break; }
      pText ++; continue;
    }
    if ('0' == *pText) { trialing_zeros ++; continue; }
    uint32_t shift_count = 3 * (1 + trialing_zeros);
    if ('1' <= *pText && *pText <= '7') {
      *value = ((*value) << shift_count) + (*pText - '0');
    } else { break; }
    trialing_zeros = 0;
    pText ++; eff_length ++;
  }
  uint32_t length = pText - input;
  if (effective_length) { *effective_length = eff_length - trialing_zeros; }
  return length;
}
// (?=\.)[01]+
inline uint32_t t_DEC_DIGITS_adic2(const char_t *const input, Number *value, const Allocator *) {
  const char_t *pText = input;
  if (!isBinDigital(pText)) { return 0; }
  uint32_t trialing_zeros = 0;
  uint32_t eff_length = 0;
  while (*pText) {
    if (*pText == '\'') {
      if (!isBinDigital(pText + 1)) { break; }
      pText ++; continue;
    }
    if ('0' == *pText) { trialing_zeros ++; continue; }
    uint32_t shift_count = 1 + trialing_zeros;
    if ('1' == *pText) {
      *value = ((*value) << shift_count) + (*pText - '0');
    } else { break; }
    trialing_zeros = 0;
    pText ++; eff_length ++;
  }
  uint32_t length = pText - input;
  if (effective_length) { *effective_length = eff_length - trialing_zeros; }
  return length;
}

#define ADIC_TYPE_16   0
#define ADIC_TYPE_10   1
#define ADIC_TYPE_8    2
#define ADIC_TYPE_2    3
#define INT_DIGITAL_FUNC      0
#define DEC_DIGITAL_FUNC     1

typedef uint32_t tokenize_t(const char_t *, uint32_t *, Number *);
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

/*
 * if adic
 * is ADIC_TYPE_16:    [a-fA-F0-9]+((\.[a-fA-F0-9]+([pP][+-]?[0-9]+)?)?))
 * is ADIC_TYPE_10:    [0-9]+((\.[0-9]+([pPeE][+-]?[0-9]+)?)?)
 * is ADIC_TYPE_8:     [0-7]+((\.[0-7]+([pPeE][+-]?[0-9]+)?)?)
 * is ADIC_TYPE_2:     [01]+((\.[01]+([pPeE][+-]?[0-9]+)?)?))
 */
uint32_t t_NUMBER(const char_t *const input, const bool negative, const uint32_t adic, const Allocator *const allocator) {
  const char_t *pText = input;

  uint32_t size = 4;
  Number integer = { .type = MATHLANG_NUMBER_REAL, .n_bits = 0, .bits.bare_bits = 0 };
  uint64_t exponent = 0;
  uint32_t int_eff_length = 0;
  uint32_t DEC_eff_length = 0;
  bool exp_negative = false;
  enum MATHLANG_NUMBER_TYPE_ENUM ;

  uint32_t length = DIGITAL_FUNC_TOOLS[adic][INT_DIGITAL_FUNC](pText, &int_eff_length, &integer);
  if (!length) { return 0; } else { pText += length; }
  if (*pText == '.') {
    type = XLR_VAL_LITERAL_FLOAT; size = 4; pText ++;
    length = DIGITAL_FUNC_TOOLS[adic][DEC_DIGITAL_FUNC](pText, &DEC_eff_length, &integer);
    if (!length) { return 0; }
    pText += length;
  }
  if (*pText == 'p' || *pText == 'P' || *pText == 'e' || *pText == 'E') {
    pText ++;
    exp_negative = (*pText == '-');
    if (isSign(pText)) { pText++; }
    length = DIGITAL_FUNC_TOOLS[ADIC_TYPE_10][INT_DIGITAL_FUNC](pText, nullptr, &exponent);
    if (!length) { return 0; }
    pText += length;
  }
  exponent = exp_negative ? -exponent : exponent;
  exponent += int_eff_length;
  exponent -= DEC_eff_length;
  if ((*pText == 'l') || (*pText == 'L')) { size *= 2; pText++; }
  if ((*pText == 'l') || (*pText == 'L')) { size *= 2; pText++; }
  size = min(size, 16);
  if ((*pText == 'u') || (*pText == 'U')) {
    if (type == XLR_VAL_LITERAL_FLOAT) { return 0; }
    type = XLR_VAL_LITERAL_UINT; pText++;
  }
  if (isIdentChar(pText) || *pText == '.') { return 0; }

  LRValue *value = allocator->calloc(1, sizeof(LRValue));
  value->size = size;
  // TODO:
  //  The value obtained in this way is not accurate enough.
  //  Please try to improve the algorithm.
  if (type == XLR_VAL_LITERAL_FLOAT) {
    const uint32_t exponent_base = ADIC_BASE[adic];
    if (size == 4 ) {
      float32_t real = ((float32_t) (uint32_t) integer);
      float32_t exp = (float32_t) pow((float32_t) exponent_base, (int32_t) exponent - 1);
      value->val.F32 = (negative) ? -real * exp : real * exp;
      value->type = (REFER(LRType)) XLR_BUILTIN_TYPE_F32;
    } else if (size == 8 ) {
      float64_t real = ((float64_t) () integer);
      float64_t exp = (float64_t) pow((float64_t) exponent_base, (int64_t) exponent - 1);
      value->val.F64 = (negative) ? -real * exp : real * exp;
      value->type = (REFER(LRType)) XLR_BUILTIN_TYPE_F64;
    } else if (size == 16) {
      float128_t real = ((float128_t) (uint128_t) integer);
      float128_t exp = (float128_t) pow((float128_t) exponent_base, (int128_t) exponent - 1);
      value->val.F128 = (negative) ? -real * exp : real * exp;
      value->type = (REFER(LRType)) XLR_BUILTIN_TYPE_F128;
    } else { return 0; }
  } else if (type == XLR_VAL_LITERAL_UINT) {
    if (negative) { integer = -integer; }
    if (size == 4) { value->val.U32 = integer; value->type = (REFER(LRType)) XLR_BUILTIN_TYPE_U32; }
    else if (size == 8) { value->val.U64 = integer; value->type = (REFER(LRType)) XLR_BUILTIN_TYPE_U64; }
    else if (size == 16) { value->val.U128 = integer; value->type = (REFER(LRType)) XLR_BUILTIN_TYPE_U128; }
    else { return 0; }
  } else {
    if (negative) { integer = -integer; }
    if (size == 4) { value->val.I32 = integer; value->type = (REFER(LRType)) XLR_BUILTIN_TYPE_I32; }
    else if (size == 8) { value->val.I64 = integer; value->type = (REFER(LRType)) XLR_BUILTIN_TYPE_I64; }
    else if (size == 16) { value->val.I128 = integer; value->type = (REFER(LRType)) XLR_BUILTIN_TYPE_I128; }
    else { return 0; }
  }

  return 0;
}
