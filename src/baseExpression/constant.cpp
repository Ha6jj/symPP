#include "baseExpression.hpp"


template <class T>
Constant<T>::Constant(const T& _value): value(_value) {}

template <class T>
T Constant<T>::eval() const
{
    return value;
}

template <class T>
std::string Constant<T>::toString() const
{
    std::ostringstream hunter;
    hunter << value;
    return hunter.str();
}

template <class T>
std::shared_ptr<BaseExpression<T>> Constant<T>::diff(const std::string& variable) const
{
    return std::make_shared<Constant<T>>(Constant<T>(T(0)));
}

template <class T>
std::shared_ptr<BaseExpression<T>> Constant<T>::subs(const std::unordered_map<std::string, T>& substitution_map) const
{
    return std::make_shared<Constant<T>>(Constant<T>(value));
}


template
class Constant<int>;
template
class Constant<double>;
template
class Constant<std::complex<double>>;