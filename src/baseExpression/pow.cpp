#include "baseExpression.hpp"


template <class T>
Pow<T>::Pow(const std::shared_ptr<BaseExpression<T>>& _first, const std::shared_ptr<BaseExpression<T>>& _second): first(_first), second(_second) {}

template <class T>
T Pow<T>::eval() const
{
    return std::pow(first->eval(), second->eval());
}

template <class T>
std::string Pow<T>::toString() const
{
    return "(" + first->toString() + ")^(" + second->toString() + ")";
}

template <class T>
std::shared_ptr<BaseExpression<T>> Pow<T>::diff(const std::string& variable) const
{
    return std::make_shared<Exp<T>>(
        std::make_shared<Prod<T>>(
            second, 
            std::make_shared<Ln<T>>(first)))->diff(variable);
}

template <class T>
std::shared_ptr<BaseExpression<T>> Pow<T>::subs(const std::unordered_map<std::string, T>& substitution_map) const
{
    return std::make_shared<Pow<T>>(first->subs(substitution_map), second->subs(substitution_map));
}


template
class Pow<int>;
template
class Pow<double>;
template
class Pow<std::complex<double>>;