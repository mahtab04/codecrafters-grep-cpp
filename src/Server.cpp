#include <iostream>
#include <string>

bool match_digits(const std::string& inputs, const std::string& pattern) 
{
    for (auto input : inputs) 
    {
        if (isdigit(input)) 
        {
            return true;
        }
    }
    return false;
}

bool match_alphanumeric(const std::string& inputs, const std::string& pattern) 
{
    for (auto input : inputs) 
    {
        if (isalnum(input)) 
        {
            return true;
        }
    }
    return false;
}

bool match_group(const std::string& inputs, const std::string& pattern) 
{
    return inputs.find_first_of(pattern) != std::string::npos;
}


bool match_pattern(const std::string& input_line, const std::string& pattern) {
    if (pattern.size() == 0) return true;
    if (input_line.size() == 0) return false;

    if (pattern.substr(0, 2) == "\\d") 
    {
        if (isdigit(input_line[0])) 
        {
            return match_pattern(input_line.substr(1), pattern.substr(2));
        }
        return match_pattern(input_line.substr(1), pattern);
    }
    else if (pattern.substr(0, 2) == "\\w") 
    {
        if (isalnum(input_line[0])) 
        {
            return match_pattern(input_line.substr(1), pattern.substr(2));
        }
        return match_pattern(input_line.substr(1), pattern);
    }
    else if (pattern[0] == '[') 
    {
        auto pos = pattern.find_first_of("]");
        if (pattern[1] == '^') 
        {
            if (!match_group(input_line, pattern.substr(2, pos - 2))) 
            {
                return match_pattern(input_line.substr(1), pattern.substr(pos + 1));
            }
            return false;
        }
        if (match_group(input_line, pattern.substr(1, pos - 1))) 
        {
            return match_pattern(input_line.substr(1), pattern.substr(pos + 1));
        }
        return false;
    }

    if (pattern[0] == input_line[0]) 
    {
        return match_pattern(input_line.substr(1), pattern.substr(1));
    }

    return match_pattern(input_line.substr(1), pattern);
}

bool match_patterns(std::string& input_line, std::string& pattern)
{
    if (pattern.empty()) return true;

    if (pattern[0] == '^')
    {
        // Ensure the match starts from the beginning of the input_line
        return match_pattern(input_line, pattern.substr(1));
    }
    else
    {
        do
        {
            if (match_pattern(input_line, pattern))
            {
                return true;
            }
            input_line = input_line.substr(1); // Move to the next character
        } while (!input_line.empty());

        return false;
    }
}
8