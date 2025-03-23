#include "baseExpression.hpp"


template <class T>
Exp<T>::Exp(const std::shared_ptr<BaseExpression<T>>& _first): first(_first) {}

template <class T>
T Exp<T>::eval() const
{
    return std::exp(first->eval());
}

template <class T>
std::string Exp<T>::toString() const
{
    return "exp(" + first->toString() + ")";
}

template <class T>
std::shared_ptr<BaseExpression<T>> Exp<T>::diff(const std::string& variable) const
{
    return std::make_shared<Prod<T>>(
        first->diff(variable), 
        std::make_shared<Exp<T>>(first));
}

template <class T>
std::shared_ptr<BaseExpression<T>> Exp<T>::subs(const std::unordered_map<std::string, T>& substitution_map) const
{
    return std::make_shared<Exp<T>>(first->subs(substitution_map));
}


template
class Exp<int>;
template
class Exp<double>;
template
class Exp<std::complex<double>>;