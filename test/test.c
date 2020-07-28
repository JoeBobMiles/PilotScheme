
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define PLT_OUT_OF_MEMORY(demanded_size, given_size) \
    printf( \
        "Insufficient memory!\n" \
        "Required:\t%lld bytes\n" \
        "Given:\t%lld bytes\n", \
        demanded_size, \
        given_size)

#include "pilot.h"

#include "utest.h"

UTEST(basic, first_token_invalid_for_empty_input)
{
    const size_t memory_pool_size = 1024;
    void* memory_pool = malloc(memory_pool_size);
    memset(memory_pool, 0, memory_pool_size);

    plt_init(memory_pool, memory_pool_size);

    plt_lexer lexer = { 0 };
    plt_token token = plt_next_token(
        &lexer,
        "",
        0);

    EXPECT_EQ(PLT_TOKEN_INVALID, token.type);

    free(memory_pool);
}

UTEST(lexing, identifies_open_paren)
{
    const size_t memory_pool_size = 1024;
    void* memory_pool = malloc(memory_pool_size);
    memset(memory_pool, 0, memory_pool_size);

    plt_init(memory_pool, memory_pool_size);

    plt_lexer lexer = { 0 };
    plt_token token = plt_next_token(
        &lexer,
        "(",
        1);

    EXPECT_EQ(PLT_TOKEN_LIST_START, token.type);

    free(memory_pool);
}

UTEST(lexing, identifies_close_paren)
{
    const size_t memory_pool_size = 1024;
    void* memory_pool = malloc(memory_pool_size);
    memset(memory_pool, 0, memory_pool_size);

    plt_init(memory_pool, memory_pool_size);

    plt_lexer lexer = { 0 };
    plt_token token = plt_next_token(
        &lexer,
        ")",
        1);

    EXPECT_EQ(PLT_TOKEN_LIST_END, token.type);

    free(memory_pool);
}

UTEST(lexing, identifies_quote)
{
    const size_t memory_pool_size = 1024;
    void* memory_pool = malloc(memory_pool_size);
    memset(memory_pool, 0, memory_pool_size);

    plt_init(memory_pool, memory_pool_size);

    plt_lexer lexer = { 0 };
    plt_token token = plt_next_token(&lexer, "\'", 1);

    EXPECT_EQ(PLT_TOKEN_QUOTE, token.type);

    free(memory_pool);
}

UTEST(lexing, identifies_number)
{
    const size_t memory_pool_size = 1024;
    void* memory_pool = malloc(memory_pool_size);
    memset(memory_pool, 0, memory_pool_size);

    plt_init(memory_pool, memory_pool_size);

    plt_lexer lexer = { 0 };
    plt_token token = plt_next_token(&lexer, "0", 1);

    EXPECT_EQ(PLT_TOKEN_NUMBER, token.type);

    free(memory_pool);
}

UTEST(lexing, identifies_ident)
{
    const size_t memory_pool_size = 1024;
    void* memory_pool = malloc(memory_pool_size);
    memset(memory_pool, 0, memory_pool_size);

    plt_init(memory_pool, memory_pool_size);

    const char* string = "cons";
    const size_t string_length = strlen(string);

    plt_lexer lexer = { 0 };
    plt_token token = plt_next_token(
        &lexer,
        string,
        string_length);

    EXPECT_EQ(PLT_TOKEN_IDENT, token.type);

    free(memory_pool);
}

UTEST(lexing, correctly_identifies_consecutive_tokens)
{
    const size_t memory_pool_size = 1024;
    void* memory_pool = malloc(memory_pool_size);
    memset(memory_pool, 0, memory_pool_size);

    plt_init(memory_pool, memory_pool_size);

    const char* source = "(cons";

    plt_lexer lexer = { 0 };

    // Extract first token (paren)
    plt_token paren = plt_next_token(
        &lexer,
        source,
        strlen(source));

    EXPECT_EQ(PLT_TOKEN_LIST_START, paren.type);
    EXPECT_STREQ("(", paren.text);

    // Extract second token (identifier)
    plt_token ident = plt_next_token(
        &lexer,
        source,
        strlen(source));

    EXPECT_EQ(PLT_TOKEN_IDENT, ident.type);
    EXPECT_STREQ("cons", ident.text);

    free(memory_pool);
}

UTEST_MAIN()