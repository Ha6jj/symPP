#include "./src/expression.hpp"
#include <regex>

//g++ -o differentiator differentiator.cpp ./src/*.cpp ./src/baseExpression/*.cpp

int find_occurrences(const std::string& s, const std::string& pattern)
{
    int occurrences = 0;
    std::string::size_type pos = 0;
    while ((pos = s.find(pattern, pos)) != std::string::npos)
    {
        ++occurrences;
        pos += pattern.length();
    }
    return occurrences;
}

int main(int argc, char *argv[])
{
    std::string expr, diff_by;
    bool evalFlag = false;
    bool diffFlag = false;
    bool compFlag = false;
    std::unordered_map<std::string, double> variables;
    std::unordered_map<std::string, std::complex<double>> complex_variables;

    for (int i = 1; i < argc; i++)
    {
        std::string arg = argv[i];
        if (arg == "--eval" || arg == "--diff") {
            expr = argv[i + 1];
            diffFlag = (arg == "--diff");
            evalFlag = (arg == "--eval");
        }
        else if (arg == "--by")
        {
            diff_by = argv[i + 1];
        }
        else if (arg.find("=") != std::string::npos)
        {
            auto pos = arg.find("=");
            std::string variable = arg.substr(0, pos);
            std::string value = arg.substr(pos + 1);
            compFlag = value.find("i") != std::string::npos;
            std::smatch match;
            std::regex complex_regex(R"(([+-]?\d*\.?\d+)([+-]\d*\.?\d*)i)");
            if (compFlag && std::regex_match(value, match, complex_regex))
            {
                complex_variables[variable] = std::complex<double>(std::stod(match[1].str()), std::stod(match[2].str()));
            }
            else
            {
                variables[variable] = std::stod(value);
            }
        }
    }

    std::stringstream hunter;
    if (compFlag || (find_occurrences(expr, "i") - find_occurrences(expr, "sin") > 0))
    {
        Expression<std::complex<double>> expression = parse<std::complex<double>>(expr);
        if (diffFlag)
        {
            hunter << expression.diff(diff_by).toString();
        }

        for (auto const &var : variables)
        {
            complex_variables[var.first] = std::complex<double>(var.second);
        }
        if (evalFlag)
        {
            hunter << expression.subs(complex_variables).eval();
        }
        
    }
    else
    {
        Expression<double> expression = parse<double>(expr);
        if (diffFlag)
        {
            hunter << expression.diff(diff_by).toString();
        }
        if (evalFlag)
        {
            hunter << expression.subs(variables).eval();
        }
    }
    std::cout << hunter.str() << std::endl;
    return 0;
}