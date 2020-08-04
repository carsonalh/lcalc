#include "lambda_calculus.h"
#include "lambda_calculus_internal.h"

#include <rigid.h>

#include <string.h>
#include <ctype.h>
#include <assert.h>

void _lc_TokenList_Init(struct lc_TokenList *list)
{
    _rg_List_Init(&list->list, sizeof(struct lc_Token), 0);
}

void _lc_TokenList_Uninit(struct lc_TokenList *list)
{
    _rg_List_Uninit(&list->list);
}

struct lc_TokenList* lc_TokenList_Create(void)
{
    struct lc_TokenList *token_list = malloc(sizeof *token_list);

    _lc_TokenList_Init(token_list);

    return token_list;
}

void lc_TokenList_Destroy(struct lc_TokenList *list)
{
    _lc_TokenList_Uninit(list);

    free(list);
}

static struct lc_Token _lc_TokenizeSingleCharacter(char c)
{
    struct lc_Token result;

    if (c == '(') {
        result.type = LC_OPEN_PAREN;
    }
    else if (c == ')') {
        result.type = LC_CLOSE_PAREN;
    }
    else if (c == '\\') {
        result.type = LC_LAMBDA;
    }
    else if (c == '.') {
        result.type = LC_DOT;
    }
    else if (isalpha(c)) {
        result.type = LC_VARIABLE;
        result.data.variable = c;
    }
    else if (isspace(c)) {
        result.type = LC_IGNORE;
    }
    else {
        result.type = LC_UNKNOWN;
    }

    return result;
}

struct lc_TokenizationError
lc_Tokenize(const char *str, struct lc_TokenList *token_list_out)
{
    if (str == NULL) {
        struct lc_TokenizationError error;
        error.type = LC_TOKEN_INVALID_STRING;
        error.char_index = 0;

        return error;
    }

    if (strlen(str) == 0) {
        struct lc_TokenizationError error;
        error.type = LC_TOKEN_NO_ERROR;
        error.char_index = 0;

        return error;
    }

    assert(rg_List_GetSize(&token_list_out->list) == 0);

    for (int i = 0; i < strlen(str); ++i) {
        struct lc_Token token = _lc_TokenizeSingleCharacter(str[i]);

        if (token.type == LC_UNKNOWN) {
            struct lc_TokenizationError error;

            error.type = LC_TOKEN_INVALID_TOKEN;
            error.char_index = i;

            return error;
        }
        else if (token.type != LC_IGNORE) {
            rg_List_InsertEnd(&token_list_out->list, &token);
        }
    }

    struct lc_TokenizationError error;
    error.type = LC_TOKEN_NO_ERROR;
    return error;
}

