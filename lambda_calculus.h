#ifndef LAMBDA_CALCULUS_H
#define LAMBDA_CALCULUS_H

enum lc_TokenType {
    LC_TOKEN_OPEN_PAREN,
    LC_TOKEN_CLOSE_PAREN,
    LC_TOKEN_LAMBDA,
    LC_TOKEN_VARIABLE,
    LC_TOKEN_DOT,
    LC_TOKEN_IGNORE,
    LC_TOKEN_UNKNOWN
};

union lc_TokenData {
    char variable;
};

struct lc_Token {
    enum lc_TokenType type;
    union lc_TokenData data;
};

struct lc_TokenList;

void                _lc_TokenList_Init(struct lc_TokenList *list);
void                _lc_TokenList_Uninit(struct lc_TokenList *list);

struct lc_TokenList*lc_TokenList_Create(void);
void                lc_TokenList_Destroy(struct lc_TokenList *list);


enum lc_TokenizationErrorType;
struct lc_TokenizationError;

enum lc_TokenizationErrorType {
    LC_TOKEN_NO_ERROR,
    LC_TOKEN_INVALID_TOKEN,
    LC_TOKEN_INVALID_STRING
};

struct lc_TokenizationError {
    enum lc_TokenizationErrorType type;
    unsigned char_index;
};

struct lc_TokenizationError
lc_Tokenize(const char *str, struct lc_TokenList *token_list_out);

enum lc_TreeType {
    LC_TREE_VARIABLE,
    LC_TREE_ABSTRACTION,
    LC_TREE_APPLICATION
};

struct lc_Tree;

struct lc_TreeAbstraction {
    char variable_name;
    struct lc_Tree *body;
};

struct lc_TreeApplication {
    struct lc_Tree *function;
    struct lc_Tree *parameter;
};

union lc_TreeData {
    char variable_name;
    struct lc_TreeAbstraction abstraction;
    struct lc_TreeApplication application;
};

/* Represents an abstract syntax tree of lambda calculus. */
struct lc_Tree {
    enum lc_TreeType type;
    union lc_TreeData data;
};

enum lc_LexerErrorType {
    LC_LEXER_NO_ERROR
};

union lc_LexerErrorData {
    /* This is a dummy member and should never be used; as soon as
     * you put another member in this union, PLEASE DELETE THIS. */
    char _;
};

struct lc_LexerError {
    enum lc_LexerErrorType type;
    union lc_LexerErrorData data;
};

void _lc_Tree_Init(struct lc_Tree *tree);
void _lc_Tree_Uninit(struct lc_Tree *tree);

struct lc_Tree *lc_Tree_Create(void);
void            lc_Tree_Destroy(struct lc_Tree *tree);

#endif /* LAMBDA_CALCULUS_H */

