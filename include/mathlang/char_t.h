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
 * Filename: char_t.h
 * Creator: Yaokai Liu
 * Create Date: 24-7-4
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#ifndef CHAR_T_H
#define CHAR_T_H

// Promise sizeof(char_t) < sizeof(uint64_t).
typedef char char_t;

#define string_t(_str) _str

#endif  // CHAR_T_H