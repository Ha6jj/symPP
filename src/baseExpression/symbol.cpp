#include "baseExpression.hpp"


template <class T>
Symbol<T>::Symbol(const std::string& _name): name(_name) {}

template <class T>
T Symbol<T>::eval() const
{
    std::cout << "Can't evaluate expression with variables" << std::endl;
    return T(0);
}

template <class T>
std::string Symbol<T>::toString() const
{
    return name;
}

template <class T>
std::shared_ptr<BaseExpression<T>> Symbol<T>::diff(const std::string& variable) const
{
    if (name == variable)
    {
        return std::make_shared<Constant<T>>(Constant<T>(1.0));
    }
    return std::make_shared<Constant<T>>(Constant<T>(0.0));
}

template <class T>
std::shared_ptr<BaseExpression<T>> Symbol<T>::subs(const std::unordered_map<std::string, T>& substitution_map) const
{
    if (substitution_map.find(name) == substitution_map.end())
    {
        return std::make_shared<Symbol<T>>(Symbol<T>(name));
    }
    return std::make_shared<Constant<T>>(Constant<T>(substitution_map.at(name)));
}


template
class Symbol<int>;
template
class Symbol<double>;
template
class Symbol<std::complex<double>>;