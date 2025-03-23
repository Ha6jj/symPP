#include "baseExpression.hpp"


template <class T>
Sin<T>::Sin(const std::shared_ptr<BaseExpression<T>>& _first): first(_first) {}

template <class T>
T Sin<T>::eval() const
{
    return std::sin(first->eval());
}

template <class T>
std::string Sin<T>::toString() const
{
    return "sin(" + first->toString() + ")";
}

template <class T>
std::shared_ptr<BaseExpression<T>> Sin<T>::diff(const std::string& variable) const
{
    return std::make_shared<Prod<T>>(
        first->diff(variable), 
        std::make_shared<Cos<T>>(first));
}

template <class T>
std::shared_ptr<BaseExpression<T>> Sin<T>::subs(const std::unordered_map<std::string, T>& substitution_map) const
{
    return std::make_shared<Sin<T>>(first->subs(substitution_map));
}


template
class Sin<int>;
template
class Sin<double>;
template
class Sin<std::complex<double>>;