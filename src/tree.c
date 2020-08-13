#include "lambda_calculus.h"
#include "lambda_calculus_internal.h"

void _lc_Tree_Init(struct lc_Tree *tree) {}

void _lc_Tree_Uninit(struct lc_Tree *tree) {}

struct lc_Tree *lc_Tree_Create(void)
{
    struct lc_Tree *tree = malloc(sizeof *tree);
    return tree;
}

void lc_Tree_Destroy(struct lc_Tree *tree)
{
    free(tree);
}

