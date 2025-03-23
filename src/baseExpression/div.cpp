#include "baseExpression.hpp"


template <class T>
Div<T>::Div(const std::shared_ptr<BaseExpression<T>>& _first, const std::shared_ptr<BaseExpression<T>>& _second): first(_first), second(_second) {}

template <class T>
T Div<T>::eval() const
{
    T denominator = second->eval();
    if (denominator == T(0))
    {
        std::cout << "Division by zero!" << std::endl;
    }
    return first->eval() / denominator;
}

template <class T>
std::string Div<T>::toString() const
{
    return "(" + first->toString() + ")/(" + second->toString() + ")";
}

template <class T>
std::shared_ptr<BaseExpression<T>> Div<T>::diff(const std::string& variable) const
{
    return std::make_shared<Div<T>>(
        std::make_shared<Sub<T>>(
            std::make_shared<Prod<T>>(first->diff(variable), second), 
            std::make_shared<Prod<T>>(first, second->diff(variable))),
        std::make_shared<Prod<T>>(second, second));
}

template <class T>
std::shared_ptr<BaseExpression<T>> Div<T>::subs(const std::unordered_map<std::string, T>& substitution_map) const
{
    return std::make_shared<Div<T>>(first->subs(substitution_map), second->subs(substitution_map));
}


template
class Div<int>;
template
class Div<double>;
template
class Div<std::complex<double>>;