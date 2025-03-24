#include "./src/expression.hpp"

//g++ -o main main.cpp ./src/*.cpp ./src/baseExpression/*.cpp

int main()
{
    Expression<double> expr = Expression<double>("x") + Expression<double>("y");
    std::cout << expr.diff("x").toString() << std::endl;
    return 0;
}