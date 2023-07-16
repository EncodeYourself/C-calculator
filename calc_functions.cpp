#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <unordered_map>

using std::string;
using double_int_vector = std::vector<std::pair<double, int>>;

std::unordered_map<char, int> lookup_table
{
    {'^', 1}, {'/', 2}, {'*', 3}, {'+', 4}, 
    {'-', 5}, {'(', 6}, {')', 7}, {' ', -1}

};


double_int_vector preprocessor(const std::string& input)
{
    string temp;
    double_int_vector result;

    for (auto idx = input.begin(); idx != input.end(); ++idx)
    {
        int type = lookup_table[*idx];
 
        switch (type)
        {
            case -1: break;
            case 5:
                if (idx == input.begin()) temp += *idx;
                else 
                {
                    if (temp.empty() && result.back().second > 0) temp += *idx;
                    else goto seven;
                }
                break;
            case 1:
            case 2:
            case 3:
            case 4:
            case 6:
            case 7:
                if (!temp.empty())
                {
                    seven:
                    result.push_back(std::make_pair(std::stod(temp), 0));
                    temp = "";
                }
                result.push_back(std::make_pair(0, type));
                break;
            default: 
                temp += *idx;
                break;
            

        }
    }
    if (!temp.empty()) result.push_back(std::make_pair(std::stod(temp), 0));
    return result;
}

double solver(double number1, int operation_type, double number2)
{
    switch(operation_type)
    {
        case 1: return std::pow(number1, number2);
        case 2: return number1 / number2;
        case 3: return number1 * number2;
        case 4: return number1 + number2;
        case 5: return number1 - number2;
        default: return 0;
    }
}

std::pair<double, int> 
sequence_solver(double_int_vector& input,
                double_int_vector::iterator begin, 
                double_int_vector::iterator end, bool mode = 0)
{   
    auto new_end = end - 2 - mode;
    for (size_t priority{1}; priority < 6; priority += 2)
    {
        for (auto idx = begin + mode; idx <= new_end; )
        {
            if ((idx+1)->second <= priority)
            {
                idx->first = solver(idx->first, (idx+1)->second, (idx+2)->first);
                
                input.erase(idx+2);
                input.erase(idx+1);
                new_end -= 2;
            }
            else idx += 2;
        }
    }
    
    return input[mode];
}
std::pair<double, int> sequence_solver(double_int_vector& input, bool mode = 0)
{
    return sequence_solver(input, input.begin(), input.end(), mode);
}

double calculator(const std::string& input)
{
    double_int_vector preprocessed_input = preprocessor(input);
    std::vector<double_int_vector::iterator> seq_beg;
    auto new_end = preprocessed_input.end();
    
    for (auto idx = preprocessed_input.begin(); 
        idx < new_end; ++idx)
    {
        if (idx->second == 6) seq_beg.push_back(idx); 
        else if (idx->second == 7)
        {

            double_int_vector::iterator new_idx = seq_beg.back();
            int difference = idx - new_idx;
            new_end -= difference;

            if (difference > 2) 
            {
                *new_idx = sequence_solver(preprocessed_input, new_idx, idx, 1);
                
                preprocessed_input.erase(new_idx+1, idx-1);

                idx = new_idx;
            }
            else 
            {
                double_int_vector::iterator new_idx = seq_beg.back();

                *new_idx = *(new_idx+1);
                preprocessed_input.erase(new_idx+1, idx+1);
            }

            seq_beg.pop_back();
            idx = new_idx;
        }
    }
    double result = sequence_solver(preprocessed_input).first;

    return result;
}