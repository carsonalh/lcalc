#include <pest.h>

#include <rigid.h>

#include <lambda_calculus.h>
#include <lambda_calculus_internal.h>

#include <string.h>

static struct lc_TokenList g_token_list;

void setUp(void)
{
    _lc_TokenList_Init(&g_token_list);
}

void tearDown(void)
{
    _lc_TokenList_Uninit(&g_token_list);
    memset(&g_token_list, 0, sizeof g_token_list);
}

TEST(returnsEmptyListForEmptyString)
{
    lc_Tokenize("", &g_token_list);

    ASSERT_EQUAL_INT(0, rg_List_GetSize(&g_token_list.list));
}

TEST(correctlyIdentifiesSingleToken, enum lc_TokenType token_type,
     const char *string)
{
    lc_Tokenize(string, &g_token_list);

    struct lc_Token first_token = \
            *(struct lc_Token *)rg_List_Get(&g_token_list.list, 0);

    ASSERT_EQUAL_INT(token_type, first_token.type);
}

TEST(onlyIdentifiesAlphabeticCharacterAsVariable, const char *string,
     bool is_variable)
{
    struct lc_TokenizationError error = lc_Tokenize(string, &g_token_list);

    if (is_variable) {
        struct lc_Token first_token = \
                *(struct lc_Token *)rg_List_Get(&g_token_list.list, 0);

        ASSERT_EQUAL_INT(LC_VARIABLE, first_token.type);
    }
    else {
        ASSERT_EQUAL_INT(LC_TOKEN_INVALID_TOKEN, error.type);
    }
}

TEST(correctlyIdentifiesMoreThanOneToken)
{
#define N_CHARS 6

    const char *string = "(\\x.x)";
    lc_Tokenize(string, &g_token_list);

    struct lc_Token tokens[N_CHARS];
    struct lc_Token expected_tokens[] = {
        { .type = LC_OPEN_PAREN },
        { .type = LC_LAMBDA },
        { .type = LC_VARIABLE },
        { .type = LC_DOT },
        { .type = LC_VARIABLE },
        { .type = LC_CLOSE_PAREN }
    };

    for (int i = 0; i < N_CHARS; ++i) {
        tokens[i] = *(struct lc_Token *)rg_List_Get(&g_token_list.list, i);
        ASSERT_EQUAL(expected_tokens[i].type, tokens[i].type);
    }

#undef N_CHARS
}

TEST(correctlyIdentifiesGivenVariable)
{
    lc_Tokenize("aX", &g_token_list);

    struct lc_Token first_token, second_token;

    first_token = *(struct lc_Token *)rg_List_Get(&g_token_list.list, 0);
    second_token = *(struct lc_Token *)rg_List_Get(&g_token_list.list, 1);

    ASSERT_EQUAL_CHAR('a', first_token.data.variable);
    ASSERT_EQUAL_CHAR('X', second_token.data.variable);
}

TEST(returnsErrorForNullString)
{
    struct lc_TokenizationError error;

    error = lc_Tokenize(NULL, &g_token_list);

    ASSERT_EQUAL_INT(LC_TOKEN_INVALID_STRING, error.type);
}

TEST(returnsNoErrorForEmptyString)
{
    struct lc_TokenizationError error;

    error = lc_Tokenize("", &g_token_list);

    ASSERT_EQUAL_INT(LC_TOKEN_NO_ERROR, error.type);
}

TEST(ignoresSpaceCharacters)
{
    struct lc_TokenizationError error = lc_Tokenize(" \t\r\n", &g_token_list);

    ASSERT_EQUAL_INT(0, rg_List_GetSize(&g_token_list.list));

    ASSERT_EQUAL_INT(LC_TOKEN_NO_ERROR, error.type);
}

int main(void)
{
    RUN_TEST(returnsEmptyListForEmptyString);

    RUN_TEST(correctlyIdentifiesSingleToken, LC_OPEN_PAREN, "(");
    RUN_TEST(correctlyIdentifiesSingleToken, LC_CLOSE_PAREN, ")");
    RUN_TEST(correctlyIdentifiesSingleToken, LC_LAMBDA, "\\");
    RUN_TEST(correctlyIdentifiesSingleToken, LC_DOT, ".");
    RUN_TEST(correctlyIdentifiesSingleToken, LC_VARIABLE, "a");

    RUN_TEST(onlyIdentifiesAlphabeticCharacterAsVariable, "$", false);
    RUN_TEST(onlyIdentifiesAlphabeticCharacterAsVariable, "*", false);
    RUN_TEST(onlyIdentifiesAlphabeticCharacterAsVariable, "/", false);
    RUN_TEST(onlyIdentifiesAlphabeticCharacterAsVariable, "#", false);

    RUN_TEST(onlyIdentifiesAlphabeticCharacterAsVariable, "b", true);
    RUN_TEST(onlyIdentifiesAlphabeticCharacterAsVariable, "C", true);
    RUN_TEST(onlyIdentifiesAlphabeticCharacterAsVariable, "A", true);
    RUN_TEST(onlyIdentifiesAlphabeticCharacterAsVariable, "Z", true);

    RUN_TEST(correctlyIdentifiesMoreThanOneToken);
    RUN_TEST(correctlyIdentifiesGivenVariable);
    RUN_TEST(returnsErrorForNullString);
    RUN_TEST(returnsNoErrorForEmptyString);
    RUN_TEST(ignoresSpaceCharacters);

    return TEST_STATUS();
}

