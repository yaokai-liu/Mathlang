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
 * Filename: action.h
 * Creator: Yaokai Liu
 * Create Date: 2026-03-21
 * Copyright (c) 2026 Yaokai Liu. All rights reserved.
 **/

#ifndef MATHLANG_ACTION_H
#define MATHLANG_ACTION_H

#include <stdint.h>

typedef struct state state;
struct grammar_action {
    const enum : uint8_t {
        MATHLANG_action_reject = 0,
        MATHLANG_action_stack = 1,
        MATHLANG_action_reduce = 2
      } action      : 2;
    // if action
    // is reduce:     count of tokens to eliminate
    // otherwise:     0
    const uint8_t count : 6;
    // if action
    // is reduce:     index of type of the result token
    // otherwise:     0
    const uint8_t type;
    // if action
    // is reduce:     index of the rule to implay
    // is stack:      index of the next state
    // otherwise:     0
    const uint16_t offset;
};

#endif //MATHLANG_ACTION_H