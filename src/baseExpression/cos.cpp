#include "baseExpression.hpp"


template <class T>
Cos<T>::Cos(const std::shared_ptr<BaseExpression<T>>& _first): first(_first) {}

template <class T>
T Cos<T>::eval() const
{
    return std::cos(first->eval());
}

template <class T>
std::string Cos<T>::toString() const
{
    return "cos(" + first->toString() + ")";
}

template <class T>
std::shared_ptr<BaseExpression<T>> Cos<T>::diff(const std::string& variable) const
{
    return std::make_shared<Prod<T>>(
        std::make_shared<Constant<T>>(T(-1)),
        std::make_shared<Prod<T>>(
            first->diff(variable), 
            std::make_shared<Sin<T>>(first)));
}

template <class T>
std::shared_ptr<BaseExpression<T>> Cos<T>::subs(const std::unordered_map<std::string, T>& substitution_map) const
{
    return std::make_shared<Cos<T>>(first->subs(substitution_map));
}


template
class Cos<int>;
template
class Cos<double>;
template
class Cos<std::complex<double>>;