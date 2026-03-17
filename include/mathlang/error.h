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
 * Filename: error.h
 * Creator: Yaokai Liu
 * Create Date: 2025-05-27
 * Copyright (c) 2025 Yaokai Liu. All rights reserved.
 **/

#ifndef MATHLANG_ERROR_H
#define MATHLANG_ERROR_H

#include "token.h"

enum MATHLANG_ERROR_CODE_ENUM {
  MATHLANG_SUCCESS,
  MATHLANG_ERROR_UNRECOGNIZED_SYMBOL,
  MATHLANG_ERROR_STACK_REDUCE_CONFLICT,
  MATHLANG_ERROR_REDUCE_STACK_CONFLICT,
  MATHLANG_ERROR_REDUCE_REDUCE_CONFLICT,

  MATHLANG_ERROR_TARGET_MISMATCH,
  MATHLANG_ERROR_DUPLICATED_SET_RULE,
  MATHLANG_ERROR_MULTI_EMPTY_RULE,

  MATHLANG_ERROR_BAD_QUANTIFIER,
  MATHLANG_ERROR_UNKNOWN_TARGET,
  MATHLANG_ERROR_UNEXPECTED_TOKEN,
  MATHLANG_ERROR_BAD_TOKEN,
  MATHLANG_ERROR_BAD_RULE,

  MATHLANG_ERROR_NUMBER_OF_ARGUMENTS_MISMATCH,
  MATHLANG_ERROR_ACCESS_NONE_FIELD_TYPE,
  MATHLANG_ERROR_CALLED_NOT_A_FUNCTION,
  MATHLANG_ERROR_NO_SUCH_ATTRIBUTE,
  MATHLANG_ERROR_NO_SUCH_VARIABLE,
  MATHLANG_ERROR_MULTI_DEFINITION,
  MATHLANG_ERROR_NO_SUCH_FIELD,
  MATHLANG_ERROR_TYPE_MISMATCH,
};


typedef struct ErrInfo {
  Location start;
  Location end;
  uint32_t code;
  uint32_t state;
  uint32_t token;
} ErrInfo;

#endif //MATHLANG_ERROR_H
