#ifndef LEXER_HEADER_GUARD
#define LEXER_HEADER_GUARD

#include <string>
#include <iostream>
#include <charconv>

enum TokenType
{
    TOK_CONSTANT = 0,
    TOK_VARIABLE = 1,
    TOK_OPERATION = 2,
    TOK_EOF = 3
};

class Token
{
public:
    Token(const char*);

    TokenType getType() const;
    std::string getStr() const;
    std::size_t getSize() const;
    double getValue() const;

private:
    TokenType type;
    std::string lexeme;
};

class Lexer
{
public:
    Lexer(std::string);

    const Token& getToken() const;
    void nextToken();

private:
    std::string s;
    Token token;
    int len = 0;
};

#endif