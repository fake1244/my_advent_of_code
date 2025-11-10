#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <regex>

#include "aoc_day_3.h"
#include "file_utils.h"

using namespace std;

AocDay3::AocDay3():AocDay(3)
{
}

AocDay3::~AocDay3()
{
}

string AocDay3::read_input(string filename)
{
    FileUtils fileutils;
    vector<string> raw_lines;
    string memory {};

    if (!fileutils.read_as_list_of_strings(filename, raw_lines))
    {
        cerr << "Error reading in the data from " << filename << endl;
        return memory;
    }

    for (auto raw_line : raw_lines)
        memory += raw_line;

    return memory;
}

string AocDay3::part1(string filename, vector<string> extra_args)
{
    auto data = read_input(filename);
    int sum {};

    std::regex mul_regex("mul\\((\\d+),(\\d+)\\)");
    auto commands_begin = std::sregex_iterator(data.begin(), data.end(), mul_regex);
    auto commands_end = std::sregex_iterator();
  
    for (std::sregex_iterator i = commands_begin; i != commands_end; ++i)
    {
        std::smatch match = *i;
        int n1 = std::stoi(match[1].str()); 
        int n2 = std::stoi(match[2].str()); 
        sum += n1 * n2;
    }

    return std::to_string(sum);
}

string AocDay3::part2(string filename, vector<string> extra_args)
{
    auto data = read_input(filename);
    int sum {};

    std::regex cmd_regex(R"((mul|do|don't)\((?:(\d+),(\d+))?\))");
    auto commands_begin = std::sregex_iterator(data.begin(), data.end(), cmd_regex);
    auto commands_end = std::sregex_iterator();
  
    bool do_next { true };

    for (std::sregex_iterator i = commands_begin; i != commands_end; ++i)
    {
        std::smatch match = *i;
        std::string cmd = match[1].str();

        if(cmd == "do"){
            do_next = true;
            continue;
        }

        if(cmd == "don't"){
            do_next = false;
            continue;
        }

        if(cmd == "mul" && do_next){
            int n1 = std::stoi(match[2].str()); 
            int n2 = std::stoi(match[3].str()); 
            sum += n1 * n2;
        }
        
    }

    return std::to_string(sum);
}
