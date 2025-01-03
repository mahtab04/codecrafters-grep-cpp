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

    else if (pattern[0] == '^')
    {
        return match_pattern(input_line, pattern.substr(1));
    }

    if (pattern[0] == input_line[0]) 
    {
        return match_pattern(input_line.substr(1), pattern.substr(1));
    }

    return match_pattern(input_line.substr(1), pattern);
}

bool match_patterns(std::string& input_line, std::string& pattern) 
{
    do {
        if (match_pattern(input_line, pattern)) {
            return true;
        }
        input_line = input_line.substr(1);
    } while (!input_line.empty());

    return false;
}

int main(int argc, char *argv[])
{
    // Flush after every std::cout / std::cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    // You can use print statements as follows for debugging, they'll be visible when running tests.
    std::cerr << "Logs from your program will appear here" << std::endl;

    if (argc != 3)
    {
        std::cerr << "Expected two arguments" << std::endl;
        return 1;
    }

    std::string flag = argv[1];
    std::string pattern = argv[2];

    if (flag != "-E")
    {
        std::cerr << "Expected first argument to be '-E'" << std::endl;
        return 1;
    }

    std::string input_line;
    std::getline(std::cin, input_line);

    try
    {
        if (match_patterns(input_line, pattern))
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}
