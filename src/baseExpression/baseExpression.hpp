#ifndef BASE_EXPRESSION_HEADER_GUARD
#define BASE_EXPRESSION_HEADER_GUARD


#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>
#include <sstream>
#include <cmath>
#include <complex>
#include <type_traits>


template<class T>
class BaseExpression
{
public:
    virtual ~BaseExpression() = default;
    
    virtual T eval() const = 0;
    virtual std::string toString() const = 0;
    virtual std::shared_ptr<BaseExpression<T>> diff(const std::string& varriable) const = 0;
    virtual std::shared_ptr<BaseExpression<T>> subs(const std::unordered_map<std::string, T>&) const = 0;
};

template<class T>
class Symbol final: public BaseExpression<T>
{
    std::string name;

public:
    Symbol(const std::string&);

    virtual T eval() const override;
    virtual std::string toString() const override;
    virtual std::shared_ptr<BaseExpression<T>> diff(const std::string& varriable) const override;
    virtual std::shared_ptr<BaseExpression<T>> subs(const std::unordered_map<std::string, T>&) const override;
};

template<class T>
class Constant final: public BaseExpression<T>
{
    T value;

public:
    Constant(const T&);

    virtual T eval() const override;
    virtual std::string toString() const override;
    virtual std::shared_ptr<BaseExpression<T>> diff(const std::string& varriable) const override;
    virtual std::shared_ptr<BaseExpression<T>> subs(const std::unordered_map<std::string, T>&) const override;
};

template<class T>
class Sum final: public BaseExpression<T>
{
    std::shared_ptr<BaseExpression<T>> first;
    std::shared_ptr<BaseExpression<T>> second;

public:
    Sum(const std::shared_ptr<BaseExpression<T>>&, const std::shared_ptr<BaseExpression<T>>&);

    virtual T eval() const override;
    virtual std::string toString() const override;
    virtual std::shared_ptr<BaseExpression<T>> diff(const std::string& varriable) const override;
    virtual std::shared_ptr<BaseExpression<T>> subs(const std::unordered_map<std::string, T>&) const override;
};

template<class T>
class Sub final: public BaseExpression<T>
{
    std::shared_ptr<BaseExpression<T>> first;
    std::shared_ptr<BaseExpression<T>> second;

public:
    Sub(const std::shared_ptr<BaseExpression<T>>&, const std::shared_ptr<BaseExpression<T>>&);

    virtual T eval() const override;
    virtual std::string toString() const override;
    virtual std::shared_ptr<BaseExpression<T>> diff(const std::string& varriable) const override;
    virtual std::shared_ptr<BaseExpression<T>> subs(const std::unordered_map<std::string, T>&) const override;
};

template<class T>
class Prod final: public BaseExpression<T>
{
    std::shared_ptr<BaseExpression<T>> first;
    std::shared_ptr<BaseExpression<T>> second;

public:
    Prod(const std::shared_ptr<BaseExpression<T>>&, const std::shared_ptr<BaseExpression<T>>&);

    virtual T eval() const override;
    virtual std::string toString() const override;
    virtual std::shared_ptr<BaseExpression<T>> diff(const std::string& varriable) const override;
    virtual std::shared_ptr<BaseExpression<T>> subs(const std::unordered_map<std::string, T>&) const override;
};

template<class T>
class Div final: public BaseExpression<T>
{
    std::shared_ptr<BaseExpression<T>> first;
    std::shared_ptr<BaseExpression<T>> second;

public:
    Div(const std::shared_ptr<BaseExpression<T>>&, const std::shared_ptr<BaseExpression<T>>&);

    virtual T eval() const override;
    virtual std::string toString() const override;
    virtual std::shared_ptr<BaseExpression<T>> diff(const std::string& varriable) const override;
    virtual std::shared_ptr<BaseExpression<T>> subs(const std::unordered_map<std::string, T>&) const override;
};

template<class T>
class Pow final: public BaseExpression<T>
{
    std::shared_ptr<BaseExpression<T>> first;
    std::shared_ptr<BaseExpression<T>> second;

public:
    Pow(const std::shared_ptr<BaseExpression<T>>&, const std::shared_ptr<BaseExpression<T>>&);

    virtual T eval() const override;
    virtual std::string toString() const override;
    virtual std::shared_ptr<BaseExpression<T>> diff(const std::string& varriable) const override;
    virtual std::shared_ptr<BaseExpression<T>> subs(const std::unordered_map<std::string, T>&) const override;
};

template<class T>
class Sin final: public BaseExpression<T>
{
    std::shared_ptr<BaseExpression<T>> first;

public:
    Sin(const std::shared_ptr<BaseExpression<T>>&);

    virtual T eval() const override;
    virtual std::string toString() const override;
    virtual std::shared_ptr<BaseExpression<T>> diff(const std::string& varriable) const override;
    virtual std::shared_ptr<BaseExpression<T>> subs(const std::unordered_map<std::string, T>&) const override;
};

template<class T>
class Cos final: public BaseExpression<T>
{
    std::shared_ptr<BaseExpression<T>> first;

public:
    Cos(const std::shared_ptr<BaseExpression<T>>&);

    virtual T eval() const override;
    virtual std::string toString() const override;
    virtual std::shared_ptr<BaseExpression<T>> diff(const std::string& varriable) const override;
    virtual std::shared_ptr<BaseExpression<T>> subs(const std::unordered_map<std::string, T>&) const override;
};

template<class T>
class Ln final: public BaseExpression<T>
{
    std::shared_ptr<BaseExpression<T>> first;

public:
    Ln(const std::shared_ptr<BaseExpression<T>>&);

    virtual T eval() const override;
    virtual std::string toString() const override;
    virtual std::shared_ptr<BaseExpression<T>> diff(const std::string& varriable) const override;
    virtual std::shared_ptr<BaseExpression<T>> subs(const std::unordered_map<std::string, T>&) const override;
};

template<class T>
class Exp final: public BaseExpression<T>
{
    std::shared_ptr<BaseExpression<T>> first;

public:
    Exp(const std::shared_ptr<BaseExpression<T>>&);

    virtual T eval() const override;
    virtual std::string toString() const override;
    virtual std::shared_ptr<BaseExpression<T>> diff(const std::string& varriable) const override;
    virtual std::shared_ptr<BaseExpression<T>> subs(const std::unordered_map<std::string, T>&) const override;
};

#endif