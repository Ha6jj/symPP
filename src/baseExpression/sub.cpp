#include "baseExpression.hpp"


template <class T>
Sub<T>::Sub(const std::shared_ptr<BaseExpression<T>>& _first, const std::shared_ptr<BaseExpression<T>>& _second): first(_first), second(_second) {}

template <class T>
T Sub<T>::eval() const
{
    return first->eval() - second->eval();
}

template <class T>
std::string Sub<T>::toString() const
{
    return first->toString() + "-" + second->toString();
}

template <class T>
std::shared_ptr<BaseExpression<T>> Sub<T>::diff(const std::string& variable) const
{
    return std::make_shared<Sub<T>>(first->diff(variable), second->diff(variable));
}

template <class T>
std::shared_ptr<BaseExpression<T>> Sub<T>::subs(const std::unordered_map<std::string, T>& substitution_map) const
{
    return std::make_shared<Sub<T>>(first->subs(substitution_map), second->subs(substitution_map));
}


template
class Sub<int>;
template
class Sub<double>;
template
class Sub<std::complex<double>>;