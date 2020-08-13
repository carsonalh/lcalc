#include <pest.h>

#include <lambda_calculus.h>

void setUp(void) {}
void tearDown(void) {}

TEST(createdTreeIsNotNull)
{
    struct lc_Tree *tree = lc_Tree_Create();

    ASSERT_NOT_NULL(tree);
}

int main(void)
{
    RUN_TEST(createdTreeIsNotNull);

    return TEST_STATUS();
}

