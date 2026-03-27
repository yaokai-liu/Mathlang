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
 * Module Name: grammar/Mathlang
 * Filename: target.h
 * Creator: Yaokai Liu
 * Create Date: 2026-03-26
 * Copyright (c) 2026 Yaokai Liu. All rights reserved.
 **/

#ifndef MATHLANG_TARGET_H
#define MATHLANG_TARGET_H

#include "array.h"
#include "Mathlang/char_t.h"

typedef struct MathEntry {} MathEntry, Definition, Theorem, Procedure;
typedef struct EntryHeader {} DefHeader, ThmHeader, ProcHeader;
typedef struct TextBlock {} TextBlock;

typedef struct Adverb {} Adverb;
typedef struct Adjective {} Adjective;
typedef struct Complement {} Complement;
typedef struct Objective {} Objective, Subjective;
typedef struct Verb {} Verb;

typedef struct Noun {} NounPhrase, BareNounPhrase, NotedNoun;
typedef Array NounPhrases; // Array<NounPhrase>

typedef struct Notation {} Notation;
typedef Array Notations; // Array<Notation>
typedef struct NotationDefinition {} NotationDefinition;
typedef Array NotationDefinitions; // Array<NotationDefinition>
typedef struct Sentence {} Statement, Operation, Sentence, StateSentence, OperaSentence;
typedef Array Sentences, StateSentences, OperaSentences; // Array<Sentence>

typedef struct Refer {} Refer;
typedef struct LatexExpression {} LatexExpression;
typedef struct LatexSymbol {} LatexSymbol, BareLatexSymbol;


typedef struct {
  uint32_t      type; // MATHLANG_IDENT_CATEGORY_ENUM
  REFER(char_t) name;
} Identifier;


#endif //MATHLANG_TARGET_H
