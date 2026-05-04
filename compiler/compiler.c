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
 * Module Name: compiler
 * Filename: compiler.c
 * Creator: 16975
 * Create Date: 2026-04-11
 * Copyright (c) 2026 Yaokai Liu. All rights reserved.
 **/

#include "compiler.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  if (argc < 2) { return -1; }
  const char_t *srcpath = argv[1];
  FILE *srcfile = fopen(srcpath, "r");
  if (srcfile == NULL) {return -1;}
  fseek(srcfile, 0, SEEK_END);
  const size_t size = ftell(srcfile);
  fseek(srcfile, 0, SEEK_SET);
  char_t *src = STDAllocator.malloc(size + 1);
  fread(src, sizeof(char_t), size, srcfile);
  src[size] = '\0';
  MathlangContext *context = MathlangContext_new(&STDAllocator);
  Tokenizer *tokenizer = MathlangTokenizer_new(src, context, &STDAllocator);

  ErrInfo err_info = {};
  MathEntry *entry = parse(tokenizer, context, &err_info, &STDAllocator);
  if (entry == NULL) {
    return (int) err_info.code;
  }
}
