#include "./src/expression.hpp"

int main()
{
    // std::string s;
    // std::cin >> s;
    // Expression<std::complex<double>> expr = parse<std::complex<double>>(s);
    // std::cout << expr.toString() << std::endl;

    Expression<double> expr = Expression<double>("x") + Expression<double>("y");
    std::cout << expr.diff("x").toString() << std::endl;
    return 0;
}