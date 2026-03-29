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
 * Filename: rules.c
 * Creator: Yaokai Liu
 * Create Date: 2026-03-27
 * Copyright (c) 2026 Yaokai Liu. All rights reserved.
 **/

#include "Mathlang/context.h"
#include "Mathlang/target.h"
#include "generated/tokens.gen.h"
#include "generated/Mathlang/rules.gen.h"

#define Array_foreach(type, _array, doing)              \
  do {                                                  \
    uint32_t __n_elements = Array_length(_array);       \
    type *__elements = Array_first_real(_array);        \
    for (uint32_t __i = 0; __i < __n_elements; __i++) { \
      type *__element = &__elements[__i];               \
      doing                                             \
    }                                                   \
  } while (false)

#define Array_foreach_virt(type, array, doing)          \
  do {                                                  \
    uint32_t __n_elements = Array_length(array);        \
    type *__elements = Array_first_virt(array);         \
    for (uint32_t __i = 0; __i < __n_elements; __i++) { \
      type *__element = &__elements[__i];               \
      doing                                             \
    }                                                   \
  } while (false)


Adjective * Mathlang_Adjective_0 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

Adjective * Mathlang_Adjective_1 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

Adverb * Mathlang_Adverb_0 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

Adverb * Mathlang_Adverb_1 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

BareLatexSymbol * Mathlang_BareLatexSymbol_0 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

BareLatexSymbol * Mathlang_BareLatexSymbol_1 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

BareLatexSymbol * Mathlang_BareLatexSymbol_2 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

BareLatexSymbol * Mathlang_BareLatexSymbol_3 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

BareLatexSymbol * Mathlang_BareLatexSymbol_4 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

BareLatexSymbol * Mathlang_BareLatexSymbol_5 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

BareNounPhrase * Mathlang_BareNounPhrase_0 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

BareNounPhrase * Mathlang_BareNounPhrase_1 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

BareNounPhrase * Mathlang_BareNounPhrase_2 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

BareNounPhrase * Mathlang_BareNounPhrase_3 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

Complement * Mathlang_Complement_0 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

Complement * Mathlang_Complement_1 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

Complement * Mathlang_Complement_2 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

Complement * Mathlang_Complement_3 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

DefHeader * Mathlang_DefHeader_0 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

Definition * Mathlang_Definition_0 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

Definition * Mathlang_Definition_1 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

LatexExpression * Mathlang_LatexExpression_0 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

LatexExpression * Mathlang_LatexExpression_1 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

LatexSymbol * Mathlang_LatexSymbol_0 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

LatexSymbol * Mathlang_LatexSymbol_1 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

LatexSymbol * Mathlang_LatexSymbol_2 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

MathEntry * Mathlang_MathEntry_0 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

MathEntry * Mathlang_MathEntry_1 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

MathEntry * Mathlang_MathEntry_2 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

MathEntry * Mathlang_MathEntry_EXT (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

Notation * Mathlang_Notation_0 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

Notation * Mathlang_Notation_1 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

Notation * Mathlang_Notation_2 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

NotationDefinition * Mathlang_NotationDefinition_0 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

NotationDefinition * Mathlang_NotationDefinition_1 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

NotationDefinitions * Mathlang_NotationDefinitions_0 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

NotationDefinitions * Mathlang_NotationDefinitions_1 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

NotationSymbol * Mathlang_NotationSymbol_0 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

NotationSymbol * Mathlang_NotationSymbol_1 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

NotationSymbol * Mathlang_NotationSymbol_2 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

Notations * Mathlang_Notations_0 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

Notations * Mathlang_Notations_1 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

NotedNoun * Mathlang_NotedNoun_0 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

NotedNoun * Mathlang_NotedNoun_1 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

NotedNoun * Mathlang_NotedNoun_2 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

NounPhrase * Mathlang_NounPhrase_0 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

NounPhrase * Mathlang_NounPhrase_1 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

NounPhrase * Mathlang_NounPhrase_2 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

NounPhrase * Mathlang_NounPhrase_3 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

NounPhrase * Mathlang_NounPhrase_4 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

NounPhrase * Mathlang_NounPhrase_5 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

NounPhrase * Mathlang_NounPhrase_6 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

NounPhrases * Mathlang_NounPhrases_0 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

NounPhrases * Mathlang_NounPhrases_1 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

NounPhrases * Mathlang_NounPhrases_2 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

NounPhrases * Mathlang_NounPhrases_3 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

OperaSentence * Mathlang_OperaSentence_0 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

OperaSentences * Mathlang_OperaSentences_0 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

OperaSentences * Mathlang_OperaSentences_1 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

Operation * Mathlang_Operation_0 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

Operation * Mathlang_Operation_1 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

ProcHeader * Mathlang_ProcHeader_0 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

Procedure * Mathlang_Procedure_0 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

Procedure * Mathlang_Procedure_1 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

Refer * Mathlang_Refer_0 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

Refer * Mathlang_Refer_1 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

Sentence * Mathlang_Sentence_0 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

Sentence * Mathlang_Sentence_1 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

Sentences * Mathlang_Sentences_0 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

Sentences * Mathlang_Sentences_1 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

StateSentence * Mathlang_StateSentence_0 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

Statement * Mathlang_Statement_0 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

Statement * Mathlang_Statement_1 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

Statement * Mathlang_Statement_2 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

Statement * Mathlang_Statement_3 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

Statement * Mathlang_Statement_4 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

Statement * Mathlang_Statement_5 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

Subjective * Mathlang_Subjective_0 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

Subjective * Mathlang_Subjective_1 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

TextBlock * Mathlang_TextBlock_0 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

Theorem * Mathlang_Theorem_0 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

Theorem * Mathlang_Theorem_1 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

ThmHeader * Mathlang_ThmHeader_0 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

ThmHeader * Mathlang_ThmHeader_1 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

Verb * Mathlang_Verb_0 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

Verb * Mathlang_Verb_1 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

Verb * Mathlang_Verb_2 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

Verb * Mathlang_Verb_3 (Token [], MathlangContext *, ErrInfo *, const Allocator *) {
  return nullptr;
}

