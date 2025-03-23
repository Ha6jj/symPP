#ifndef EXPRESSION_HEADER_GUARD
#define EXPRESSION_HEADER_GUARD

#include "./baseExpression/baseExpression.hpp"
#include "lexer.hpp"
#include <type_traits>

template <class T>
class Expression
{
public:
    Expression(const T&);
    Expression(const Expression&);
    Expression(Expression&&);
    Expression(const std::string&);
    Expression(const std::shared_ptr<BaseExpression<T>>&);
    ~Expression() = default;

    Expression<T>& operator=(const Expression<T>&);
    Expression<T>& operator=(Expression<T>&&);

    Expression<T> operator+(const Expression<T>&) const;
    Expression<T> operator-(const Expression<T>&) const;
    Expression<T> operator*(const Expression<T>&) const;
    Expression<T> operator/(const Expression<T>&) const;
    Expression<T> operator^(const Expression<T>&) const;

    Expression<T> sin(void) const;
    Expression<T> cos(void) const;
    Expression<T> ln(void) const;
    Expression<T> exp(void) const;

    T eval() const;
    std::string toString() const;
    Expression<T> diff(const std::string&) const;
    Expression<T> subs(const std::unordered_map<std::string, T>&) const;

private:
    std::shared_ptr<BaseExpression<T>> implExpression;
};

template<class T>
class Parser
{
public:
    Parser(std::string);

    Expression<T> parse();

private:
    Lexer lexer;

    Expression<T> parseSum();
    Expression<T> parseProduct();
    Expression<T> parsePower();
    Expression<T> parseMinus();
    Expression<T> parseToken();
};

template <class T>
Expression<T> parse(const std::string& input)
{
    return Parser<T>(input).parse();
}

#endif