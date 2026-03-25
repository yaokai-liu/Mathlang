${license}

#ifndef LATEX_RULES_H
#define LATEX_RULES_H

#include "Latex/target.h"
#include "Latex/context.h"

typedef void *fn_Latex_reduce(Token argv[], MLContext *, ErrInfo *, const Allocator *);

enum LATEX_PRODUCT_RULE_ENUM {
  ${enum_reduces}
};

extern fn_Latex_reduce * const LATEX_PRODUCTS[];

${reduces}

#endif  // LATEX_RULES_H
