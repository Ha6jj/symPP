#include "expression.hpp"

template <class T>
Expression<T>::Expression(const T& value): implExpression(std::make_shared<Constant<T>>(value)) {}

template <class T>
Expression<T>::Expression(const Expression& other): implExpression(other.implExpression) {}

template <class T>
Expression<T>::Expression(Expression &&other): implExpression(std::move(other.implExpression)) {}

template <class T>
Expression<T>::Expression(const std::string& variable):  implExpression(std::make_shared<Symbol<T>>(variable)) {}

template <class T>
Expression<T>::Expression(const std::shared_ptr<BaseExpression<T>>& _implExpression):  implExpression(_implExpression) {}

template <class T>
Expression<T>& Expression<T>::operator=(const Expression<T>& other)
{
    implExpression = other.implExpression;
    return *this;
}

template <class T>
Expression<T>& Expression<T>::operator=(Expression<T>&& other)
{
    implExpression = std::move(other.implExpression);
    return *this;
}

template <class T>
Expression<T> Expression<T>::operator+(const Expression<T>& other) const
{
    return Expression<T>(std::make_shared<Sum<T>>(implExpression, other.implExpression));
}

template <class T>
Expression<T> Expression<T>::operator-(const Expression<T>& other) const
{
    return Expression<T>(std::make_shared<Sub<T>>(implExpression, other.implExpression));
}

template <class T>
Expression<T> Expression<T>::operator*(const Expression<T>& other) const
{
    return Expression<T>(std::make_shared<Prod<T>>(implExpression, other.implExpression));
}

template <class T>
Expression<T> Expression<T>::operator/(const Expression<T>& other) const
{
    return Expression<T>(std::make_shared<Div<T>>(implExpression, other.implExpression));
}

template <class T>
Expression<T> Expression<T>::operator^(const Expression<T>& other) const
{
    return Expression<T>(std::make_shared<Pow<T>>(implExpression, other.implExpression));
}

template <class T>
Expression<T> Expression<T>::sin(void) const
{
    return Expression<T>(std::make_shared<Sin<T>>(implExpression));
}

template <class T>
Expression<T> Expression<T>::cos(void) const
{
    return Expression<T>(std::make_shared<Cos<T>>(implExpression));
}

template <class T>
Expression<T> Expression<T>::ln(void) const
{
    return Expression<T>(std::make_shared<Ln<T>>(implExpression));
}

template <class T>
Expression<T> Expression<T>::exp(void) const
{
    return Expression<T>(std::make_shared<Exp<T>>(implExpression));
}

template <class T>
T Expression<T>::eval() const
{
    return implExpression->eval();
}

template <class T>
std::string Expression<T>::toString() const
{
    return implExpression->toString();
}

template <class T>
Expression<T> Expression<T>::diff(const std::string& variable) const
{
    return Expression<T>(implExpression->diff(variable));
}

template <class T>
Expression<T> Expression<T>::subs(const std::unordered_map<std::string, T>& substitution_map) const
{
    return Expression<T>(implExpression->subs(substitution_map));
}


template
class Expression<int>;
template
class Expression<double>;
template
class Expression<std::complex<double>>;