#include "lexer.hpp"

Token::Token(const char* s)
{
    if (s == nullptr || *s == '\0')
    {
        type = TOK_EOF;
        lexeme = std::string();
    }
    else if (std::isdigit(*s))
    {
        char* end;
        std::strtod(s, &end);
        type = TOK_CONSTANT;
        lexeme = std::string(s, (end - s));
    }
    else if (std::isalpha(*s))
    {
        int length = 0;
        while (*(s + length) != '\0' && std::isalnum(*(s + length)))
        {
            length += 1;
        }
        type = TOK_VARIABLE;
        lexeme = std::string(s, length);
    }
    else
    {
        type = TOK_OPERATION;
        lexeme = std::string(s, s + 1);
    }
}

TokenType Token::getType() const
{
    return type;
}

std::string Token::getStr() const
{
    return lexeme;
}

std::size_t Token::getSize() const
{
    return lexeme.size();
}

double Token::getValue() const
{
    if (type != TOK_CONSTANT)
    {
        std::cout << "Wrong type getting in Token::getValue()" << std::endl;
    }
    double value;
    std::from_chars(lexeme.c_str(), lexeme.c_str() + getSize(), value);
    return value;
}


Lexer::Lexer(std::string _s): s(std::move(_s)), token(s.c_str()) {}

const Token& Lexer::getToken() const
{
    return token;
}

void Lexer::nextToken()
{
    len += token.getSize();
    token = Token(s.c_str() + len);
}