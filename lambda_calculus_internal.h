#ifndef LAMBDA_CALCULUS_INTERNAL_H
#define LAMBDA_CALCULUS_INTERNAL_H

#include "lambda_calculus.h"

#define LC_TOKEN_CHAR_OPEN_PAREN    '('
#define LC_TOKEN_CHAR_CLOSE_PAREN   ')'
#define LC_TOKEN_CHAR_LAMBDA        '\\'
#define LC_TOKEN_CHAR_DOT           '.'

#include <rigid.h>

struct lc_TokenList {
    struct rg_List list;
};

#endif /* LAMBDA_CALCULUS_INTERNAL_H */

