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


/***************************************************/
/******************* Declarations ******************/
/***************************************************/

typedef struct PreProcessMacro PreProcessMacro;
typedef struct MathRecord MathEntry, Definition, Theorem, Procedure;
typedef struct EntryHeader DefHeader, ThmHeader, ProcHeader;
typedef struct TextBlock TextBlock;

typedef struct Adverb Adverb;
typedef struct Adjective Adjective;
typedef struct Complement Complement;
typedef struct Object Object;
typedef Array Objective, Subjective; // Array<Object>
typedef struct Verb Verb;
typedef struct Noun NounPhrase, BareNounPhrase, NotedNoun, Noun;
typedef Array NounPhrases; // Array<NounPhrase>

typedef struct Notation Notation;
typedef Array Notations; // Array<Notation>
typedef struct NotationDefinition NotationDefinition;
typedef Array NotationDefinitions; // Array<NotationDefinition>
typedef struct Sentence Statement, Operation, Sentence, StateSentence, OperaSentence;
typedef Array Sentences, StateSentences, OperaSentences; // Array<Sentence>

typedef struct Refer Refer;
typedef struct LatexExpression LatexExpression;
typedef struct LatexSymbol NotationSymbol, LatexSymbol, BareLatexSymbol;

typedef struct IntroItem IntroItem;
typedef Array IntroItems; // Array<IntroItem>
typedef struct Identifier Identifier;

typedef struct PathString PathString;
typedef Array PathStrings; // Array<PathString>
typedef struct Pattern Pattern;

/***************************************************/
/******************* Definitions *******************/
/***************************************************/

typedef struct PreProcessMacro PreProcessMacro;
typedef struct MathRecord {} MathEntry, Definition, Theorem, Procedure;
typedef struct EntryHeader {} DefHeader, ThmHeader, ProcHeader;
typedef struct TextBlock {} TextBlock;

typedef struct Adverb {} Adverb;
typedef struct Adjective {} Adjective;
typedef struct Complement {} Complement;
typedef struct Object {
  REFER(Noun) type;
  Array *     modifiers; // Array<REFER(MathRecord)>
  Notation   *notation;
} Object;
typedef Array Objective, Subjective; // Array<Object>
typedef struct Verb {} Verb;
typedef struct Noun {
  REFER(Noun) prototype;
  Array *     modifiers; // Array<REFER(MathRecord)>
} NounPhrase, BareNounPhrase, NotedNoun, Noun;
typedef Array NounPhrases; // Array<NounPhrase>

typedef struct Notation {
  LatexSymbol *name;
  Notations   *args;
} Notation;
typedef Array Notations; // Array<Notation>
typedef struct NotationDefinition {} NotationDefinition;
typedef Array NotationDefinitions; // Array<NotationDefinition>
typedef struct Sentence {} Statement, Operation, Sentence, StateSentence, OperaSentence;
typedef Array Sentences, StateSentences, OperaSentences; // Array<Sentence>

typedef struct Refer {} Refer;
typedef struct LatexExpression {} LatexExpression;
typedef struct LatexSymbol {

} NotationSymbol, LatexSymbol, BareLatexSymbol;

typedef struct Identifier {
  uint32_t      category; // MATHLANG_IDENT_CATEGORY_ENUM
  REFER(char_t) name;
} Identifier;

typedef struct PathString {} PathString;
typedef Array PathStrings; // Array<PathString>

#endif //MATHLANG_TARGET_H
