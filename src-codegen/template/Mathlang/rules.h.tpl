${license}

#ifndef MATHLANG_RULES_H
#define MATHLANG_RULES_H

#include "Mathlang/target.h"
#include "Mathlang/context.h"

typedef void *fn_mathlang_reduce(Token argv[], MathlangContext *, ErrInfo *, const Allocator *);

enum MATHLANG_PRODUCT_RULE_ENUM {
  ${enum_reduces}
};

extern fn_mathlang_reduce * const MATHLANG_PRODUCTS[];

${reduces}

#endif  // MATHLANG_RULES_H
