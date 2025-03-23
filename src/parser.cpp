#include "expression.hpp"


template <class T>
Parser<T>::Parser(std::string _lexer): lexer(std::move(_lexer)) {}

template <class T>
Expression<T> Parser<T>::parse()
{
    Expression<T> expr = parseSum();
    if (lexer.getToken().getType() != TOK_EOF)
    {
        std::cout << "Failed to parse term" << std::endl;
    }
    return expr;
}

template <class T>
Expression<T> Parser<T>::parseSum()
{
    Expression<T> expr = parseProduct();
    while (true)
    {
        if (lexer.getToken().getStr() == "+")
        {
            lexer.nextToken();
            expr = expr + parseProduct();
        }
        else if (lexer.getToken().getStr() == "-")
        {
            lexer.nextToken();
            expr = expr - parseProduct();
        }
        else
        {
            break;
        }
    }
    return expr;
}

template <class T>
Expression<T> Parser<T>::parseProduct()
{
    Expression<T> expr = parsePower();
    while (true)
    {
        if (lexer.getToken().getStr() == "*")
        {
            lexer.nextToken();
            expr = expr * parseProduct();
        }
        else if (lexer.getToken().getStr() == "/")
        {
            lexer.nextToken();
            expr = expr / parseProduct();
        }
        else
        {
            break;
        }
    }
    return expr;
}

template <class T>
Expression<T> Parser<T>::parsePower()
{
    Expression<T> expr = parseMinus();
    if (lexer.getToken().getStr() == "^")
    {
        lexer.nextToken();
        return expr ^ parsePower();
    }
    return expr;
}

template <class T>
Expression<T> Parser<T>::parseMinus()
{
    if (lexer.getToken().getStr() == "-")
    {
        lexer.nextToken();
        return Expression<T>(T(0)) - parseMinus();
    }
    return parseToken();
}

template <class T>
Expression<T> Parser<T>::parseToken()
{
    Token token = lexer.getToken();
        
    if (token.getType() == TOK_CONSTANT)
    {
        lexer.nextToken();
        if constexpr (std::is_same<T, std::complex<double>>::value)
        {
            if (lexer.getToken().getType() == TOK_VARIABLE && lexer.getToken().getStr() == "i")
            {
                lexer.nextToken();
                return Expression<T>(T(0, token.getValue()));
            }
        }
        return Expression<T>(token.getValue());
    }
        
    if (token.getType() == TOK_VARIABLE)
    {
        lexer.nextToken();
        std::string name(token.getStr());
            
        if (lexer.getToken().getStr() == "(")
        {
            lexer.nextToken();
            Expression<T> expr = parseSum();
            if (lexer.getToken().getStr() != ")")
            {
                std::cout << "Invalid scobe sequence" << std::endl;
            }
            lexer.nextToken();

            if (name == "sin")
            {
                return expr.sin();
            }
            if (name == "cos")
            {
                return expr.cos();
            }
            if (name == "ln")
            {
                return expr.ln();
            }
            if (name == "exp")
            {
                return expr.exp();
            }
            
            std::cout << "Invalid function name: " << name << std::endl;
        }

        if (name == "pi")
        {
            return Expression<T>(M_PI);
        }
        if (name == "e")
        {
            return Expression<T>(M_E);
        }
        if constexpr (std::is_same<T, std::complex<double>>::value)
        {
            if (name == "i")
            {
                return Expression<T>(std::complex<double>(0, 1));
            }
        }
        return Expression<T>(name);
    }
    
    if (token.getStr() == "(")
    {
        lexer.nextToken();
        Expression<T> expr = parseSum();
        if (lexer.getToken().getStr() != ")")
        {
            std::cout << "Invalid scobe sequence" << std::endl;
        }
        lexer.nextToken();
        return expr;
    }
    
    std::cout << "Unexpected term" << std::endl;
    return Expression<T>(T(0));
}


template
class Parser<int>;
template
class Parser<double>;
template
class Parser<std::complex<double>>;