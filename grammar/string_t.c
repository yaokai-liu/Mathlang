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
 * Filename: string_t.c
 * Creator: Yaokai Liu
 * Create Date: 2026-03-25
 * Copyright (c) 2026 Yaokai Liu. All rights reserved.
 **/

#include "string_t.h"


inline uint32_t stridx_o(const char_t chr, const char_t * const str) {
  if (!str) { return -1; }
  int len = 0;
  while (chr != str[len] && str[len]) { len++; }
  return len;
}

inline uint32_t strcmp_o(const char_t *const str1, const char_t * const str2) {
  uint32_t i = 0;
  while (str1[i] && str2[i] && (str1[i] == str2[i])) { i++; }
  return i;
}
