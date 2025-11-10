#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <regex>

#include "aoc_day_4.h"
#include "file_utils.h"

using namespace std;

AocDay4::AocDay4():AocDay(4)
{
}

AocDay4::~AocDay4()
{
}

vector<vector<char>> AocDay4::read_input(string filename)
{
    FileUtils fileutils;
    vector<string> raw_lines;
    vector<vector<char>> data {};

    if (!fileutils.read_as_list_of_strings(filename, raw_lines))
    {
        cerr << "Error reading in the data from " << filename << endl;
        return data;
    }

    for (auto & line : raw_lines){
        vector<char> row;
        for (auto& c : line)
            row.push_back(c);
        
        data.push_back(row);
    }

    return data;
}

int AocDay4::count_horizontal(vector<vector<char>> data)
{
    int count { 0 };

    for(auto& row : data){
        for (size_t i {}; i < row.size() - 3; ++i){
            if (is_xmas(row[i], row[i+1], row[i+2], row[i+3]))
                count++;
        }
    }

    return count;
}

int AocDay4::count_vertical(vector<vector<char>> data)
{
    int count { 0 };

    for(size_t i {}; i < data.size() - 3; ++i){
        for (size_t j {}; j < data[i].size(); ++j){
            if (is_xmas(data[i][j], data[i+1][j], data[i+2][j], data[i+3][j]))
                count++;
        }
    }
    
    return count;
}

int AocDay4::count_diagonal(vector<vector<char>> data)
{
    int count { 0 };

    int n = data.size();
    int m = data[0].size();

    for (int i {}; i < n - 3; ++i)
        for (int j {}; j < m - 3; ++j)
            if(is_xmas(data[i][j], data[i + 1][j + 1], data[i + 2][j + 2], data[i + 3][j + 3]))
                count++;

    for (int i {}; i < n - 3; ++i)   
        for (int j { 3 }; j < m; ++j)
            if(is_xmas(data[i][j], data[i + 1][j - 1], data[i + 2][j - 2], data[i + 3][j - 3]))
                count++;

    return count;
}

bool AocDay4::is_xmas(char c1, char c2, char c3, char c4)
{
    return (c1 == 'X' && c2 == 'M' && c3 == 'A' && c4 == 'S') || (c4 == 'X' && c3 == 'M' && c2 == 'A' && c1 == 'S');
}

string AocDay4::part1(string filename, vector<string> extra_args){
    auto data = read_input(filename);
    int count { 0 };

    count += count_horizontal(data);
    count += count_vertical(data);
    count += count_diagonal(data);

    return to_string(count);
}

string AocDay4::part2(string filename, vector<string> extra_args)
{
    return "0";
}
