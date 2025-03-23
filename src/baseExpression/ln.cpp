#include "baseExpression.hpp"


template <class T>
Ln<T>::Ln(const std::shared_ptr<BaseExpression<T>>& _first): first(_first) {}

template <class T>
T Ln<T>::eval() const
{
    T argument = first->eval();
    if (argument == T(0))
    {
        std::cout << "Calculating log of zero!" << std::endl;
    }
    return std::log(argument);
}

template <class T>
std::string Ln<T>::toString() const
{
    return "ln(" + first->toString() + ")";
}

template <class T>
std::shared_ptr<BaseExpression<T>> Ln<T>::diff(const std::string& variable) const
{
    return std::make_shared<Div<T>>(
        first->diff(variable), 
        first);
}

template <class T>
std::shared_ptr<BaseExpression<T>> Ln<T>::subs(const std::unordered_map<std::string, T>& substitution_map) const
{
    return std::make_shared<Ln<T>>(first->subs(substitution_map));
}


template
class Ln<int>;
template
class Ln<double>;
template
class Ln<std::complex<double>>;