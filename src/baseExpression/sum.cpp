#include "baseExpression.hpp"


template <class T>
Sum<T>::Sum(const std::shared_ptr<BaseExpression<T>>& _first, const std::shared_ptr<BaseExpression<T>>& _second): first(_first), second(_second) {}

template <class T>
T Sum<T>::eval() const
{
    return first->eval() + second->eval();
}

template <class T>
std::string Sum<T>::toString() const
{
    return first->toString() + "+" + second->toString();
}

template <class T>
std::shared_ptr<BaseExpression<T>> Sum<T>::diff(const std::string& variable) const
{
    return std::make_shared<Sum<T>>(first->diff(variable), second->diff(variable));
}

template <class T>
std::shared_ptr<BaseExpression<T>> Sum<T>::subs(const std::unordered_map<std::string, T>& substitution_map) const
{
    return std::make_shared<Sum<T>>(first->subs(substitution_map), second->subs(substitution_map));
}


template
class Sum<int>;
template
class Sum<double>;
template
class Sum<std::complex<double>>;