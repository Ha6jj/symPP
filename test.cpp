#include "./src/expression.hpp"

void test_constructor()
{
    bool result = true;

    result = result && (Expression<double>(0).toString() == "0");
    result = result && (Expression<double>("x").toString() == "x");
    Expression<double> expr = Expression<double>("x") + Expression<double>("y");
    Expression<double> copy = expr;
    result = result && (expr.toString() == copy.toString());

    if (result)
        std::cout << "[OK]   Constructors are ok\n";
    else
        std::cout << "[FAIL] Constructors are not ok\n";
}

void test_utils()
{
    bool result = true;

    Expression<double> expr = Expression<double>("x") + Expression<double>("y");
    result = result && (Expression<double>(55).eval() == 55);
    result = result && (expr.toString() == "x+y");
    result = result && (expr.diff("x").toString() == "1+0");
    result = result && (expr.subs({{"x", 44}, {"y", 11}}).eval() == 55);

    if (result)
        std::cout << "[OK]   Utils are ok\n";
    else
        std::cout << "[FAIL] Utils are not ok\n";
}

void test_operations()
{
    bool result = true;

    Expression<double> expr = Expression<double>("x") + Expression<double>("y");
    result = result && (expr.cos().toString() == "cos(x+y)");
    result = result && ((expr + expr.ln()).toString() == "x+y+ln(x+y)");
    result = result && ((expr ^ Expression<double>(34)).toString() == "(x+y)^(34)");

    if (result)
        std::cout << "[OK]   Operations are ok\n";
    else
        std::cout << "[FAIL] Operations are not ok\n";
}

void test_parser()
{
    bool result = true;
    result = result && (parse<std::complex<double>>("x+2i*ln(y)").toString() == "x+((0,2))*(ln(y))");
    result = result && (parse<std::complex<double>>("cos(10i+exp(z))").toString() == "cos((0,10)+exp(z))");
    result = result && (parse<std::complex<double>>("(var+zxc)^(10+sin(ggg))").toString() == "(var+zxc)^((10,0)+sin(ggg))");

    if (result)
        std::cout << "[OK]   Parser is ok\n";
    else
        std::cout << "[FAIL] Parser is not ok\n";
}


int main()
{
    test_constructor();
    test_utils();
    test_operations();
    test_parser();
    return 0;
}