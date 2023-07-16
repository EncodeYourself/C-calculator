#include <string>
#include <vector>
#include <iostream>

#include "calc_functions.h"


int main()
{
    std::vector<std::string> tests
    {
        "(5 + 5) * 3 - 4 + 3 / 2", // 27.5
        "5^2 *  3--4", // 79
        "-5 + (-5) + (5) * (-5)", // -35
        "-5^2 * -5^2/5", //125
        "5^(.4)",
        "5^.4" 

    };
    
    for (const std::string& str: tests)
    {
        double result = calculator(str);
        std::cout << result << std::endl;
    };
    
}