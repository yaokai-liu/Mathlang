${license}

#ifndef MATHLANG_RULES_H
#define MATHLANG_RULES_H

#include "Mathlang/target.h"
#include "Mathlang/context.h"

typedef void *fn_Mathlang_reduce(Token argv[], MLContext *, ErrInfo *, const Allocator *);

enum MATHLANG_PRODUCT_RULE_ENUM {
  ${enum_reduces}
};

extern fn_Mathlang_reduce * const MATHLANG_PRODUCTS[];

${reduces}

#endif  // MATHLANG_RULES_H
