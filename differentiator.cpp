#include "./src/expression.hpp"

#include <regex>

template <typename T, typename VarMap>
std::string process(Expression<T> expr, bool diffFlag, bool evalFlag, const std::string &diff_by, const VarMap &substitution_map)
{
    std::stringstream hunter;
    if (diffFlag)
    {
        hunter << expr.diff(diff_by).toString();
    }
    if (evalFlag)
    {
        hunter << expr.subs(substitution_map).eval();
    }
    return hunter.str();
}

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
    bool contains_complex = false;
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
            std::string var_name = arg.substr(0, pos);
            std::string val_str = arg.substr(pos + 1);
            contains_complex = val_str.find("i") != std::string::npos;
            std::smatch match;
            std::regex complex_regex(R"(([+-]?\d*\.?\d+)([+-]\d*\.?\d*)i)");
            if (contains_complex && std::regex_match(val_str, match, complex_regex))
            {
                complex_variables[var_name] = std::complex<double>(std::stod(match[1].str()), std::stod(match[2].str()));
            }
            else
            {
                variables[var_name] = std::stod(val_str);
            }
        }
    }

    if (contains_complex || (find_occurrences(expr, "i") - find_occurrences(expr, "sin") > 0))
    {
        Expression<std::complex<double>> expression = parse<std::complex<double>>(expr);
        for (auto const &var : variables)
        {
            complex_variables[var.first] = std::complex<double>(var.second);
        }
        std::cout << process(expression, diffFlag, evalFlag, diff_by, complex_variables) << std::endl;
    }
    else
    {
        Expression<double> expression = parse<double>(expr);
        std::cout << process(expression, diffFlag, evalFlag, diff_by, variables) << std::endl;
    }
    return 0;
}