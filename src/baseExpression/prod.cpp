#include "baseExpression.hpp"


template <class T>
Prod<T>::Prod(const std::shared_ptr<BaseExpression<T>>& _first, const std::shared_ptr<BaseExpression<T>>& _second): first(_first), second(_second) {}

template <class T>
T Prod<T>::eval() const
{
    return first->eval() * second->eval();
}

template <class T>
std::string Prod<T>::toString() const
{
    return "(" + first->toString() + ")*(" + second->toString() + ")";
}

template <class T>
std::shared_ptr<BaseExpression<T>> Prod<T>::diff(const std::string& variable) const
{
    return std::make_shared<Sum<T>>(
        std::make_shared<Prod<T>>(first->diff(variable), second), 
        std::make_shared<Prod<T>>(first, second->diff(variable)));
}

template <class T>
std::shared_ptr<BaseExpression<T>> Prod<T>::subs(const std::unordered_map<std::string, T>& substitution_map) const
{
    return std::make_shared<Prod<T>>(first->subs(substitution_map), second->subs(substitution_map));
}


template
class Prod<int>;
template
class Prod<double>;
template
class Prod<std::complex<double>>;